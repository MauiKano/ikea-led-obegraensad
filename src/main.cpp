#include <Arduino.h>
#include <SPI.h>

#ifdef ESP32
#include <WiFiManager.h>
#endif
#ifdef ESP32
#include <ESPmDNS.h>
#endif
#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

#include "PluginManager.h"

#include "plugins/BreakoutPlugin.h"
#include "plugins/CirclePlugin.h"
#include "plugins/DrawPlugin.h"
#include "plugins/FireworkPlugin.h"
#include "plugins/GameOfLifePlugin.h"
#include "plugins/LinesPlugin.h"
#include "plugins/RainPlugin.h"
#include "plugins/SnakePlugin.h"
#include "plugins/StarsPlugin.h"
#include "plugins/TickingClockPlugin.h"
#include "plugins/TickingSmallClockPlugin.h"
#include "plugins/BinaryClockPlugin.h"

//#include "plugins/PongClockPlugin.h"
#include "plugins/FiveLetterWordsPlugin.h"
 #ifdef FREKVENS
///#include "plugins/FFTPlugin.h"  // does not yet work
#endif
#ifdef ENABLE_SERVER
#include "plugins/AnimationPlugin.h"
//#include "plugins/BigClockPlugin.h"
//#include "plugins/ClockPlugin.h"

#include "plugins/BinaryClockPlugin.h"
#include "plugins/WeatherPlugin.h"
#include "plugins/TelegramBotPlugin.h"

#endif

#include "asyncwebserver.h"
#include "ota.h"
#include "screen.h"
#include "secrets.h"
#include "websocket.h"
#include "messages.h"

#ifdef BME280INSTALLED
#include "tandp.h"
#endif
#ifdef TPHINSTALLED
#include "TPHSensor.h"
#endif

#ifdef RTCINSTALLED
#include <RTClib.h>
RTC_DS3231 rtc;
DateTime rtcTime;
#endif

unsigned long previousMillis = 0;
unsigned long interval = 30000;

#ifdef FREKVENS
 int pwrButtonState = 0;
 int lastPwrButtonState = 1;
 int micValue = 0;
 #endif

PluginManager pluginManager;
SYSTEM_STATUS currentStatus = NONE;
#ifdef ESP32
WiFiManager wifiManager;

#endif
#ifdef ESP32
int modePirState;
int lastModePirState;

#define TIMER0_INTERVAL_MS        40   // initialize timer 1 with 60 seconds
hw_timer_t *Pir_timer = timerBegin(1, ((256*256) - 1), true); // use timer 1 for PIR handling, scale down to 1MHz
bool timerISRCalled = false;
Plugin *alwaysRunPlugin = NULL;  // used to always run the TelegramBot in the main loop
#endif

unsigned long lastConnectionAttempt = 0;
const unsigned long connectionInterval = 10000;

#ifdef ESP32
void connectToWiFi()
{
   //wifiManager.resetSettings(); // wipe stored credentials for testing
  // if a WiFi setup AP was started, reboot is required to clear routes
  bool wifiWebServerStarted = false;
  wifiManager.setTimeout(60);

  wifiManager.setWebServerCallback(
      [&wifiWebServerStarted]()
      { wifiWebServerStarted = true; });

  wifiManager.setHostname(WIFI_HOSTNAME);
  wifiManager.autoConnect(WIFI_MANAGER_SSID);

  if (MDNS.begin(WIFI_HOSTNAME))
  {
    MDNS.addService("http", "tcp", 80);
    MDNS.setInstanceName(WIFI_HOSTNAME);
  }
  else
  {
    Serial.println("Could not start mDNS!");
  }

  if (wifiWebServerStarted)
  {
    // Reboot required, otherwise wifiManager server interferes with our server
    Serial.println("Done running WiFi Manager webserver - rebooting");
    ESP.restart();
  }

  lastConnectionAttempt = millis();
}

 void IRAM_ATTR PirEventHandler() {
  timerISRCalled = true; 
  Screen.setBrightness(1);  // dim the screen after  the timer expired
  timerAlarmDisable(Pir_timer);// disable timer after one execution 
  timerStop(Pir_timer);
}

