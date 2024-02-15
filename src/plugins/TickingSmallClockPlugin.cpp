#include "plugins/TickingSmallClockPlugin.h"

// Function to get current time from either Internet or RTC
/*
tm TickingSmallClockPlugin::mytime() {
  tm timeinfo;
  if (WiFi.status() == WL_CONNECTED && getLocalTime(&timeinfo)) {
    // Time from Internet
    return timeinfo;
  } else {
    // Fallback to RTC
    DateTime rtcTime = rtc.now();
    timeinfo.tm_year = rtcTime.year() - 1900;
    timeinfo.tm_mon = rtcTime.month() - 1;
    timeinfo.tm_mday = rtcTime.day();
    timeinfo.tm_hour = rtcTime.hour();
    timeinfo.tm_min = rtcTime.minute();
    timeinfo.tm_sec = rtcTime.second();
    return timeinfo;
  }
}
*/
void TickingSmallClockPlugin::mytime(tm *ti) {

    // Fallback to RTC
    DateTime rtcTime = rtc.now();
    ti->tm_year = rtcTime.year() - 1900;
    ti->tm_mon = rtcTime.month() - 1;
    ti->tm_mday = rtcTime.day();
    ti->tm_hour = rtcTime.hour();
    ti->tm_min = rtcTime.minute();
    ti->tm_sec = rtcTime.second();
}

void TickingSmallClockPlugin::setup()
{
  // loading screen
  Screen.setPixel(4, 7, 1);
  Screen.setPixel(5, 7, 1);
  Screen.setPixel(7, 7, 1);
  Screen.setPixel(8, 7, 1);
  Screen.setPixel(10, 7, 1);
  Screen.setPixel(11, 7, 1);

  previousMinutes = -1;
  previousHour = -1;

   // #ifdef RTCINSTALLED
 // SETUP RTC MODULE
  if (! rtc.begin()) {
    Serial.println("RTC module is NOT found");
    Serial.flush();
    while (1);
  }
  // automatically sets the RTC to the date & time on PC this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//#endif

}

int XPosSeconds(int s) {
  int x;
  if (s < 8) {
    x = 8 + s; // move right on the upper border
  } else if (s < 23) {
     x = 15;  // stay on the right border
  } else if (s < 38) {
     x = 15 - (s - 22); // move left on the lower border
  } else if (s < 53) {
     x = 0;  // stay on the left border
  } else {
    x = s - 52;
  }
 return x;
}

int YPosSeconds(int s) {
  int y;
  if (s < 8) {
    y = 0;  // stay on the upper border
  } else if (s < 23) {
    y = s - 7; // move down on the right border
  } else if (s < 38) {
    y = 15; // stay on the bottom border
  } else if (s < 53) {
    y = 15 - (s - 37);  // move up on the right border
  } else { 
    y = 0;  // stay on the upper border
  }
 return y;
}

void TickingSmallClockPlugin::loop()
{
  mytime(&timeinfo);
  if (true)
 //   if (getLocalTime(&timeinfo))

  {
    if (previousHour != timeinfo.tm_hour || previousMinutes != timeinfo.tm_min)
    {
      Screen.clear();
      Screen.drawNumbers(3, 2, {(timeinfo.tm_hour - timeinfo.tm_hour % 10) / 10, timeinfo.tm_hour % 10},128);
      Screen.drawNumbers(3, 8, {(timeinfo.tm_min - timeinfo.tm_min % 10) / 10, timeinfo.tm_min % 10}),128;
      previousMinutes = timeinfo.tm_min;
      previousHour = timeinfo.tm_hour;
    }

    if(previousSecond != timeinfo.tm_sec){
      // clear prevous one
       Screen.setPixel(XPosSeconds(previousSecond),
                         YPosSeconds(previousSecond), 
                         1,
                         0);
      // set new one
         Screen.setPixel(XPosSeconds(timeinfo.tm_sec),
                         YPosSeconds(timeinfo.tm_sec), 
                         1,
          //               Screen.getCurrentBrightness());
                         255);

      previousSecond =  timeinfo.tm_sec;
    }
  }
}

const char *TickingSmallClockPlugin::getName() const
{
  return "Ticking Small Clock";
}
