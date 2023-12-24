#include "plugins/BlankPlugin.h"


 void BlankPlugin::setup()
 {
     // loading screen
     Screen.clear();
     currentStatus = NONE;
 }

 void BlankPlugin::loop()
 {/*
     Screen.clear();
     Screen.setBrightness(0);  // dim the screen after  the timer expired
     delay(100);
     */
 }

 void BlankPlugin::update()
 {
 }

 const char *BlankPlugin::getName() const
 {
     return "Blank";
 }
