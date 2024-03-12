#pragma once

#include "PluginManager.h"
#ifdef RTCINSTALLED
#include <RTClib.h>
#endif

#ifdef RTCINSTALLED
extern RTC_DS3231 rtc;
extern DateTime rtcTime;
#endif

class TickingSmallClockPlugin : public Plugin
{
private:
  struct tm timeinfo;

  int previousMinutes;
  int previousHour;
  int previousSecond;

//////#ifdef RTCINSTALLED
  /////RTC_DS3231 rtc;
  ////DateTime rtcTime;
/////#endif

public:
  void setup() override;
  void loop() override;
  bool mytime(struct tm *ti);

  const char *getName() const override;
};