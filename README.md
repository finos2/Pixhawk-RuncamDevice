# Arduino driver for RunCam split cameras
> Small lightweight camera , easy to mount to FC stack , now talking to a onboard AVR

![ RunCam Split 2](/IMG/RCSplit2.png "RunCam")

# The idea
This small camera, with a surprizingly good quality sensor for its price, has exposed a uart interface for communicating to a racing UAV`s Flight computer runing firmware like Betaflight, cleanflight etc. for FPV Racing pilots to control it while this camera is mounted on board the quad without the need of any app . Protocol explained [here](https://support.runcam.com/hc/en-us/articles/360014537794-RunCam-Device-Protocol)

My idea back in 2015 was to package this camera into a go-pro sized 3d printed box, have a arduino comunicate with the Pixhawk , the FC that my copters use , and that i would be able with a few pwm lines not only fully control the camera (menus, start stop rec , photo capture ) from my FrSky Taranis Plus switches  but also be able to send commands like "take picture" from arducopter missions. 
As per 2020 , [folks in ArduPilot have added support](https://github.com/ArduPilot/ardupilot/issues/10103) for this camera right on the firmware, providing [almost all functionality](https://ardupilot.org/copter/docs/common-camera-runcam.html) that i was looking for back in '15 , but for their implementation the copter has to be disarmed to change setings , mine doesnt. 


# Functionality 

The AVR (Atmega328p) runing this Code would have the RunCam device (Split 1,2,4k etc) connected to its hardware uart, running at 115200 baud. 

Then it would have 2 PWM inputs on arduino pin `D2` and `D3`

These 2 PWM inputs would connect to the AUX pwm of the pixhawk , shutter config described [here](https://ardupilot.org/copter/docs/common-camera-shutter-with-servo.html).

The RC1(aka `D2`) would receive the Camera trigger event for a mission for example , then proceed to send the `SimPower` byte array to the RunCam device over serial , that this will trigger the camera to take a picture assuming the camera is in picture mode. 

The RC2(aka `D3`) acts a bit differently. Its what controls the menus . 
In my taranis i have created a mix using 2 switches that allows me to navigate the menus, 
I do this by setting as a natural position of a 3 way swich the center, then when i go to their extremes means that im "pushing" one of the 2 buttons on the camera , (`SimPower` or `SimWiFi`). 
in the physical camera , a long press of the Wifi button changes modes (Photo/Video) here its done using the 3rd command, `Mode`. Alongside my taranis mix.

sounds chaotic but is proven to be very functional to fly with this setup.


# A few words about the RunCam device protocol

```c
byte SimWiFi[] = { 0xCC, 0x01, 0x00, 0x32 };
byte SimPower[]= { 0xCC, 0x01, 0x01, 0xE7 };
byte Mode[]    = { 0xCC, 0x01, 0x02, 0x4D };
byte StartRec[]= { 0xCC, 0x01, 0x03, 0x98 };
byte stopRec[]=  { 0xCC, 0x01, 0x04, 0xCC };
```
the protocol was as follows : 

```
{Header,Command ID,ActionID,crc8}
```
now in 2023 i re-visited runcam's website , the protocol much more elaborate , i dont know if it will work with the modern splits (Split 3, split 4k) ... it should... 