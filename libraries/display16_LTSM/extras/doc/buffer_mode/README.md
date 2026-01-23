# Advanced Buffer Mode Readme

**This mode is only for high RAM MCUs.**

Advanced buffer mode allows the library to write to a global screen buffer (`screenBuffer`) instead of directly writing to the VRAM of the display. This mode is off by default but can be enabled for specific use cases where buffering is advantageous. ScreenBuffer is a Vector.

Advanced buffer mode offers several key benefits. It enables double buffering, where all drawing operations are first performed in memory and then written to the display in a single operation. With batch drawing, multiple graphics operations can be completed before updating the screen, improving rendering efficiency. The memory-resident buffer also allows for custom effects like fading or blending to be applied before display. Additionally, since memory operations are faster than direct display writes, this approach leads to optimized performance for applications with frequent updates.

However, it comes with limitations. It requires significant heap memory and flushing the buffer to the display can introduce a performance overhead. Compatibility is also a concern on memory-constrained devices. Use advanced buffer mode when you need complex rendering, visual effects, or performance optimizations. For simpler applications where memory is limited, direct display drawing may be more suitable. Bear in mind many functions in normal mode have some form of local buffered writes already.

Size of buffer required.

| Display size | bytes |
| ---- | --- |
| 96x64  |12,288 |
| 240x320| 153,600|

Whether your MCU can use this mode 
will depend on size of display and the available heap SRAM memory of your MCU + program
This table (figures are approximations) give some indication. Some examples of SRAM usage for selected display sizes.

| MCU | Total SRAM | Usable for Framebuffer (safe) | Max Resol (safe) |
|------------|------|---------|------------|
| Uno/Nano (ATmega328P)| 2 KB   | ~1 KB  | ~22×22   |
| Arduino Mega 2560     | 8 KB       | ~6 KB       | ~55×55  |
| Arduino Uno R4 | 32 KB      | ~24 KB    | ~109×109 |
| ESP8266     | 80 KB      | ~50 KB    | ~158×158  |
| ESP32      | 320 KB     | ~200 KB   | ~316×316|
| RP2040 (Raspberry Pi Pico)| 264 KB     | ~200 KB  | ~316×316  |
| STM32 “Blue Pill” (F103) | 20 KB      | ~14 KB   | ~83×83  |


## Enabling Advanced Buffer Mode

To enable advanced buffer mode, you need to define the macro `dislib16_ADVANCED_SCREEN_BUFFER_ENABLE`. This macro is located in the file `display16_common_LTSM.hpp` (USER OPTION 2). By default, this macro is commented out or undefined. Once enabled, the library will use the `screenBuffer` for many drawing operations instead of writing directly to the display VRAM.

## Usage

1. setBuffer, sets the buffer allocates memory for a buffer to cover entire screen, call at setup of Display operations.
2. destroyBuffer, destroys buffer de-allocates memory, call at end of Display operations.
3. clearBuffer, fills buffer with a colour, by default black.
4. writeBuffer, writes buffer in a single SPI buffered write to screen.

## Functions

Once enabled The following functions will write to screen Buffer instead of 
VRAM of display.

1. drawPixel()
2. All Bitmap functions.
3. All Draw text functions only IF **textCharPixelOrBuffer = true** 

The situation with graphic functions is complicated as some use 
fast draw methods of drawFastVLine() and drawFastHLine().
and fillRectBuffer uses a local buffer in function to write to display VRAM.
So depending on the graphic function code may write to screenBuffer and/or VRAM. 
Note fillRectBuffer is wrapped by fillScreen. 

## Examples

There are examples downstream in driver libraries for Advanced buffer mode. There are called "FRAME BUFFER.ino".
