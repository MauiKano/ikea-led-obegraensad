#pragma once

#include "PluginManager.h"

class TickingSmallClockPlugin : public Plugin
{
private:
  struct tm timeinfo;

  int previousMinutes;
  int previousHour;
  int previousSecond;


public:
  void setup() override;
  void loop() override;
  const char *getName() const override;
};