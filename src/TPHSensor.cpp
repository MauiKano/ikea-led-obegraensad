#include "TPHSensor.h"
#include <SPI.h>
#include "constants.h"

#ifdef TPHINSTALLED

// Global instance of TandP
TPHSensor tandpandh; /// = TandP::getInstance();

float TPHSensor::getTemperature() {
    readBME280();
    readAHT10();
    temperature = (ahttemperature + bmetemperature) / 2.0;
    return temperature;
}

float TPHSensor::getPressure() {
    readBME280();
    return seaLevelPressure;
}

float TPHSensor::getHumidity() {
    readAHT10();
    return humidity;
}

bool TPHSensor::initTPH() {
    initBME280();
    initAHT10();
    return true;    
}

bool TPHSensor::initBME280() {
   //if (!bme.begin(0x76, 0x55) && !bme.begin(0x77,0x55)) { // Try both common I2C addresses
    if (!bme.begin(0x77, 0x58)) { // Try both common I2C addresses
        // i2c address and ChipID = 0x55 = BMP180, 0x58=BMP280, 0x60=BME280
        Serial.println("BME280 not found! Check wiring.");
        bmeinitialized = false;
        return false;
    }
    bmeinitialized = true;
      // Set BMP280 settings
      //bme.setSampling(Adafruit_BMP280::MODE_NORMAL,   // Continuous mode
        //Adafruit_BMP280::SAMPLING_X2,   // Temperature oversampling
        //Adafruit_BMP280::SAMPLING_X16,  // Pressure oversampling
        //Adafruit_BMP280::FILTER_X16,    // Filtering
        //Adafruit_BMP280::STANDBY_MS_500); // Standby time

    Serial.println("BME280 initialized successfully!");
    return true;
}
bool TPHSensor::initAHT10() {
    //if (!bme.begin(0x76, 0x55) && !bme.begin(0x77,0x55)) { // Try both common I2C addresses
     if (!aht.begin()) { // Try both common I2C addresses
         Serial.println("AHT10 not found! Check wiring.");
         ahtinitialized = false;
         return false;
     }
     ahtinitialized = true;
     Serial.println("AHT10 initialized successfully!");
     return true;
 }

// Function to read temperature, pressure, and humidity
void TPHSensor::readBME280() {
    if (bmeinitialized == true) {
        //temperature = (float) bme.sensorID();
      //temperature = constrain((float) bme.readTemperature(), 0.0, 99.0);
      bmetemperature = bme.readTemperature();
      temperature = (bmetemperature + ahttemperature) / 2.0;
      //pressure = (float) bme.getStatus ();
      //pressure = constrain((float)bme.readPressure()/100.0F, 100.0, 2000.0);
      pressure = bme.readPressure()/100.0F;
      seaLevelPressure = pressure / pow(1.0 - (ALTITUDE / 44330.0), 5.255);
    } else {
       bmetemperature = 13;
       pressure = 1001;
       seaLevelPressure = 1003;
    }
}

void TPHSensor::readAHT10() {
    if (ahtinitialized == true) {
      aht.getEvent(&he, &te);// populate temp and humidity objects with fresh data
      humidity = he.relative_humidity;
      ahttemperature = te.temperature;
      temperature = (bmetemperature + ahttemperature) / 2.0;
    } else {
       ahttemperature = 14;
       humidity = 50;
    }
}

void TPHSensor::readTPH() {
 readBME280();
 readAHT10();
}


// Display adjustments
int upperY = 1;
int midY   = 5;
int lowerY = 9;

