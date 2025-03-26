#pragma once

#include "screen.h"

#ifdef TPHINSTALLED
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

class  TPHSensor
{

private:
  Adafruit_BMP280 bme;
  Adafruit_AHTX0 aht;
  sensors_event_t he, te;
  float temperature;
  float bmetemperature;
  float ahttemperature;
  float pressure;
  float seaLevelPressure;
  float humidity;
  bool  bmeinitialized = false;
  bool  ahtinitialized = false;

public:

  static TPHSensor &getInstance();
  bool  initTPH(); 
  bool  initBME280();
  void  readBME280(); 
  bool  initAHT10();
  void  readAHT10(); 
  void  readTPH(); 
  void  ShowPressure(int delayMS) ;
  void  ShowTempAndPressure(int delayMS) ;
  void  ShowTempAndHumidity(int delayMS);
  float getTemperature();
  float getPressure();
  float getHumidity();
};

extern  TPHSensor tandpandh;

void handleTemperature(AsyncWebServerRequest *request);
void handlePressure(AsyncWebServerRequest *request);
void handleHumidity(AsyncWebServerRequest *request);

#endif