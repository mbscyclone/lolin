/*! 
	@file     bare_bones.ino
	@brief    bare bones example sketch,
	@details  Working Examples .ino are created to demonstrate 
						the use of the Display16_LTSM library, 
						in the driver libraries that import this library. 
						See Main readme for more details.
*/

// === 1. Library, the display driver will include everything needed  ===
// #include "ST7735_LTSM.hpp"
// #include "ST7789_LTSM.hpp"
// #include "SSD1331_LTSM.hpp"
// #include "ILI9341_LTSM.hpp"
// #include "GC9A01_LTSM.hpp"

// ====

// === 2. Included Fonts all are optional except Default, which library already includes.===
// #include <fonts_LTSM/FontArialBold_LTSM.hpp>
// #include <fonts_LTSM/FontArialRound_LTSM.hpp>
// #include <fonts_LTSM/FontDefault_LTSM.hpp>
// #include <fonts_LTSM/FontGll_LTSM.hpp>
// #include <fonts_LTSM/FontGroTeskBig_LTSM.hpp>
// #include <fonts_LTSM/FontGroTesk_LTSM.hpp>
// #include <fonts_LTSM/FontHallfetica_LTSM.hpp>
// #include <fonts_LTSM/FontInconsola_LTSM.hpp>
// #include <fonts_LTSM/FontMega_LTSM.hpp>
// #include <fonts_LTSM/FontMint_LTSM.hpp>
// #include <fonts_LTSM/FontOrla_LTSM.hpp>
// #include <fonts_LTSM/FontPico_LTSM.hpp>
// #include <fonts_LTSM/FontRetro_LTSM.hpp>
// #include <fonts_LTSM/FontSevenSeg_LTSM.hpp>
// #include <fonts_LTSM/FontSinclairS_LTSM.hpp>
// #include <fonts_LTSM/FontSixteenSeg_LTSM.hpp>
// ===

// === 3. Included Bitmap test data files, optional just for testing ===
// #include "bitmap_test_data_LTSM/Bitmap_TEST_Data_16color1.hpp"
// #include "bitmap_test_data_LTSM/Bitmap_TEST_Data_16color2.hpp"
// #include "bitmap_test_data_LTSM/Bitmap_TEST_Data_8color.hpp"
// #include "bitmap_test_data_LTSM/Bitmap_TEST_Data_bicolor.hpp"
// ===

// === 4. Check User options optional ===
#ifdef dislib16_ADVANCED_GRAPHICS_ENABLE
#pragma message("gll: dislib16_ADVANCED_GRAPHICS_ENABLE is defined.")
#endif
#ifdef dislib16_ADVANCED_SCREEN_BUFFER_ENABLE
#pragma message("gll: dislib16_ADVANCED_SCREEN_BUFFER_ENABLE is defined. ")
#endif
#ifdef dislib16_DEBUG_MODE_ENABLE
#pragma message("gll: ddislib16_DEBUG_MODE_ENABLE is defined.")
#endif

// ===

void setup() {
	// put your driver setup code here, to run once:

}

void loop() {
	// put your main code here, to run repeatedly:

}