void setupPirTimer() {
    timerAttachInterrupt(Pir_timer, &PirEventHandler,  true);
    timerAlarmWrite(Pir_timer, TIMER0_INTERVAL_MS*1000, true);
    timerAlarmEnable(Pir_timer);
    Serial.println("Starting  hw Pir Timer ");
    Screen.setBrightness(255);
}

void checkPir(bool turnOn) {
  if (timerISRCalled) { // just simple print statement that should not happen in the ISR
   //   Messages.add("I", 0, 0, 50); // repeat=0, id=0, delay=10
   //   Messages.scroll();
    Serial.println("Timer ISR called");
    timerISRCalled = false;
  }
  modePirState = digitalRead(PIN_PIR);
  if (PIRBTE1619 == 1) modePirState = !modePirState;

  if ((modePirState != lastModePirState && modePirState == HIGH) || turnOn) {
    // do it one more time
    //  Messages.add("M", 0, 0, 50); // repeat=0, id=0, delay=10
    //  Messages.scroll();
      Serial.println("Pir detected motion");
      Screen.setBrightness(255);  // turn display on
      timerAlarmEnable(Pir_timer);
      timerStart(Pir_timer);
  }
  lastModePirState = modePirState;
}
#endif

#ifdef ESP8266
void connectToWiFi()
{
  Serial.println("Connecting to Wi-Fi...");

  // Delete old config
  WiFi.disconnect(true);

#if defined(IP_ADDRESS) && defined(GWY) && defined(SUBNET) && defined(DNS1) && \
    defined(DNS2)
  auto ip = IPAddress();
  ip.fromString(IP_ADDRESS);

  auto gwy = IPAddress();
  gwy.fromString(GWY);

  auto subnet = IPAddress();
  subnet.fromString(SUBNET);

  auto dns1 = IPAddress();
  dns1.fromString(DNS1);

  auto dns2 = IPAddress();
  dns2.fromString(DNS2);

  WiFi.config(ip, gwy, subnet, dns1, dns2);
#endif

  WiFi.setHostname(WIFI_HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Wait for connection
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20)
  {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  // Check connection result
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("\nFailed to connect to Wi-Fi. Please check credentials.");
  }

  lastConnectionAttempt = millis();
}
#endif

void setup()
{
  Serial.begin(115200);

  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_ENABLE, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_PIR, INPUT);

  #ifdef BME280INSTALLED
  pinMode(PIN_I2C_SCL, OUTPUT);
  pinMode(PIN_I2C_SDA, OUTPUT);
  #endif


  #ifdef TPHINSTALLED
  pinMode(PIN_I2C_SCL, OUTPUT);
  pinMode(PIN_I2C_SDA, OUTPUT);
  #endif

#ifdef RTCINSTALLED
  pinMode(GPIO_NUM_21, OUTPUT); //I2C for RTC
  pinMode(GPIO_NUM_22, OUTPUT);
#endif

  #ifdef FREKVENS
   pinMode(PIN_POWER, INPUT_PULLUP);
  // pinMode(MIC_INPUT, INPUT);
 #endif

// server
#ifdef ENABLE_SERVER
  connectToWiFi();

  // set time server
  configTzTime(TZ_INFO, NTP_SERVER);

  initOTA(server);
  initWebsocketServer(server);
  initWebServer();
  #endif

  #ifdef RTCINSTALLED
  // SETUP RTC MODULE
  if (! rtc.begin()) {
    Serial.println("RTC module is NOT found");
    Serial.flush();
    while (1);
  }
  #endif

