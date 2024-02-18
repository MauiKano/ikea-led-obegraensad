#pragma once

#include "PluginManager.h"
#include <RTClib.h>

extern RTC_DS3231 rtc;
extern DateTime rtcTime;

class TickingClockPlugin : public Plugin
{
private:
    struct tm timeinfo;

    int previousMinutes;
    int previousHour;
    int previousSecond;
    //#ifdef RTCINSTALLED
    // RTC_DS3231 rtc;
    // DateTime rtcTime;

//#endif

public:
    void setup() override;
    void loop() override;
    bool mytime(struct tm *ti);
    const char *getName() const override;
};
