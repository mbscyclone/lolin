[![Website](https://img.shields.io/badge/Website-Link-blue.svg)](https://gavinlyonsrepo.github.io/)  [![Rss](https://img.shields.io/badge/Subscribe-RSS-yellow.svg)](https://gavinlyonsrepo.github.io//feed.xml)  [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme/whitelight976)

# display16_LTSM Readme

## Table of contents

  * [Overview](#overview)
  * [Installation](#installation)
  * [Documentation](#documentation)
    * [Supported devices](#supported-devices)
    * [API documentation](#api-documentation)
    * [Fonts](#fonts)
  * [Software](#software)
    * [Advanced Graphics](#advanced-graphics)
    * [Advanced buffer mode](#Advanced-buffer-mode)
    * [Debug mode](#debug-mode)
    * [File-system](#file-system)
    * [Error Codes](#error-codes)
  * [Notes](#notes)

## Overview

* Name : display16_LTSM
* Title : Graphics Library for 16-bit color graphic displays for Arduino eco-system.
* Description :

0. C++ Library to support 16-bit color graphic displays
1. Graphics class included.
2. Bitmaps supported: 1, 8, and 16 bit + sprites.
3. Multiple displays supported, see supported-devices, new components can be easily added.
    Display driver are separate libraries that import this one.
4. 16 fonts included, new fonts can be easily added without changing source code
5. [URL project github link](https://github.com/gavinlyonsrepo/display16_LTSM)

* Author: Gavin Lyons


## Installation

The library is included in the official Arduino library manger and the optimum way to install it is using the library manager which can be opened by the *manage libraries* option in Arduino IDE. 

## Documentation

### Supported devices

Component drivers are separate dependent downstream libraries that include this library.

| Component name | Type | Interface | Readme URL link |
| -------- | ---------- | --------- | ---------- |
| ST7735 | TFT LCD|SPI HW & SW| [github link](https://github.com/gavinlyonsrepo/ST7735_LTSM)|
| ST7789 | TFT LCD|SPI HW & SW| [github link](https://github.com/gavinlyonsrepo/ST7789_LTSM)|
| SSD1331| OLED |SPI HW & SW  | [github link](https://github.com/gavinlyonsrepo/SSD1331_LTSM)|
| ILI9341 | TFT LCD |SPI HW & SW  | [github link](https://github.com/gavinlyonsrepo/ILI9341_LTSM)|
| GC9A01 | TFT LCD |SPI HW & SW  | [github link](https://github.com/gavinlyonsrepo/GC9A01_LTSM)|

### API Documentation

Code is commented for doxygen API documentation software.

### Fonts

The font system readme is in the 'doc' folder [at link.](extras/doc/fonts/README.md)

## Software

### Advanced Graphics

There is an advanced graphics modes in library.
Standard graphics supports drawing lines, pixels
rectangles, triangles, circles and rounded rectangles.
Advanced graphics supports drawing polygons, dot grid, quadrilaterals, 
arcs, ellipses and lines at an angle.
It is **OFF** by default.
If you want these 'advanced' functions, simply 
comment in define dislib16 ADVANCED GRAPHICS ENABLE in display16 common LTSM.hpp. 
This will enable advanced graphics mode. If this is disabled some examples 
may not work fully or even compile. 

### Advanced buffer mode

Advanced buffer mode. There is advanced buffer mode where the code writes to a global screen buffer instead of the VRAM of display. It is **OFF** by default more details at readme, 
which is in the 'doc' folder [at link.](extras/doc/buffer_mode/README.md)
**This mode is only for high RAM MCUs.**

### Debug Mode 

This is **OFF** by default
If debug mode is enabled: error messages, warnings & important information is sent to serial monitor.
User ino file must enable serial port. To enable simply 
comment in define dislib16 DEBUG MODE ENABLE in file display16 common LTSM.hpp.


### File system

File system Hierarchy:

[![ pic ](https://github.com/gavinlyonsrepo/display16_LTSM/blob/main/extras/images/filesystem.jpg)](https://github.com/gavinlyonsrepo/display16_LTSM/blob/main/extras/images/filesystem.jpg) 

### Error Codes 

Most functions that return a value, return a enum. 
Zero for success and a positive number for an error code. 
The enum is in file: display16 common LTSM.hpp.

## Notes