#ifdef RTCINSTALLED

  #ifdef ENABLE_SERVER
  struct tm ti;
  if (WiFi.status() == WL_CONNECTED && getLocalTime(&ti)) {
    // Time from Internet
      rtc.adjust(DateTime(ti.tm_year, ti.tm_mon, ti.tm_mday, ti.tm_hour, ti.tm_min, ti.tm_sec));
  }
  #endif
#endif

  Screen.setup();
  pluginManager.addPlugin(new TickingClockPlugin());
  pluginManager.addPlugin(new TickingSmallClockPlugin());
  pluginManager.addPlugin(new BinaryClockPlugin());
  pluginManager.addPlugin(new BreakoutPlugin());
  pluginManager.addPlugin(new SnakePlugin());
  pluginManager.addPlugin(new GameOfLifePlugin());
  pluginManager.addPlugin(new StarsPlugin());
  pluginManager.addPlugin(new LinesPlugin());
  pluginManager.addPlugin(new CirclePlugin());
  pluginManager.addPlugin(new RainPlugin());
  //pluginManager.addPlugin(new FireworkPlugin());
  //pluginManager.addPlugin(new PongClockPlugin());
 // pluginManager.addPlugin(new FiveLetterWordsPlugin());

#ifdef FREKVENS
 //  pluginManager.addPlugin(new FFTPlugin()); // does not yet work
#endif

#ifdef ENABLE_SERVER
  //pluginManager.addPlugin(new BigClockPlugin());
  //pluginManager.addPlugin(new ClockPlugin());
  // pluginManager.addPlugin(new DrawPlugin());

  pluginManager.addPlugin(new WeatherPlugin());
  //pluginManager.addPlugin(new AnimationPlugin());

  pluginManager.addPlugin(new BinaryClockPlugin());
 // pluginManager.addPlugin(new TelegramBotPlugin());
  alwaysRunPlugin = new TelegramBotPlugin();
  alwaysRunPlugin->setup();
#endif

  pluginManager.init();
#ifdef ESP32
  setupPirTimer();
#endif

#ifdef ENABLE_SERVER
  Messages.add(WiFi.localIP().toString().c_str());
  Messages.scroll();
#endif

  Messages.add("Welcome :-)");
  Messages.scroll();
}

void loop()
{
  #ifdef FREKVENS
  pwrButtonState = digitalRead(PIN_POWER);
  if (pwrButtonState != lastPwrButtonState && pwrButtonState == HIGH)
  {
    Serial.println("Powerbutton pressed, set status POWEROFF");
    if (currentStatus == POWEROFF) {
      currentStatus = NONE;
      checkPir(true);
      Serial.println("Powerbutton pressed, set status from POWEROFF to NONE");
      Messages.add("Welcome back");
      Messages.scroll();
    } else {
      currentStatus = POWEROFF;
      Serial.println("Powerbutton pressed, set status from NONE to POWEROFF");
      Messages.add("Goodbye :-(");
      Messages.scroll();
      Screen.clear();
    }
 }
 lastPwrButtonState = pwrButtonState;
 //micValue = analogRead(MIC_INPUT);
 //if ((micValue > 4500) || (micValue < 500)) Serial.println(micValue);
  
  if (currentStatus != POWEROFF) {
     Messages.scrollMessageEveryMinute();
    pluginManager.runActivePlugin();
  }
  #endif 


#ifndef FREKVENS
  //Messages.scrollMessageEveryMinute();
  pluginManager.runActivePlugin();
#endif

  if (alwaysRunPlugin) {
     alwaysRunPlugin->loop();
  }
#ifdef ESP32
   checkPir(false);
  
#endif
#ifdef ENABLE_SERVER

  if (WiFi.status() != WL_CONNECTED && millis() - lastConnectionAttempt > connectionInterval)
  {
    Serial.println("Lost connection to Wi-Fi. Reconnecting...");
    connectToWiFi();
  }

  cleanUpClients();
#endif
  delay(1);
}
