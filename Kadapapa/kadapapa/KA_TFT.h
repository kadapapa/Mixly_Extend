#ifndef __KA_TFT_H_
#define __KA_TFT_H_

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "utility/SPI.h"

#include "KA_Port.h"

/******************************************************************
 This is the core graphics library for all our displays, providing
 basic graphics primitives (points, lines, circles, etc.). It needs
 to be paired with a hardware-specific library for each display
 device we carry (handling the lower-level functions).
 
 KA_TFT invests time and resources providing this open
 source code, please support KA_TFT and open-source hardware
 by purchasing products from KA_TFT!
 
 Written by Limor Fried/Ladyada for KA_TFT Industries.
 Processing-like API written by Enrico Gueli for Officine Arduino.
 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.
 ******************************************************************/

/*
 * This library can work with or without the presence of an SD
 * reading library (to load images). At the moment, only the
 * Arduino SD library is supported; it is included in
 * standard Arduino libraries.
 * 
 * The presence of the SD library is detected by looking at the
 * __SD_H__ preprocessor variable, defined into 
 * Arduino SD library to avoid double inclusion. This means
 * that in order to use the image-related API of KA_TFT_GFX,
 * SD.h *must* be included before KA_TFT_GFX.
 * 
 * The bottom part of this include file contains the actual image
 * loading code; if it was in a separate .cpp file, there were no
 * way to check if the SD library was present or not.
 * 
 * A partial solution was to include SD.h anyway, see if that works
 * (i.e. it is found in the include search path) and act accordingly.
 * But this solution relied on the preprocessor to issue only a
 * warning when an include file is not found. Avr-gcc, used for
 * Arduino 8-bit MCUs, does that, but the standard gcc-4.4, used for
 * Arduino Due, issues a fatal error and stops compilation.
 * 
 * The best solution so far is to put the code here. It works if this
 * include is used only in one .cpp file in the build (this is the
 * case of most Arduino sketches); if used in multiple .cpp files,
 * the linker may complain about duplicate definitions.
 * 
 */ 
 
#if ARDUINO >= 100
	#include "Arduino.h"
	#include "Print.h"
#else
	#include "WProgram.h"
#endif

#define swap(a, b) { int16_t t = a; a = b; b = t; }

typedef uint16_t color;

class KA_TFT_GF: public Print {
	public:

	KA_TFT_GF(int16_t w, int16_t h); // Constructor

#if ARDUINO >= 100
	virtual size_t write(uint8_t);
#else
	virtual void   write(uint8_t);
#endif

	// This MUST be defined by the subclass
	virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;

