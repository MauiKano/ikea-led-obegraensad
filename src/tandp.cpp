#include "tandp.h"
#include <SPI.h>
#include "constants.h"

#ifdef BME280INSTALLED

// Global instance of TandP
TandP tandp; /// = TandP::getInstance();

float TandP::getTemperature() {
    readBME280();
    return temperature;
}

float TandP::getPressure() {
    readBME280();
    return seaLevelPressure;
}


bool TandP::initBME280() {
   //if (!bme.begin(0x76, 0x55) && !bme.begin(0x77,0x55)) { // Try both common I2C addresses
    if (!bme.begin(0x76, 0x58)) { // Try both common I2C addresses
        // i2c address and ChipID = 0x55 = BMP180, 0x58=BMP280, 0x60=BME280
        Serial.println("BME280 not found! Check wiring.");
        initialized = false;
        return false;
    }
    initialized = true;
      // Set BMP280 settings
      //bme.setSampling(Adafruit_BMP280::MODE_NORMAL,   // Continuous mode
        //Adafruit_BMP280::SAMPLING_X2,   // Temperature oversampling
        //Adafruit_BMP280::SAMPLING_X16,  // Pressure oversampling
        //Adafruit_BMP280::FILTER_X16,    // Filtering
        //Adafruit_BMP280::STANDBY_MS_500); // Standby time

    Serial.println("BME280 initialized successfully!");
    return true;
}

// Function to read temperature, pressure, and humidity
void TandP::readBME280() {
    if (initialized == true) {
        //temperature = (float) bme.sensorID();
      //temperature = constrain((float) bme.readTemperature(), 0.0, 99.0);
      temperature = bme.readTemperature();
      //pressure = (float) bme.getStatus ();
      //pressure = constrain((float)bme.readPressure()/100.0F, 100.0, 2000.0);
      pressure = bme.readPressure()/100.0F;
      seaLevelPressure = pressure / pow(1.0 - (ALTITUDE / 44330.0), 5.255);
    } else {
       temperature = 13;
       pressure = 1001;
       seaLevelPressure = 1003;
    }
}

// Display adjustments
int pressY = 1;
int tempY = 9;

void TandP::ShowTempAndPressure() {
    readBME280();

    int tempInt     = static_cast<int>(constrain(temperature, 0.0, 99.0));  // limit to prevent overflow in display
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
        Screen.drawCharacter(9, tempY, Screen.readBytes(degreeSymbol), 4, 50);
        Screen.drawNumbers(1, tempY, {tempTens, tempOnes});
    } else {
        Screen.drawCharacter(7, tempY, Screen.readBytes(degreeSymbol), 4, 50);
        Screen.drawNumbers(4, tempY, {tempOnes});
    }

    // Display Pressure
    //Screen.drawNumbers(0, pressY, {pressThousands, pressHundreds, pressTens, pressOnes});
    Screen.drawNumbers(0, pressY, {pressHundreds, pressTens, pressOnes});
}

// HTTP request handler
void handleTemperature(AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(tandp.getTemperature(), 2) + "\n");
}

void handlePressure(AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(tandp.getPressure(), 2) + "\n");
}

#endif