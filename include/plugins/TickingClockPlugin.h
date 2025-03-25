#pragma once

#include "PluginManager.h"
#ifdef BME280INSTALLED
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#endif

#ifdef RTCINSTALLED
#include <RTClib.h>
extern RTC_DS3231 rtc;
extern DateTime rtcTime;
#endif

class TickingClockPlugin : public Plugin
{
private:
    struct tm timeinfo;

    int previousMinutes;
    int previousHour;
    int previousSecond;
/////#ifdef RTCINSTALLED
  ////   rtc;
  /////  DateTime rtcTime;
/////#endif
//#endif

public:
    void setup() override;
    void loop() override;
    bool mytime(struct tm *ti);
    const char *getName() const override;
};