void TPHSensor::ShowTempAndPressure(int delayMS) {
    readBME280();
    readAHT10();
    Screen.cacheCurrent();
    Screen.clear();
    temperature = (ahttemperature + bmetemperature) / 2.0;
    int tempInt     = static_cast<int>(round(constrain(temperature, 0.0, 99.0)));  // limit to prevent overflow in display
    int pressureInt = static_cast<int>(constrain(seaLevelPressure, 100.0, 2000.0));
    if (pressureInt >= 1000) {
        pressureInt = pressureInt - 1000;  // only 3 digits can be displayed, => subtract 1000
    }
    
    int tempTens = abs(tempInt) / 10;
    int tempOnes = abs(tempInt) % 10;

    int pressThousands = pressureInt / 1000;
    int pressHundreds = (pressureInt % 1000) / 100;
    int pressTens = (pressureInt % 100) / 10;
    int pressOnes = pressureInt % 10;

    // Display Temperature
    if (tempInt >= 10) {
        Screen.drawCharacter(9, lowerY, Screen.readBytes(degreeSymbol), 4);
        Screen.drawNumbers(1, lowerY, {tempTens, tempOnes});
    } else {
        Screen.drawCharacter(7, lowerY, Screen.readBytes(degreeSymbol), 4);
        Screen.drawNumbers(4, lowerY, {tempOnes});
    }

    Screen.drawNumbers(0, upperY, {pressHundreds, pressTens, pressOnes});
    delay(delayMS);
    Screen.restoreCache();
}

void TPHSensor::ShowPressure(int delayMS) {
    readBME280();
    readAHT10();
    Screen.cacheCurrent();
    Screen.clear();
    int pressureInt = static_cast<int>(constrain(seaLevelPressure, 100.0, 2000.0));
    if (pressureInt >= 1000) {
        pressureInt = pressureInt - 1000;  // only 3 digits can be displayed, => subtract 1000
    }
    
    int pressThousands = pressureInt / 1000;
    int pressHundreds = (pressureInt % 1000) / 100;
    int pressTens = (pressureInt % 100) / 10;
    int pressOnes = pressureInt % 10;

    Screen.drawNumbers(0, midY, {pressThousands, pressHundreds, pressTens, pressOnes});
    delay(delayMS);
    Screen.restoreCache();
}

void TPHSensor::ShowTempAndHumidity(int delayMS) {
    readBME280();
    readAHT10();
    Screen.cacheCurrent();
    Screen.clear();
    temperature = (ahttemperature + bmetemperature) / 2.0;
    int tempInt     = static_cast<int>(round(constrain(temperature, 0.0, 99.0)));  // limit to prevent overflow in display
    int humInt      = static_cast<int>(round(constrain(humidity, 0.0, 99.0)));  // limit to prevent overflow in display
    
    int tempTens = abs(tempInt) / 10;
    int tempOnes = abs(tempInt) % 10;
    int humTens  = abs(humInt) / 10;
    int humOnes  = abs(humInt) % 10; 

    // Display Temperature
    if (tempInt >= 10) {
        Screen.drawCharacter(9, lowerY, Screen.readBytes(degreeSymbol), 4);
        Screen.drawNumbers(1, lowerY, {tempTens, tempOnes});
    } else {
        Screen.drawCharacter(7, lowerY, Screen.readBytes(degreeSymbol), 4);
        Screen.drawNumbers(4, upperY, {tempOnes});
    }

// Display Humidity
    if (humInt >= 10) {
        Screen.drawCharacter(11, upperY, Screen.readBytes(percentSymbol), 8);
        Screen.drawNumbers(1, upperY, {humTens, humOnes});
    } else {
        Screen.drawCharacter(11, upperY, Screen.readBytes(percentSymbol), 8);
        //Screen.drawCharacter(9, tempY, Screen.readBytes(percentSymbol), 4, 50);
        Screen.drawNumbers(4, upperY, {humOnes});
    }
    delay(delayMS);
    Screen.restoreCache();
}

// HTTP request handler
void handleTemperature(AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(tandpandh.getTemperature(), 2) + "\n");
}

void handlePressure(AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(tandpandh.getPressure(), 2) + "\n");
}

void handleHumidity(AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(tandpandh.getHumidity(), 2) + "\n");
}

#endif