	// These MAY be overridden by the subclass to provide device-specific
	// optimized code.  Otherwise 'generic' versions are used.
	virtual void 
		drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color),//绘制线段
		drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),//绘制垂直线
		drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),//绘制水平线
		drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),//绘制矩形
		fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),//填充矩形
		fillScreen(uint16_t color),//整屏填充
		invertDisplay(boolean i);//颜色反相

	// These exist only with KA_TFT_GFX (no subclass overrides)
	void
		drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),//绘制圆形
		fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),//填充圆形
		drawCircleHelper(int16_t x0, int16_t y0,int16_t r, uint8_t cornername, uint16_t color),//绘制弧形（cornername参数不详）
		fillCircleHelper(int16_t x0, int16_t y0, int16_t r,uint8_t cornername, int16_t delta, uint16_t color),//填充弧形（cornername 和 delta 参数不详 绘制图形不规则）
		drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color),//绘制三角形
		fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color),//填充三角形
		drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color),//绘制圆角矩形（代码与实际不符）
		fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color),//填充圆角矩形（代码与实际不符）
		drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h,uint16_t color),
		drawChar(int16_t x, int16_t y, unsigned char c,uint16_t color, uint16_t bg, uint8_t size),//绘制字符（c为ASCII bg为背景）
		setCursor(int16_t x, int16_t y),//设置光标
		setTextColor(uint16_t c),//设置字文字颜色
		setTextColor(uint16_t c, uint16_t bg),//设置文字颜色，背景
		setTextSize(uint8_t s),//设置文字字体
		setTextWrap(boolean w),
		setRotation(uint8_t r);//旋转屏幕

	int16_t height(void),width(void);
	uint8_t getRotation(void);
  
	/*
	* Processing-like graphics primitives
	*/
  
	/// transforms a color in 16-bit form given the RGB components.
	/// The default implementation makes a 5-bit red, a 6-bit
	/// green and a 5-bit blue (MSB to LSB). Devices that use
	/// different scheme should override this. 
	virtual uint16_t newColor(uint8_t red, uint8_t green, uint8_t blue);
   
	void
		// http://processing.org/reference/background_.html		
		background(uint8_t red, uint8_t green, uint8_t blue),
		background(color c),//设置背景

		// http://processing.org/reference/fill_.html		
		fill(uint8_t red, uint8_t green, uint8_t blue),
		fill(color c), //填充 在绘制图形前加此函数

		// http://processing.org/reference/noFill_.html		
		noFill(),//取消填充 在绘制图形前加此函数

		// http://processing.org/reference/stroke_.html
		stroke(uint8_t red, uint8_t green, uint8_t blue),
		stroke(color c),//绘制 在绘制图形前加此函数

		// http://processing.org/reference/noStroke_.html
		noStroke(),//取消绘制 在绘制图形前加此函数
	  
		text(int16_t x, int16_t y, uint8_t s,uint16_t color,uint16_t bgcolor,String text),	
		text(const char * text, int16_t x, int16_t y),//添加字符串
				
		textWrap(const char * text, int16_t x, int16_t y),

		textSize(uint8_t size),
	  
		// similar to ellipse() in Processing, but with
		// a single radius.
		// http://processing.org/reference/ellipse_.html
		circle(int16_t x, int16_t y, int16_t r),//绘制圆形
		point(int16_t x, int16_t y),//绘制点
		line(int16_t x1, int16_t y1, int16_t x2, int16_t y2),//绘制线
		quad(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, int16_t x4, int16_t y4),//绘制方形
		rect(int16_t x, int16_t y, int16_t width, int16_t height),//绘制矩形
		rect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t radius),//绘制圆角矩形
		triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3);//绘制三角形
		 
protected:

	int16_t WIDTH, HEIGHT;   // this is the 'raw' display w/h - never changes	
	int16_t _width, _height,cursor_x, cursor_y; // dependent on rotation		
	uint16_t textcolor, textbgcolor;	
	uint8_t textsize,rotation;	
	boolean wrap; // If set, 'wrap' text at right edge of display

	/*
	* Processing-style graphics state
	*/
	
	color strokeColor;	
	bool useStroke;	
	color fillColor;	
	bool useFill;		

	const char cover = 218;
//	uint8_t textlength;
//	uint8_t old_textlength;
	
};


/***************************************************
  This is a library for the KA_TFT 1.8" SPI display.
  This library works with the KA_TFT 1.8" TFT Breakout w/SD card
  ----> http://www.KA_TFT.com/products/358
  as well as KA_TFT raw 1.8" TFT display
  ----> http://www.KA_TFT.com/products/618
 
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  KA_TFT invests time and resources providing this open source code,
  please support KA_TFT and open-source hardware by purchasing
  products from KA_TFT!

  Written by Limor Fried/Ladyada for KA_TFT Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "WProgram.h"
#endif
#include <avr/pgmspace.h>

// some flags for initR() :(
#define INITR_GREENTAB 0x0
#define INITR_REDTAB   0x1
#define INITR_BLACKTAB   0x2

#define ST7735_TFTWIDTH  130
#define ST7735_TFTHEIGHT 160

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// Color definitions
#define	ST7735_BLACK   0x0000
#define	ST7735_BLUE    0x001F
#define	ST7735_RED     0xF800
#define	ST7735_GREEN   0x07E0
#define ST7735_CYAN    0x07FF
#define ST7735_MAGENTA 0xF81F
#define ST7735_YELLOW  0xFFE0  
#define ST7735_WHITE   0xFFFF


class KA_TFT_ST7735 : public KA_TFT_GF {

public:

	KA_TFT_ST7735();
	void TFTbegin(uint8_t cs,uint8_t rs); 
	void     
		initB(void),                             // for ST7735B displays
		initG(void),                             // for ILI9163C displays
		initR(uint8_t options = INITR_GREENTAB), // for ST7735R
		setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1),
		pushColor(uint16_t color),
		fillScreen(uint16_t color),
		drawPixel(int16_t x, int16_t y, uint16_t color),
		drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
		drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
		fillRect(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color),
		setRotation(uint8_t r),
		invertDisplay(boolean i);
	uint16_t Color565(uint8_t r, uint8_t g, uint8_t b) { return newColor(r, g, b);}
  
	/* These are not for current use, 8-bit protocol only!
	uint8_t  readdata(void),
	readcommand8(uint8_t);
	uint16_t readcommand16(uint8_t);
	uint32_t readcommand32(uint8_t);
	void     dummyclock(void);
	*/

