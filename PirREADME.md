# This describes the add-on of a PIR sensor for the IKEA OBEGRÄNSAD Hack/Mod

The IKEA OBEGRÄNSAD LED Wall Lamp and the great Hack/Mod from https://github.com/MauiKano/ikea-led-obegraensad/tree/main/3dp is switched-on as soon as it is connected to the power, e.g. it does not have a on/off switch. Instead of just adding a simple switch I did add a PIR motion sensor. With this mod the LED WAll Lamp turns on maximum brightness if a motion (or person) in its field of sight is detected. After a configurable periode of time it dims to minimal brightness. 


<img src="https://github.com/MauiKano/ikea-led-obegraensad/blob/main/3dp/PirMountPic4.png" width="60%" />



## Features

- uses a second hw_timer of the ESP
- uses one more GPIP port
- uses the widely and cheap available PIR sensor SR602. This sensor requires GND, VCC (5V works well) and has a 0/3.3V output that directly connects to a GPIO
- a simple STL model for 3D print of a sensor mount is provided
- only a few software modifications are needed. Basically on motion detection the brightness is turned on and a timer is started. Once the timer triggers, is ISR is called that reduces the brigness to a minimum.
