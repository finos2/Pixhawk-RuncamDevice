# RunCam Device Protocol

|Header|Command ID|Action ID|crc8|
|-|-|-|-|
|0xCC|0x01|Please refer to the 'Action' section for specific values|Check code|


## Action ##

| Action                                   | Value | Description                           |
|------------------------------------------|-------|---------------------------------------|
| RCDEVICE_PROTOCOL_SIMULATE_WIFI_BTN      | 0x00  | Simulation Click the Wi-Fi button     |
| RCDEVICE_PROTOCOL_SIMULATE_POWER_BTN     | 0x01  | Simulation Click the Power button     |
| RCDEVICE_PROTOCOL_CHANGE_MODE            | 0x02  | Switch the camera mode                |
| RCDEVICE_PROTOCOL_CHANGE_START_RECORDING | 0x03  | Control the camera to start recording |
| RCDEVICE_PROTOCOL_CHANGE_STOP_RECORDING  | 0x04  | Control the camera to stop recording  |

## CRC-8 calculatation

```c
uint8_t crc8_dvb_s2(uint8_t crc, unsigned char a)
{
    crc ^= a;
    for (int ii = 0; ii < 8; ++ii) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ 0xD5;
        } else {
            crc = crc << 1;
        }
    }

    return crc;
}
```
> to calculate the CRC8_dvb_S2 you call the funtion n times, once for each byte in the array. 

eg.:

```c
#include <stdio.h>
#include <stdint.h>

uint8_t crc8_dvb_s2(uint8_t crc, unsigned char a);

unsigned char data[] = {0x00, 0x01, 0x00};

int main()
{
    
    int len = sizeof(data) / sizeof(data[0]);
    uint8_t crc = 0x00;
    for (int i = 0; i < len; i++) {
        crc = crc8_dvb_s2(crc, data[i]);
    }
    printf("CRC-8: 0x%02X\n", crc);
    
    return 0;
}
```