private:
	uint8_t  tabcolor;

	void     
		spiwrite(uint8_t),
		writecommand(uint8_t c),
		writedata(uint8_t d),
		commandList(const uint8_t *addr),
		commonInit(const uint8_t *cmdList);
//uint8_t  spiread(void);

	volatile uint8_t *dataport, *clkport, *csport, *rsport;
	uint8_t 
		_cs, _rs, _rst, _sid, _sclk,
		datapinmask, clkpinmask, cspinmask, rspinmask,
		colstart, rowstart; // some displays need this changed
 
};




#ifndef ARDUINO_ARCH_SAM
#include <avr/io.h>
#endif
#include <avr/pgmspace.h> 
 
#ifndef FONT5X7_H
#define FONT5X7_H

// standard ascii 5x7 font

static const unsigned char  font[] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00,   
	0x3E, 0x5B, 0x4F, 0x5B, 0x3E, 	
	0x3E, 0x6B, 0x4F, 0x6B, 0x3E, 	
	0x1C, 0x3E, 0x7C, 0x3E, 0x1C, 
	0x18, 0x3C, 0x7E, 0x3C, 0x18, 
	0x1C, 0x57, 0x7D, 0x57, 0x1C, 
	0x1C, 0x5E, 0x7F, 0x5E, 0x1C, 
	0x00, 0x18, 0x3C, 0x18, 0x00, 
	0xFF, 0xE7, 0xC3, 0xE7, 0xFF, 
	0x00, 0x18, 0x24, 0x18, 0x00, 
	0xFF, 0xE7, 0xDB, 0xE7, 0xFF, 
	0x30, 0x48, 0x3A, 0x06, 0x0E, 
	0x26, 0x29, 0x79, 0x29, 0x26, 
	0x40, 0x7F, 0x05, 0x05, 0x07, 
	0x40, 0x7F, 0x05, 0x25, 0x3F, 
	0x5A, 0x3C, 0xE7, 0x3C, 0x5A, 
	0x7F, 0x3E, 0x1C, 0x1C, 0x08, 
	0x08, 0x1C, 0x1C, 0x3E, 0x7F, 
	0x14, 0x22, 0x7F, 0x22, 0x14, 
	0x5F, 0x5F, 0x00, 0x5F, 0x5F, 
	0x06, 0x09, 0x7F, 0x01, 0x7F, 
	0x00, 0x66, 0x89, 0x95, 0x6A, 
	0x60, 0x60, 0x60, 0x60, 0x60, 
	0x94, 0xA2, 0xFF, 0xA2, 0x94, 
	0x08, 0x04, 0x7E, 0x04, 0x08, 
	0x10, 0x20, 0x7E, 0x20, 0x10, 
	0x08, 0x08, 0x2A, 0x1C, 0x08, 
	0x08, 0x1C, 0x2A, 0x08, 0x08, 
	0x1E, 0x10, 0x10, 0x10, 0x10, 
	0x0C, 0x1E, 0x0C, 0x1E, 0x0C, 
	0x30, 0x38, 0x3E, 0x38, 0x30, 
	0x06, 0x0E, 0x3E, 0x0E, 0x06, 
	0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x5F, 0x00, 0x00, 
	0x00, 0x07, 0x00, 0x07, 0x00, 
	0x14, 0x7F, 0x14, 0x7F, 0x14, 
	0x24, 0x2A, 0x7F, 0x2A, 0x12, 
	0x23, 0x13, 0x08, 0x64, 0x62, 
	0x36, 0x49, 0x56, 0x20, 0x50, 
	0x00, 0x08, 0x07, 0x03, 0x00, 
	0x00, 0x1C, 0x22, 0x41, 0x00, 
	0x00, 0x41, 0x22, 0x1C, 0x00, 
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A, 
	0x08, 0x08, 0x3E, 0x08, 0x08, 
	0x00, 0x80, 0x70, 0x30, 0x00, 
	0x08, 0x08, 0x08, 0x08, 0x08, 
	0x00, 0x00, 0x60, 0x60, 0x00, 
	0x20, 0x10, 0x08, 0x04, 0x02, 
	0x3E, 0x51, 0x49, 0x45, 0x3E, 
	0x00, 0x42, 0x7F, 0x40, 0x00, 
	0x72, 0x49, 0x49, 0x49, 0x46, 
	0x21, 0x41, 0x49, 0x4D, 0x33, 
	0x18, 0x14, 0x12, 0x7F, 0x10, 
	0x27, 0x45, 0x45, 0x45, 0x39, 
	0x3C, 0x4A, 0x49, 0x49, 0x31, 
	0x41, 0x21, 0x11, 0x09, 0x07, 
	0x36, 0x49, 0x49, 0x49, 0x36, 
	0x46, 0x49, 0x49, 0x29, 0x1E, 
	0x00, 0x00, 0x14, 0x00, 0x00, 
	0x00, 0x40, 0x34, 0x00, 0x00, 
	0x00, 0x08, 0x14, 0x22, 0x41, 
	0x14, 0x14, 0x14, 0x14, 0x14, 
	0x00, 0x41, 0x22, 0x14, 0x08, 
	0x02, 0x01, 0x59, 0x09, 0x06, 
	0x3E, 0x41, 0x5D, 0x59, 0x4E, 
	0x7C, 0x12, 0x11, 0x12, 0x7C, 
	0x7F, 0x49, 0x49, 0x49, 0x36, 
	0x3E, 0x41, 0x41, 0x41, 0x22, 
	0x7F, 0x41, 0x41, 0x41, 0x3E, 
	0x7F, 0x49, 0x49, 0x49, 0x41, 
	0x7F, 0x09, 0x09, 0x09, 0x01, 
	0x3E, 0x41, 0x41, 0x51, 0x73, 
	0x7F, 0x08, 0x08, 0x08, 0x7F, 
	0x00, 0x41, 0x7F, 0x41, 0x00, 
	0x20, 0x40, 0x41, 0x3F, 0x01, 
	0x7F, 0x08, 0x14, 0x22, 0x41, 
	0x7F, 0x40, 0x40, 0x40, 0x40, 
	0x7F, 0x02, 0x1C, 0x02, 0x7F, 
	0x7F, 0x04, 0x08, 0x10, 0x7F, 
	0x3E, 0x41, 0x41, 0x41, 0x3E, 
	0x7F, 0x09, 0x09, 0x09, 0x06, 
	0x3E, 0x41, 0x51, 0x21, 0x5E, 
	0x7F, 0x09, 0x19, 0x29, 0x46, 
	0x26, 0x49, 0x49, 0x49, 0x32, 
	0x03, 0x01, 0x7F, 0x01, 0x03, 
	0x3F, 0x40, 0x40, 0x40, 0x3F, 
	0x1F, 0x20, 0x40, 0x20, 0x1F, 
	0x3F, 0x40, 0x38, 0x40, 0x3F, 
	0x63, 0x14, 0x08, 0x14, 0x63, 
	0x03, 0x04, 0x78, 0x04, 0x03, 
	0x61, 0x59, 0x49, 0x4D, 0x43, 
	0x00, 0x7F, 0x41, 0x41, 0x41, 
	0x02, 0x04, 0x08, 0x10, 0x20, 
	0x00, 0x41, 0x41, 0x41, 0x7F, 
	0x04, 0x02, 0x01, 0x02, 0x04, 
	0x40, 0x40, 0x40, 0x40, 0x40, 
	0x00, 0x03, 0x07, 0x08, 0x00, 
	0x20, 0x54, 0x54, 0x78, 0x40, 
	0x7F, 0x28, 0x44, 0x44, 0x38, 
	0x38, 0x44, 0x44, 0x44, 0x28, 
	0x38, 0x44, 0x44, 0x28, 0x7F, 
	0x38, 0x54, 0x54, 0x54, 0x18, 
	0x00, 0x08, 0x7E, 0x09, 0x02, 
	0x18, 0xA4, 0xA4, 0x9C, 0x78, 
	0x7F, 0x08, 0x04, 0x04, 0x78, 
	0x00, 0x44, 0x7D, 0x40, 0x00, 
	0x20, 0x40, 0x40, 0x3D, 0x00, 
	0x7F, 0x10, 0x28, 0x44, 0x00, 
	0x00, 0x41, 0x7F, 0x40, 0x00, 
	0x7C, 0x04, 0x78, 0x04, 0x78, 
	0x7C, 0x08, 0x04, 0x04, 0x78, 
	0x38, 0x44, 0x44, 0x44, 0x38, 
	0xFC, 0x18, 0x24, 0x24, 0x18, 
	0x18, 0x24, 0x24, 0x18, 0xFC, 
	0x7C, 0x08, 0x04, 0x04, 0x08, 
	0x48, 0x54, 0x54, 0x54, 0x24, 
	0x04, 0x04, 0x3F, 0x44, 0x24, 
	0x3C, 0x40, 0x40, 0x20, 0x7C, 
	0x1C, 0x20, 0x40, 0x20, 0x1C, 
	0x3C, 0x40, 0x30, 0x40, 0x3C, 
	0x44, 0x28, 0x10, 0x28, 0x44, 
	0x4C, 0x90, 0x90, 0x90, 0x7C, 
	0x44, 0x64, 0x54, 0x4C, 0x44, 
	0x00, 0x08, 0x36, 0x41, 0x00, 
	0x00, 0x00, 0x77, 0x00, 0x00, 
	0x00, 0x41, 0x36, 0x08, 0x00, 
	0x02, 0x01, 0x02, 0x04, 0x02, 
	0x3C, 0x26, 0x23, 0x26, 0x3C, 
	0x1E, 0xA1, 0xA1, 0x61, 0x12, 
	0x3A, 0x40, 0x40, 0x20, 0x7A, 
	0x38, 0x54, 0x54, 0x55, 0x59, 
	0x21, 0x55, 0x55, 0x79, 0x41, 
	0x21, 0x54, 0x54, 0x78, 0x41, 
	0x21, 0x55, 0x54, 0x78, 0x40, 
	0x20, 0x54, 0x55, 0x79, 0x40, 
	0x0C, 0x1E, 0x52, 0x72, 0x12, 
	0x39, 0x55, 0x55, 0x55, 0x59, 
	0x39, 0x54, 0x54, 0x54, 0x59, 
	0x39, 0x55, 0x54, 0x54, 0x58, 
	0x00, 0x00, 0x45, 0x7C, 0x41, 
	0x00, 0x02, 0x45, 0x7D, 0x42, 
	0x00, 0x01, 0x45, 0x7C, 0x40, 
	0xF0, 0x29, 0x24, 0x29, 0xF0, 
	0xF0, 0x28, 0x25, 0x28, 0xF0, 
	0x7C, 0x54, 0x55, 0x45, 0x00, 
	0x20, 0x54, 0x54, 0x7C, 0x54, 
	0x7C, 0x0A, 0x09, 0x7F, 0x49, 
	0x32, 0x49, 0x49, 0x49, 0x32, 
	0x32, 0x48, 0x48, 0x48, 0x32, 
	0x32, 0x4A, 0x48, 0x48, 0x30, 
	0x3A, 0x41, 0x41, 0x21, 0x7A, 
	0x3A, 0x42, 0x40, 0x20, 0x78, 
	0x00, 0x9D, 0xA0, 0xA0, 0x7D, 
	0x39, 0x44, 0x44, 0x44, 0x39, 
	0x3D, 0x40, 0x40, 0x40, 0x3D, 
	0x3C, 0x24, 0xFF, 0x24, 0x24, 
	0x48, 0x7E, 0x49, 0x43, 0x66, 
	0x2B, 0x2F, 0xFC, 0x2F, 0x2B, 
	0xFF, 0x09, 0x29, 0xF6, 0x20, 
	0xC0, 0x88, 0x7E, 0x09, 0x03, 
	0x20, 0x54, 0x54, 0x79, 0x41, 
	0x00, 0x00, 0x44, 0x7D, 0x41, 
	0x30, 0x48, 0x48, 0x4A, 0x32, 
	0x38, 0x40, 0x40, 0x22, 0x7A, 
	0x00, 0x7A, 0x0A, 0x0A, 0x72, 
	0x7D, 0x0D, 0x19, 0x31, 0x7D, 
	0x26, 0x29, 0x29, 0x2F, 0x28, 
	0x26, 0x29, 0x29, 0x29, 0x26, 
	0x30, 0x48, 0x4D, 0x40, 0x20, 
	0x38, 0x08, 0x08, 0x08, 0x08, 
	0x08, 0x08, 0x08, 0x08, 0x38, 
	0x2F, 0x10, 0xC8, 0xAC, 0xBA, 
	0x2F, 0x10, 0x28, 0x34, 0xFA, 
	0x00, 0x00, 0x7B, 0x00, 0x00, 
	0x08, 0x14, 0x2A, 0x14, 0x22, 
	0x22, 0x14, 0x2A, 0x14, 0x08, 
	0xAA, 0x00, 0x55, 0x00, 0xAA, 
	0xAA, 0x55, 0xAA, 0x55, 0xAA, 
	0x00, 0x00, 0x00, 0xFF, 0x00, 
	0x10, 0x10, 0x10, 0xFF, 0x00, 
	0x14, 0x14, 0x14, 0xFF, 0x00, 
	0x10, 0x10, 0xFF, 0x00, 0xFF, 
	0x10, 0x10, 0xF0, 0x10, 0xF0, 
	0x14, 0x14, 0x14, 0xFC, 0x00, 
	0x14, 0x14, 0xF7, 0x00, 0xFF, 
	0x00, 0x00, 0xFF, 0x00, 0xFF, 
	0x14, 0x14, 0xF4, 0x04, 0xFC, 
	0x14, 0x14, 0x17, 0x10, 0x1F, 
	0x10, 0x10, 0x1F, 0x10, 0x1F, 
	0x14, 0x14, 0x14, 0x1F, 0x00, 
	0x10, 0x10, 0x10, 0xF0, 0x00, 
	0x00, 0x00, 0x00, 0x1F, 0x10, 
	0x10, 0x10, 0x10, 0x1F, 0x10, 
	0x10, 0x10, 0x10, 0xF0, 0x10, 
	0x00, 0x00, 0x00, 0xFF, 0x10, 
	0x10, 0x10, 0x10, 0x10, 0x10, 
	0x10, 0x10, 0x10, 0xFF, 0x10, 
	0x00, 0x00, 0x00, 0xFF, 0x14, 
	0x00, 0x00, 0xFF, 0x00, 0xFF, 
	0x00, 0x00, 0x1F, 0x10, 0x17, 
	0x00, 0x00, 0xFC, 0x04, 0xF4, 
	0x14, 0x14, 0x17, 0x10, 0x17, 
	0x14, 0x14, 0xF4, 0x04, 0xF4, 
	0x00, 0x00, 0xFF, 0x00, 0xF7, 
	0x14, 0x14, 0x14, 0x14, 0x14, 
	0x14, 0x14, 0xF7, 0x00, 0xF7, 
	0x14, 0x14, 0x14, 0x17, 0x14, 
	0x10, 0x10, 0x1F, 0x10, 0x1F, 
	0x14, 0x14, 0x14, 0xF4, 0x14, 
	0x10, 0x10, 0xF0, 0x10, 0xF0, 
	0x00, 0x00, 0x1F, 0x10, 0x1F, 
	0x00, 0x00, 0x00, 0x1F, 0x14, 
	0x00, 0x00, 0x00, 0xFC, 0x14, 
	0x00, 0x00, 0xF0, 0x10, 0xF0, 
	0x10, 0x10, 0xFF, 0x10, 0xFF, 
	0x14, 0x14, 0x14, 0xFF, 0x14, 
	0x10, 0x10, 0x10, 0x1F, 0x00, 
	0x00, 0x00, 0x00, 0xF0, 0x10, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 
	0xFF, 0xFF, 0xFF, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xFF, 0xFF, 
	0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 
	0x38, 0x44, 0x44, 0x38, 0x44, 
	0x7C, 0x2A, 0x2A, 0x3E, 0x14, 
	0x7E, 0x02, 0x02, 0x06, 0x06, 
	0x02, 0x7E, 0x02, 0x7E, 0x02, 
	0x63, 0x55, 0x49, 0x41, 0x63, 
	0x38, 0x44, 0x44, 0x3C, 0x04, 
	0x40, 0x7E, 0x20, 0x1E, 0x20, 
	0x06, 0x02, 0x7E, 0x02, 0x02, 
	0x99, 0xA5, 0xE7, 0xA5, 0x99, 
	0x1C, 0x2A, 0x49, 0x2A, 0x1C, 
	0x4C, 0x72, 0x01, 0x72, 0x4C, 
	0x30, 0x4A, 0x4D, 0x4D, 0x30, 
	0x30, 0x48, 0x78, 0x48, 0x30, 
	0xBC, 0x62, 0x5A, 0x46, 0x3D, 
	0x3E, 0x49, 0x49, 0x49, 0x00, 
	0x7E, 0x01, 0x01, 0x01, 0x7E, 
	0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 
	0x44, 0x44, 0x5F, 0x44, 0x44, 
	0x40, 0x51, 0x4A, 0x44, 0x40, 
	0x40, 0x44, 0x4A, 0x51, 0x40, 
	0x00, 0x00, 0xFF, 0x01, 0x03, 
	0xE0, 0x80, 0xFF, 0x00, 0x00, 
	0x08, 0x08, 0x6B, 0x6B, 0x08, 
	0x36, 0x12, 0x36, 0x24, 0x36, 
	0x06, 0x0F, 0x09, 0x0F, 0x06, 
	0x00, 0x00, 0x18, 0x18, 0x00, 
	0x00, 0x00, 0x10, 0x10, 0x00, 
	0x30, 0x40, 0xFF, 0x01, 0x01, 
	0x00, 0x1F, 0x01, 0x01, 0x1E, 
	0x00, 0x19, 0x1D, 0x17, 0x12, 
	0x00, 0x3C, 0x3C, 0x3C, 0x3C, 
	0x00, 0x00, 0x00, 0x00, 0x00, 
};
#endif

