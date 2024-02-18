#pragma once

// disable if you do not want to have online functionality
/////#define ENABLE_SERVER

// enable to use led mapping for Frekvens instead of Obegränsad
 // https://www.ikea.com/de/de/p/frekvens-multibeleuchtung-led-schwarz-30420354/ 
//#define FREKVENS

#ifdef ESP32
#define PIN_ENABLE GPIO_NUM_4// 7
#define PIN_DATA   GPIO_NUM_12 // 5
#define PIN_CLOCK  GPIO_NUM_32 //4
#define PIN_LATCH  GPIO_NUM_25 //3
#define PIN_BUTTON GPIO_NUM_27 // 1
#define PIN_PIR    GPIO_NUM_0 // 1
#endif

#ifdef FREKVENS
 #define PIN_POWER  GPIO_NUM_26
 #define PIN_PIR    GPIO_NUM_2 // 0 seems broken on my esp in my FREKVENS box
 //#define MIC_INPUT GPIO_NUM_36
 #endif

#define RTCINSTALLED

#define PIRBTE1619 0 // set to 1 if this pir sensor is used as it has reversed logig


#ifdef ESP8266
#define PIN_ENABLE 16
#define PIN_DATA 13
#define PIN_CLOCK 14
#define PIN_LATCH 0
#define PIN_BUTTON 2
#endif

// disable if you do not want to use the internal storage
// https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/
// timer1 on esp8266 is not compatible with flash file system reads
#ifndef ESP8266
#define ENABLE_STORAGE
#endif

#ifdef ENABLE_SERVER
// https://github.com/nayarsystems/posix_tz_db/blob/master/zones.json
#define NTP_SERVER "de.pool.ntp.org"
#define TZ_INFO "CET-1CEST,M3.5.0,M10.5.0/3"
#endif

#define COLS 16
#define ROWS 16

// set your city or coords (https://github.com/chubin/wttr.in)
#define WEATHER_LOCATION "Zuerich"

// name of WiFi created by the device if no known WiFi is available
#define WIFI_MANAGER_SSID "Ikea Display Setup WiFi"

// use ALL of the following to use static IP config
/*
#define IP_ADDRESS "192.168.0.250"
#define SUBNET "255.255.255.0"
#define DNS1 "1.1.1.1"
#define DNS2 "8.8.8.8"
#define GWY "192.168.0.1"
*/

// ---------------

enum SYSTEM_STATUS
{
  NONE,
  WSBINARY,
  UPDATE,
  LOADING,
  POWEROFF,
};

extern SYSTEM_STATUS currentStatus;