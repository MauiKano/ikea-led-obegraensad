#pragma once

#include "screen.h"

#ifdef BME280INSTALLED
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

class TandP
{

private:
  Adafruit_BMP280 bme;
  float temperature;
  float pressure;
  float seaLevelPressure;
  bool  initialized = false;

public:
  TandP() = default;
  static TandP &getInstance();
  void readBME280(); 
  bool initBME280();
  void ShowTempAndPressure() ;
  float getTemperature();
  float getPressure();
};

extern  TandP tandp;

void handleTemperature(AsyncWebServerRequest *request);
void handlePressure(AsyncWebServerRequest *request);

#endif