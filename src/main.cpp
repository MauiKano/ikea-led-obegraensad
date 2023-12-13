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


#ifdef ESP32
#define _TIMERINTERRUPT_LOGLEVEL_     0
#include  <ESP32_New_TimerInterrupt.h>
#define TIMER0_INTERVAL_MS        5000   // initialize timer 0 with 5000 milli seconds
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

#ifdef ENABLE_SERVER
#include "plugins/AnimationPlugin.h"
#include "plugins/BigClockPlugin.h"
#include "plugins/ClockPlugin.h"
#include "plugins/WeatherPlugin.h"
#endif

#include "asyncwebserver.h"
#include "ota.h"
#include "screen.h"
#include "secrets.h"
#include "websocket.h"

unsigned long previousMillis = 0;
unsigned long interval = 30000;

PluginManager pluginManager;
SYSTEM_STATUS currentStatus = NONE;
#ifdef ESP32
WiFiManager wifiManager;
#endif
#ifdef ESP32
int modePirState;
int lastModePirState;
ESP32Timer ITimer0(1);
hw_timer_t *Screen_timer = timerBegin(0, 80, true);
#endif

unsigned long lastConnectionAttempt = 0;
const unsigned long connectionInterval = 10000;

#ifdef ESP32
void connectToWiFi()
{

  // if a WiFi setup AP was started, reboot is required to clear routes
  bool wifiWebServerStarted = false;
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
// timer interupt stuff
bool IRAM_ATTR TimerHandler(void * timerNo) {
  //Screen.clear();
  Serial.println("Timer ISR called");

  Screen.setBrightness(2);  // dim the screen after  the timer expired
  ITimer0.stopTimer(); // disable timer after one execution
  return true;
}

void setupTimer() {
  if (ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler)) {
    Serial.print("Starting  ITimer0 OK, millis() = ");
    Serial.println(millis());
    ITimer0.enableTimer();
    ITimer0.stopTimer();
    Screen.setBrightness(255);
  } else
     Serial.println("Can't set ITimer0. Select another freq. or timer");
}

void checkPir() {
  modePirState = digitalRead(PIN_PIR);
 // Serial.print("Pir="); Serial.println(modePirState);

  if (modePirState != lastModePirState && modePirState == HIGH) {
      Serial.println("Pir detected motion");
      Screen.setBrightness(255);  // turn display on
      ITimer0.restartTimer();
  } else {
     // ITimer0.disableTimer();
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

// server
#ifdef ENABLE_SERVER
  connectToWiFi();

  // set time server
  configTzTime(TZ_INFO, NTP_SERVER);

  initOTA(server);
  initWebsocketServer(server);
  initWebServer();
#endif

  Screen.setup();

  pluginManager.addPlugin(new DrawPlugin());
  pluginManager.addPlugin(new BreakoutPlugin());
  pluginManager.addPlugin(new SnakePlugin());
  pluginManager.addPlugin(new GameOfLifePlugin());
  pluginManager.addPlugin(new StarsPlugin());
  pluginManager.addPlugin(new LinesPlugin());
  pluginManager.addPlugin(new CirclePlugin());
  pluginManager.addPlugin(new RainPlugin());
  pluginManager.addPlugin(new FireworkPlugin());

#ifdef ENABLE_SERVER
  pluginManager.addPlugin(new BigClockPlugin());
  pluginManager.addPlugin(new ClockPlugin());
  pluginManager.addPlugin(new WeatherPlugin());
  pluginManager.addPlugin(new AnimationPlugin());
#endif

  pluginManager.init();
}

void loop()
{
  pluginManager.runActivePlugin();
#ifdef ESP32
    checkPir();
#endif
  if (WiFi.status() != WL_CONNECTED && millis() - lastConnectionAttempt > connectionInterval)
  {
    Serial.println("Lost connection to Wi-Fi. Reconnecting...");
    connectToWiFi();
  }

#ifdef ENABLE_SERVER
  cleanUpClients();
#endif
  delay(1);
}