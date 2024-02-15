#pragma once

#include "PluginManager.h"
#include <RTClib.h>

class TickingSmallClockPlugin : public Plugin
{
private:
  struct tm timeinfo;

  int previousMinutes;
  int previousHour;
  int previousSecond;

//#ifdef RTCINSTALLED
RTC_DS3231 rtc;
//#endif

public:
  void setup() override;
  void loop() override;
  void mytime(tm *ti);

  const char *getName() const override;
};