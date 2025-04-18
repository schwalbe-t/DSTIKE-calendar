# DSTIKE-calendar 

Turn your DSTIKE Deauther Watch into a calendar smart watch. 

### Customization

Currently, to customize the schedule and known networks, source files have to be edited directly:
- `watch/src/calendar.cpp` - NTP server, time zone and schedule items
- `watch/src/wifi.cpp` - List of known networks

### Building

This project can be built using PlatformIO.
If you have the PlatformIO CLI installed, run the following command in the `watch`-directory with full priviliges (admin cmd instance, `sudo`, ...), to install the firmware on a watch connected via USB:
```
platformio run -t upload
```