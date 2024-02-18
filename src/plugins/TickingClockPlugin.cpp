#include "plugins/TickingClockPlugin.h"

bool TickingClockPlugin::mytime(struct tm *ti) {
    uint32_t start = millis();
    while((millis()-start) <= 5000) {
        rtcTime = rtc.now();
        ti->tm_year = rtcTime.year() - 1900;
        ti->tm_mon = rtcTime.month() - 1;
        ti->tm_mday = rtcTime.day();
        ti->tm_hour = rtcTime.hour();
        ti->tm_min = rtcTime.minute();
        ti->tm_sec = rtcTime.second();
        Serial.printf("%d:%d:%d",ti->tm_hour, ti->tm_min, ti->tm_sec);
        Serial.println();
        return true;
    }
    return false;
}

void TickingClockPlugin::setup()
{
  previousMinutes = -1;
  previousHour = -1;
}

void TickingClockPlugin::loop()
{
  if (mytime(&timeinfo))
  {

    if ((timeinfo.tm_hour * 60 + timeinfo.tm_min) < 6 * 60 + 30 ||
        (timeinfo.tm_hour * 60 + timeinfo.tm_min) > 22 * 60 + 30) // only between 6:30 and 22:30
    {
      Screen.clear();
      return;
    }

    if (previousHour != timeinfo.tm_hour || previousMinutes != timeinfo.tm_min)
    {

      std::vector<int> hh = {(timeinfo.tm_hour - timeinfo.tm_hour % 10) / 10, timeinfo.tm_hour % 10};
      std::vector<int> mm = {(timeinfo.tm_min - timeinfo.tm_min % 10) / 10, timeinfo.tm_min % 10};

      Screen.clear();

      Screen.drawCharacter(2, 0, Screen.readBytes(fonts[1].data[hh[0]]), 8); //, Screen.getCurrentBrightness());
      Screen.drawCharacter(9, 0, Screen.readBytes(fonts[1].data[hh[1]]), 8); //, Screen.getCurrentBrightness());
      Screen.drawCharacter(2, 9, Screen.readBytes(fonts[1].data[mm[0]]), 8); //, Screen.getCurrentBrightness());
      Screen.drawCharacter(9, 9, Screen.readBytes(fonts[1].data[mm[1]]), 8); //, Screen.getCurrentBrightness());
      previousMinutes = timeinfo.tm_min;
      previousHour = timeinfo.tm_hour;
    }
    if (previousSecond != timeinfo.tm_sec)
    {
      // clear second lane
      Screen.drawRectangle(0, 7, 16, 2, true, 0);
      // alternating second pixel
      if ((timeinfo.tm_sec * 32 / 60) % 2 == 0)
        Screen.setPixel(timeinfo.tm_sec * 16 / 60, 7, 1, Screen.getCurrentBrightness());
      else
        Screen.setPixel(timeinfo.tm_sec * 16 / 60, 8, 1, Screen.getCurrentBrightness());

      previousSecond = timeinfo.tm_sec;
    }
  }
}

const char *TickingClockPlugin::getName() const
{
  return "Ticking Clock";
}