#if defined(__SD_H__)  // Arduino SD library

#define BUFFPIXEL 20
	
class Adafruit_GF;
/// This class mimics Processing's PImage, but with fewer
/// capabilities. It allows an image stored in the SD card to be
/// drawn to the display.
/// @author Enrico Gueli <enrico.gueli@gmail.com>
class PImage {
public:
	PImage() : 
	
	_valid(false), 
	_bmpWidth(0), 
	_bmpHeight(0) { }

	void draw(Adafruit_GF & glcd, int16_t x, int16_t y);
	static PImage loadImage(const char * fileName);
	void close() { _bmpFile.close(); }
	bool isValid() { return _valid; }
	int width() { return _bmpWidth; }	
	int height() { return _bmpHeight; }
  
private:
	friend class Adafruit_GF;

	File _bmpFile;
	int  _bmpWidth, _bmpHeight;   // W+H in pixels
	uint8_t  _bmpDepth;              // Bit depth (currently must be 24)
	uint32_t _bmpImageoffset;        // Start of image data in file
	uint32_t _rowSize;               // Not always = bmpWidth; may have padding
	bool     _flip; 
	bool     _valid;

	PImage(File & bmpFile, int bmpWidth, int bmpHeight, uint8_t  bmpDepth, uint32_t bmpImageoffset, uint32_t rowSize, bool     flip) : 
	_bmpFile(bmpFile),
	_bmpWidth(bmpWidth),
	_bmpHeight(bmpHeight),
	_bmpDepth(bmpDepth),
	_bmpImageoffset(bmpImageoffset),
	_rowSize(rowSize),
	_flip(flip),
	_valid(true){}// since Adafruit_GFX is friend, we could just let it write the variables and save some CPU cycles

	static uint16_t read16(File f);
	static uint32_t read32(File f);

	// TODO close the file in ~PImage and PImage(const PImage&)

};

	PImage loadImage(const char * fileName) { return PImage::loadImage(fileName); }
   
	void image(PImage & img, uint16_t x, uint16_t y);

#else
// #warning "The SD library was not found. loadImage() and image() won't be supported."
#endif


class KA_TFT : public KA_TFT_ST7735 {
public:
	KA_TFT();
	void begin();  
};

#endif


