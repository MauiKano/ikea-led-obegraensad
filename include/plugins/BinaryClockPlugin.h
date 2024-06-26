#pragma once

#include "PluginManager.h"
#include <RTClib.h>

extern RTC_DS3231 rtc;
extern DateTime rtcTime;

class BinaryClockPlugin : public Plugin
{
private:
  static const uint8_t LED_STATUS_OFF = 0;
  static const uint8_t LED_STATUS_ON = 1;

  struct tm timeinfo;
  int previousMinutes;
  int previousHour;
  int previousSecond;

  void drawBinaryNumber(uint8_t col, uint8_t number);

public:
  void setup() override;
  void loop() override;
  const char *getName() const override;
  bool mytime(struct tm *ti);
};
