#include "plugins/BinaryClockPlugin.h"

#ifdef RTCINSTALLED
bool BinaryClockPlugin::mytime(struct tm *ti) {
    uint32_t start = millis();
    while((millis()-start) <= 5000) {
        rtcTime = rtc.now();
        ti->tm_year = rtcTime.year() - 1900;
        ti->tm_mon = rtcTime.month() - 1;
        ti->tm_mday = rtcTime.day();
        ti->tm_hour = rtcTime.hour();
        ti->tm_min = rtcTime.minute();
        ti->tm_sec = rtcTime.second();
   //     Serial.printf("%d:%d:%d",ti->tm_hour, ti->tm_min, ti->tm_sec);
   //     Serial.println();
        return true;
    }
    return false;
}
#endif

void BinaryClockPlugin::setup()
{
  previousHour = -1;
  previousMinutes = -1;
  previousSecond = -1;
}

void BinaryClockPlugin::loop()
{
 //// if (mytime(&timeinfo))
  if (getLocalTime(&timeinfo))

  {
    if (previousMinutes != timeinfo.tm_sec || previousMinutes != timeinfo.tm_min || previousHour != timeinfo.tm_hour)
    {
      Screen.clear();

      drawBinaryNumber(0, timeinfo.tm_hour);
      drawBinaryNumber(1, timeinfo.tm_min);
      drawBinaryNumber(2, timeinfo.tm_sec);

      previousHour = timeinfo.tm_hour;
      previousMinutes = timeinfo.tm_min;
      previousSecond = timeinfo.tm_sec;
    }

  }
}

void BinaryClockPlugin::drawBinaryNumber(uint8_t col, uint8_t number)
{
    if (col > 2)
    {
        col = 2;
    }

    if (number > 60)
    {
        number = 60;
    }

    auto isBitSet =[](uint8_t number, uint8_t bitIndex)
    {
        return number & (1 << bitIndex);
    };

    int x = 0;
    int y = 0;
    for (unsigned char bitIndex = 0; bitIndex < 6; bitIndex++)
    {
        if (isBitSet(number, bitIndex))
        {
            x = 1;
            x += (bitIndex % 2 == 0) ? 2 : 0;
            x += col * 5;

            y = 1;
            y += 5 * (2 - bitIndex / 2);

            Screen.drawRectangle(x, y, 2, 4, true, BinaryClockPlugin::LED_STATUS_ON);
        }
    }
}

const char *BinaryClockPlugin::getName() const
{
  return "Binary Clock";
}
