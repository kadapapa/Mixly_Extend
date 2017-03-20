/*
This is the core graphics library for all our displays, providing a common
set of graphics primitives (points, lines, circles, etc.).  It needs to be
paired with a hardware-specific library for each display device we carry
(to handle the lower-level functions).

CaduinoTFT invests time and resources providing this open source code, please
support CaduinoTFT & open-source hardware by purchasing products from CaduinoTFT!

Copyright (c) 2013 CaduinoTFT Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include "KA_TFT.h"

KA_TFT::KA_TFT():KA_TFT_ST7735()
{ 
	_width = ST7735_TFTHEIGHT;
	_height = ST7735_TFTWIDTH;
}

// begin
void KA_TFT::begin()
{
	SPI.begin();
	TFTbegin(8,13);
	initR(INITR_REDTAB);
	setRotation(1);
}

// width and height
KA_TFT_GF::KA_TFT_GF(int16_t w, int16_t h):WIDTH(w), HEIGHT(h)
{
	_width    = WIDTH;
	_height   = HEIGHT;
	rotation  = 0;
	cursor_y  = cursor_x    = 0;
	textsize  = 1;
	textcolor = textbgcolor = 0xFFFF;
	wrap = true;
}

// draw a circle outline
void KA_TFT_GF::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) 
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	drawPixel(x0, y0+r, color);
	drawPixel(x0, y0-r, color);
	drawPixel(x0+r, y0, color);
	drawPixel(x0-r, y0, color);

	while (x<y) 
	{
		if (f >= 0) 
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		drawPixel(x0 + x, y0 + y, color);
		drawPixel(x0 - x, y0 + y, color);
		drawPixel(x0 + x, y0 - y, color);
		drawPixel(x0 - x, y0 - y, color);
		drawPixel(x0 + y, y0 + x, color);
		drawPixel(x0 - y, y0 + x, color);
		drawPixel(x0 + y, y0 - x, color);
		drawPixel(x0 - y, y0 - x, color);   
	}
}

// draw a circle helper
void KA_TFT_GF::drawCircleHelper( int16_t x0, int16_t y0,int16_t r, uint8_t cornername, uint16_t color)
{
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y) 
	{
		if (f >= 0) 
		{
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;
		if (cornername & 0x4) 
		{
			drawPixel(x0 + x, y0 + y, color);
			drawPixel(x0 + y, y0 + x, color);
		} 
		if (cornername & 0x2) 
		{
			drawPixel(x0 + x, y0 - y, color);
			drawPixel(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8) 
		{
			drawPixel(x0 - y, y0 + x, color);
			drawPixel(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1) 
		{
			drawPixel(x0 - y, y0 - x, color);
			drawPixel(x0 - x, y0 - y, color);
		}
	}
}

// fill a circle
void KA_TFT_GF::fillCircle(int16_t x0, int16_t y0, int16_t r,uint16_t color) 
{
	drawFastVLine(x0, y0-r, 2*r+1, color);
	fillCircleHelper(x0, y0, r, 3, 0, color);
}

// used to do circles and roundrects
void KA_TFT_GF::fillCircleHelper(int16_t x0, int16_t y0, int16_t r,uint8_t cornername, int16_t delta,uint16_t color) 
{
	int16_t f     = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x     = 0;
	int16_t y     = r;

	while (x<y) 
	{
		if (f >= 0) 
		{
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;
		
		if (cornername & 0x1) 
		{
			drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
			drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
		}
		if (cornername & 0x2) 
		{
			drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
			drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
		}
	}
}

// Bresenham's algorithm - thx wikpedia
void KA_TFT_GF::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) 
{
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) 
	{
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1) 
	{
		swap(x0, x1);
		swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) 
	{
		ystep = 1;
	} 
	else 
	{
		ystep = -1;
	}

	for (; x0<=x1; x0++) 
	{
		if (steep) 
		{
			drawPixel(y0, x0, color);
		} 
		else 
		{
			drawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0) 
		{
			y0 += ystep;
			err += dx;
		}
	}
}

// Draw a rectangle
void KA_TFT_GF::drawRect(int16_t x,int16_t y,int16_t w,int16_t h,uint16_t color) 
{
	drawFastHLine(x, y, w, color);
	drawFastHLine(x, y+h-1, w, color);
	drawFastVLine(x, y, h, color);
	drawFastVLine(x+w-1, y, h, color);
}

// draw a fast v line
void KA_TFT_GF::drawFastVLine(int16_t x,int16_t y,int16_t h,uint16_t color) 
{
	// Update in subclasses if desired!
	drawLine(x, y, x, y+h-1, color);
}

// draw a fast h line
void KA_TFT_GF::drawFastHLine(int16_t x,int16_t y,int16_t w, uint16_t color) 
{
	// Update in subclasses if desired!
	drawLine(x, y, x+w-1, y, color);
}

// fill a rect
void KA_TFT_GF::fillRect(int16_t x,int16_t y,int16_t w,int16_t h,uint16_t color) 
{
	// Update in subclasses if desired!
	for (int16_t i=x; i<x+w; i++) 
	{
		drawFastVLine(i, y, h, color);
	}
}

// fill a screen
void KA_TFT_GF::fillScreen(uint16_t color) 
{
	fillRect(0, 0, _width, _height, color);
}

// Draw a rounded rectangle
void KA_TFT_GF::drawRoundRect(int16_t x,int16_t y,int16_t w,int16_t h,int16_t r,uint16_t color) 
{
	// smarter version
	drawFastHLine(x+r  , y    , w-2*r, color); // Top
	drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
	drawFastVLine(x    , y+r  , h-2*r, color); // Left
	drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
	// draw four corners
	drawCircleHelper(x+r    , y+r    , r, 1, color);
	drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
	drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
	drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

// Fill a rounded rectangle
void KA_TFT_GF::fillRoundRect(int16_t x,int16_t y,int16_t w,int16_t h,int16_t r,uint16_t color) 
{
	// smarter version
	fillRect(x+r, y, w-2*r, h, color);

	// draw four corners
	fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

// Draw a triangle
void KA_TFT_GF::drawTriangle(int16_t x0,int16_t y0,int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint16_t color) 
{
	drawLine(x0, y0, x1, y1, color);
	drawLine(x1, y1, x2, y2, color);
	drawLine(x2, y2, x0, y0, color);
}

// Fill a triangle
void KA_TFT_GF::fillTriangle(int16_t x0,int16_t y0,int16_t x1,int16_t y1,int16_t x2,int16_t y2,uint16_t color) 
{
	int16_t a, b, y, last;

	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (y0 > y1) 
	{
		swap(y0, y1); swap(x0, x1);
	}
	if (y1 > y2) 
	{
		swap(y2, y1); swap(x2, x1);
	}
	if (y0 > y1) 
	{
		swap(y0, y1); swap(x0, x1);
	}

	if(y0 == y2) 
	{ // Handle awkward all-on-same-line case as its own thing
		a = b = x0;
		if(x1 < a)      a = x1;
		else if(x1 > b) b = x1;
		if(x2 < a)      a = x2;
		else if(x2 > b) b = x2;
		drawFastHLine(a, y0, b-a+1, color);
		return;
	}

	int16_t
		dx01 = x1 - x0,
		dy01 = y1 - y0,
		dx02 = x2 - x0,
		dy02 = y2 - y0,
		dx12 = x2 - x1,
		dy12 = y2 - y1,
		sa   = 0,
		sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
	if(y1 == y2) last = y1;   // Include y1 scanline
	else         last = y1-1; // Skip it

	for(y=y0; y<=last; y++) 
	{
		a   = x0 + sa / dy01;
		b   = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;
		/* longhand:
		a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
		b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		*/
		if(a > b) swap(a,b);
		drawFastHLine(a, y, b-a+1, color);
	}

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) 
	{
		a   = x1 + sa / dy12;
		b   = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		/* longhand:
		a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
		b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		*/
		if(a > b) swap(a,b);
		drawFastHLine(a, y, b-a+1, color);
	}
}

// Draw a bitmap
void KA_TFT_GF::drawBitmap(int16_t x,int16_t y,const uint8_t *bitmap, int16_t w, int16_t h,uint16_t color) 
{
	int16_t i, j, byteWidth = (w + 7) / 8;

	for(j=0; j<h; j++) 
	{
		for(i=0; i<w; i++ ) 
		{
			if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) 
			{
				drawPixel(x+i, y+j, color);
			}
		}
	}
}


#if ARDUINO >= 100
size_t KA_TFT_GF::write(uint8_t c) {
#else
void KA_TFT_GF::write(uint8_t c) {
#endif
	if (c == '\n') 
	{
		cursor_y += textsize*8;
		cursor_x = 0;
	} 
	else if (c == '\r') 
	{
	// skip em
	} 
	else
	{
		drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
		cursor_x += textsize*6;
		if (wrap && (cursor_x > (_width - textsize*6))) 
		{
			cursor_y += textsize*8;
			cursor_x = 0;
		}
	}
#if ARDUINO >= 100
	return 1;
#endif
}

// draw a character
void KA_TFT_GF::drawChar(int16_t x,int16_t y,unsigned char c,uint16_t color,uint16_t bg,uint8_t size) 
{
	if((x >= _width)		|| // Clip right
	(y >= _height)		|| // Clip bottom
	((x + 6 * size - 1) < 0)	|| // Clip left
	((y + 8 * size - 1) < 0))     // Clip top
	return;

	for (int8_t i=0; i<6; i++ ) 
	{
		uint8_t line;
		if (i == 5) 
		line = 0x0;
		else 
		line = pgm_read_byte(font+(c*5)+i);
		for (int8_t j = 0; j<8; j++) 
		{
			if (line & 0x1) 
			{
				if (size == 1) // default size
					drawPixel(x+i, y+j, color);
				else
				{  // big size
					fillRect(x+(i*size), y+(j*size), size, size, color);
				} 
			} 
			else if (bg != color) 
			{
				if (size == 1) // default size
				drawPixel(x+i, y+j, bg);
				else 
				{  // big size
					fillRect(x+i*size, y+j*size, size, size, bg);
				} 	
			}
			line >>= 1;
		}
	}
}

void KA_TFT_GF::setCursor(int16_t x, int16_t y) 
{
	cursor_x = x;
	cursor_y = y;
}

void KA_TFT_GF::setTextSize(uint8_t s) 
{
	textsize = (s > 0) ? s : 1;
}

void KA_TFT_GF::setTextColor(uint16_t c) 
{
	textcolor = c;
	textbgcolor = c; 
  // for 'transparent' background, we'll set the bg 
  // to the same as fg instead of using a flag
}

void KA_TFT_GF::setTextColor(uint16_t c, uint16_t b) 
{
	textcolor = c;
	textbgcolor = b; 
}

void KA_TFT_GF::setTextWrap(boolean w) 
{
	wrap = w;
}

uint8_t KA_TFT_GF::getRotation(void) 
{
	return rotation;
}

void KA_TFT_GF::setRotation(uint8_t x) 
{
	rotation = (x & 3);
	switch (x) 
	{
		case 0:
		case 2:
		_width = WIDTH;
		_height = HEIGHT;
		break;
		case 1:
		case 3:
		_width = HEIGHT;
		_height = WIDTH;
		break;
	}
}

// return the size of the display (per current rotation)
int16_t KA_TFT_GF::width(void) 
{ 
	return _width; 
}
 
int16_t KA_TFT_GF::height(void) 
{ 
	return _height; 
}

void KA_TFT_GF::invertDisplay(boolean i) 
{
  // Do nothing, must be subclassed if supported
  if(i)
  {
  }
}

uint16_t KA_TFT_GF::newColor(uint8_t r, uint8_t g, uint8_t b) 
{
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void KA_TFT_GF::background(uint8_t red, uint8_t green, uint8_t blue) 
{
	background(newColor(red, green, blue));
}

void KA_TFT_GF::background(color c) 
{
	fillScreen(c);
}

void KA_TFT_GF::stroke(uint8_t red, uint8_t green, uint8_t blue) 
{
	stroke(newColor(red, green, blue));
}

void KA_TFT_GF::stroke(color c) 
{
	  useStroke = true;
	  strokeColor = c;
	  setTextColor(c);
}

void KA_TFT_GF::noStroke() 
{
	useStroke = false;
}

void KA_TFT_GF::noFill() 
{
	useFill = false;
}

void KA_TFT_GF::fill(uint8_t red, uint8_t green, uint8_t blue) 
{
	fill(newColor(red, green, blue));
}

void KA_TFT_GF::fill(color c) 
{
	useFill = true;
	fillColor = c;
}

void KA_TFT_GF::text(int16_t x, int16_t y, uint8_t s,uint16_t color,uint16_t bgcolor,String text) 
{	
	setTextSize(s);
	setCursor(x, y);
	stroke(bgcolor);
	for(int i = 0;i < 10;i++)
    {
		print(cover);
    }

	setCursor(x, y);
	stroke(color);	
	print(text);
}

void KA_TFT_GF::text(const char * text, int16_t x, int16_t y) 
{
	if (!useStroke)
    return;
  
	setTextWrap(false);
	setTextColor(strokeColor);
	setCursor(x, y);
	print(text);
}

void KA_TFT_GF::textWrap(const char * text, int16_t x, int16_t y) 
{
	if (!useStroke)
    return;
  
	setTextWrap(true);
	setTextColor(strokeColor);
	setCursor(x, y);
	print(text);
}

void KA_TFT_GF::textSize(uint8_t size) 
{
	setTextSize(size);
}

void KA_TFT_GF::point(int16_t x, int16_t y) 
{
	if (!useStroke)
    return;
  
	drawPixel(x, y, strokeColor);
}

void KA_TFT_GF::line(int16_t x1, int16_t y1, int16_t x2, int16_t y2) 
{
	if (!useStroke)
    return;
  
	if (x1 == x2) 
	{
		if (y1 < y2)
			drawFastVLine(x1, y1, y2 - y1, strokeColor);
		else
			drawFastVLine(x1, y2, y1 - y2, strokeColor);      
	}
	else if (y1 == y2) 
	{
		if (x1 < x2)
			drawFastHLine(x1, y1, x2 - x1, strokeColor);
		else
			drawFastHLine(x2, y1, x1 - x2, strokeColor);
	}
	else 
	{
		drawLine(x1, y1, x2, y2, strokeColor);
	}
}

void KA_TFT_GF::rect(int16_t x, int16_t y, int16_t width, int16_t height) 
{
	if (useFill) 
	{
		fillRect(x, y, width, height, fillColor);
	}
	if (useStroke) 
	{
		drawRect(x, y, width, height, strokeColor);
	}
}

void KA_TFT_GF::rect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t radius) 
{
	if (radius == 0) 
	{
		rect(x, y, width, height);
	}
	if (useFill) 
	{
		fillRoundRect(x, y, width, height, radius, fillColor);
	}
	if (useStroke) 
	{
		drawRoundRect(x, y, width, height, radius, strokeColor);
	}
}

void KA_TFT_GF::circle(int16_t x, int16_t y, int16_t r) 
{
	if (r == 0)
    return;
  
	if (useFill) 
	{
		fillCircle(x, y, r, fillColor);
	}
	if (useStroke) 
	{
		drawCircle(x, y, r, strokeColor);
	}
}

void KA_TFT_GF::triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3) 
{
	if (useFill) 
	{
		fillTriangle(x1, y1, x2, y2, x3, y3, fillColor);
	}
	if (useStroke)
	{
		drawTriangle(x1, y1, x2, y2, x3, y3, strokeColor);
	}
}


/*************************************************** 
  This is a library for the CaduinoTFT 1.8" SPI display.
  This library works with the CaduinoTFT 1.8" TFT Breakout w/SD card
  ----> http://www.CaduinoTFT.com/products/358
  as well as CaduinoTFT raw 1.8" TFT display
  ----> http://www.CaduinoTFT.com/products/618
 
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  CaduinoTFT invests time and resources providing this open source code,
  please support CaduinoTFT and open-source hardware by purchasing
  products from CaduinoTFT!

  Written by Limor Fried/Ladyada for CaduinoTFT Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


inline uint16_t swapcolor(uint16_t x) 
{ 
	return (x << 11) | (x & 0x07E0) | (x >> 11);
}

// Constructor when using software SPI.  All output pins are configurable.
KA_TFT_ST7735::KA_TFT_ST7735() : KA_TFT_GF(ST7735_TFTWIDTH, ST7735_TFTHEIGHT) 
{

}

void KA_TFT_ST7735::TFTbegin(uint8_t cs,uint8_t rs)
{
	_cs   = cs;
	_rs   = rs;
}

inline void KA_TFT_ST7735::spiwrite(uint8_t c) 
{
	SPI.transfer(c);
}

void KA_TFT_ST7735::writecommand(uint8_t c) 
{
	*rsport &= ~rspinmask;
	*csport &= ~cspinmask;

	//Serial.print("C ");
	spiwrite(c);

	*csport |= cspinmask;
}

void KA_TFT_ST7735::writedata(uint8_t c)
{
	*rsport |=  rspinmask;
	*csport &= ~cspinmask;

	//Serial.print("D ");
	spiwrite(c);

	*csport |= cspinmask;
}


// Rather than a bazillion writecommand() and writedata() calls, screen
// initialization commands and arguments are organized in these tables
// stored in PROGMEM.  The table may look bulky, but that's mostly the
// formatting -- storage-wise this is hundreds of bytes more compact
// than the equivalent code.  Companion function follows.
#define DELAY 0x80

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x08
#define MADCTL_MH  0x04

PROGMEM const static unsigned char
  Bcmd[] = {                  // Initialization commands for 7735B screens
    18,                       // 18 commands in list:
    ST7735_SWRESET,   DELAY,  //  1: Software reset, no args, w/delay
      50,                     //     50 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, no args, w/delay
      255,                    //     255 = 500 ms delay
    ST7735_COLMOD , 1+DELAY,  //  3: Set color mode, 1 arg + delay:
      0x05,                   //     16-bit color
      10,                     //     10 ms delay
    ST7735_FRMCTR1, 3+DELAY,  //  4: Frame rate control, 3 args + delay:
      0x00,                   //     fastest refresh
      0x06,                   //     6 lines front porch
      0x03,                   //     3 lines back porch
      10,                     //     10 ms delay
    ST7735_MADCTL , 1      ,  //  5: Memory access ctrl (directions), 1 arg:
      0x08,                   //     Row addr/col addr, bottom to top refresh
    ST7735_DISSET5, 2      ,  //  6: Display settings #5, 2 args, no delay:
      0x15,                   //     1 clk cycle nonoverlap, 2 cycle gate
                              //     rise, 3 cycle osc equalize
      0x02,                   //     Fix on VTL
    ST7735_INVCTR , 1      ,  //  7: Display inversion control, 1 arg:
      0x0,                    //     Line inversion
    ST7735_PWCTR1 , 2+DELAY,  //  8: Power control, 2 args + delay:
      0x02,                   //     GVDD = 4.7V
      0x70,                   //     1.0uA
      10,                     //     10 ms delay
    ST7735_PWCTR2 , 1      ,  //  9: Power control, 1 arg, no delay:
      0x05,                   //     VGH = 14.7V, VGL = -7.35V
    ST7735_PWCTR3 , 2      ,  // 10: Power control, 2 args, no delay:
      0x01,                   //     Opamp current small
      0x02,                   //     Boost frequency
    ST7735_VMCTR1 , 2+DELAY,  // 11: Power control, 2 args + delay:
      0x3C,                   //     VCOMH = 4V
      0x38,                   //     VCOML = -1.1V
      10,                     //     10 ms delay
    ST7735_PWCTR6 , 2      ,  // 12: Power control, 2 args, no delay:
      0x11, 0x15,
    ST7735_GMCTRP1,16      ,  // 13: Magical unicorn dust, 16 args, no delay:
      0x09, 0x16, 0x09, 0x20, //     (seriously though, not sure what
      0x21, 0x1B, 0x13, 0x19, //      these config values represent)
      0x17, 0x15, 0x1E, 0x2B,
      0x04, 0x05, 0x02, 0x0E,
    ST7735_GMCTRN1,16+DELAY,  // 14: Sparkles and rainbows, 16 args + delay:
      0x0B, 0x14, 0x08, 0x1E, //     (ditto)
      0x22, 0x1D, 0x18, 0x1E,
      0x1B, 0x1A, 0x24, 0x2B,
      0x06, 0x06, 0x02, 0x0F,
      10,                     //     10 ms delay
    ST7735_CASET  , 4      ,  // 15: Column addr set, 4 args, no delay:
      0x00, 0x02,             //     XSTART = 2
      0x00, 0x81,             //     XEND = 129
    ST7735_RASET  , 4      ,  // 16: Row addr set, 4 args, no delay:
      0x00, 0x02,             //     XSTART = 1
      0x00, 0x81,             //     XEND = 160
    ST7735_NORON  ,   DELAY,  // 17: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,   DELAY,  // 18: Main screen turn on, no args, w/delay
      255 },                  //     255 = 500 ms delay
	  
  Rcmd1[] = {                 // Init for 7735R, part 1 (red or green tab)
    15,                       // 15 commands in list:
    ST7735_SWRESET,   DELAY,  //  1: Software reset, 0 args, w/delay
      150,                    //     150 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, 0 args, w/delay
      255,                    //     500 ms delay
    ST7735_FRMCTR1, 3      ,  //  3: Frame rate ctrl - normal mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR2, 3      ,  //  4: Frame rate control - idle mode, 3 args:
      0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR3, 6      ,  //  5: Frame rate ctrl - partial mode, 6 args:
      0x01, 0x2C, 0x2D,       //     Dot inversion mode
      0x01, 0x2C, 0x2D,       //     Line inversion mode
    ST7735_INVCTR , 1      ,  //  6: Display inversion ctrl, 1 arg, no delay:
      0x07,                   //     No inversion
    ST7735_PWCTR1 , 3      ,  //  7: Power control, 3 args, no delay:
      0xA2,
      0x02,                   //     -4.6V
      0x84,                   //     AUTO mode
    ST7735_PWCTR2 , 1      ,  //  8: Power control, 1 arg, no delay:
      0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    ST7735_PWCTR3 , 2      ,  //  9: Power control, 2 args, no delay:
      0x0A,                   //     Opamp current small
      0x00,                   //     Boost frequency
    ST7735_PWCTR4 , 2      ,  // 10: Power control, 2 args, no delay:
      0x8A,                   //     BCLK/2, Opamp current small & Medium low
      0x2A,  
    ST7735_PWCTR5 , 2      ,  // 11: Power control, 2 args, no delay:
      0x8A, 0xEE,
    ST7735_VMCTR1 , 1      ,  // 12: Power control, 1 arg, no delay:
      0x0E,
    ST7735_INVOFF , 0      ,  // 13: Don't invert display, no args, no delay
    ST7735_MADCTL , 1      ,  // 14: Memory access control (directions), 1 arg:
      0xC8,                   //     row addr/col addr, bottom to top refresh
    ST7735_COLMOD , 1      ,  // 15: set color mode, 1 arg, no delay:
      0x05 },                 //     16-bit color
	  
  Rcmd2green[] = {            // Init for 7735R, part 2 (green tab only)
    2,                        //  2 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x02,             //     XSTART = 0
      0x00, 0x7F+0x02,        //     XEND = 127
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x01,             //     XSTART = 0
      0x00, 0x9F+0x01 },      //     XEND = 159
	  
  Rcmd2red[] = {              // Init for 7735R, part 2 (red tab only)
    2,                        //  2 commands in list:
    ST7735_CASET  , 4      ,  //  1: Column addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x7F,             //     XEND = 127
    ST7735_RASET  , 4      ,  //  2: Row addr set, 4 args, no delay:
      0x00, 0x00,             //     XSTART = 0
      0x00, 0x9F },           //     XEND = 159
	  
  Rcmd3[] = {                 // Init for 7735R, part 3 (red or green tab)
    4,                        //  4 commands in list:
    ST7735_GMCTRP1, 16      , //  1: Magical unicorn dust, 16 args, no delay:
      0x02, 0x1c, 0x07, 0x12,
      0x37, 0x32, 0x29, 0x2d,
      0x29, 0x25, 0x2B, 0x39,
      0x00, 0x01, 0x03, 0x10,
    ST7735_GMCTRN1, 16      , //  2: Sparkles and rainbows, 16 args, no delay:
      0x03, 0x1d, 0x07, 0x06,
      0x2E, 0x2C, 0x29, 0x2D,
      0x2E, 0x2E, 0x37, 0x3F,
      0x00, 0x00, 0x02, 0x10,
    ST7735_NORON  ,    DELAY, //  3: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,    DELAY, //  4: Main screen turn on, no args w/delay
      100 },                  //     100 ms delay
	  
  Gcmd[] = {                  // Initialization commands for 7735B screens
    19,                       // 18 commands in list:
    ST7735_SWRESET,   DELAY,  //  1: Software reset, no args, w/delay
      50,                     //     50 ms delay
    ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, no args, w/delay
      100,                    //     255 = 500 ms delay
    0x26 , 1,  			// 3: Set default gamma
      0x04,                     //     16-bit color
    0xb1, 2,              	// 4: Frame Rate
      0x0b,
      0x14,
    0xc0, 2,                    // 5: VRH1[4:0] & VC[2:0]
      0x08,
      0x00,
    0xc1, 1,                    // 6: BT[2:0]
      0x05,
    0xc5, 2,                    // 7: VMH[6:0] & VML[6:0]
      0x41,
      0x30,
    0xc7, 1,                    // 8: LCD Driving control
      0xc1,
    0xEC, 1,                    // 9: Set pumping color freq
      0x1b,
    0x3a , 1 + DELAY,  	        // 10: Set color format
      0x55,                     //     16-bit color
      100,
    0x2a, 4,                    // 11: Set Column Address
      0x00,
      0x00,
      0x00,
      0x7f,
    0x2b, 4,                    // 12: Set Page Address
      0x00,
      0x00,
      0x00,
      0x9f,
    0x36, 1,                    // 12+1: Set Scanning Direction
      0xc8,
    0xb7, 1,			// 14: Set Source Output Direciton
      0x00,
    0xf2, 1,			// 15: Enable Gamma bit
      0x00,
    0xe0, 15 + DELAY,		// 16: magic
      0x28, 0x24, 0x22, 0x31,
      0x2b, 0x0e, 0x53, 0xa5,
      0x42, 0x16, 0x18, 0x12,
      0x1a, 0x14, 0x03,
      50,
    0xe1, 15 + DELAY,		// 17: more magic
      0x17, 0x1b, 0x1d, 0x0e,
      0x14, 0x11, 0x2c, 0xa5,
      0x3d, 0x09, 0x27, 0x2d,
      0x25, 0x2b, 0x3c, 
      50, 
    ST7735_NORON  ,   DELAY,  // 17: Normal display on, no args, w/delay
      10,                     //     10 ms delay
    ST7735_DISPON ,   DELAY,  // 18: Main screen turn on, no args, w/delay
      255 };                  //     255 = 500 ms delay


// Companion code to the above tables.  Reads and issues
// a series of LCD commands stored in PROGMEM byte array.
void KA_TFT_ST7735::commandList(const uint8_t *addr) 
{

	uint8_t  numCommands, numArgs;
	uint16_t ms;

	numCommands = pgm_read_byte(addr++);   // Number of commands to follow
	while(numCommands--) 
	{                 // For each command...
		writecommand(pgm_read_byte(addr++)); //   Read, issue command
		numArgs  = pgm_read_byte(addr++);    //   Number of args to follow
		ms       = numArgs & DELAY;          //   If hibit set, delay follows args
		numArgs &= ~DELAY;                   //   Mask out delay bit
		while(numArgs--) 
		{                   //   For each argument...
			writedata(pgm_read_byte(addr++));  //     Read, issue argument
		}

		if(ms) 
		{
			ms = pgm_read_byte(addr++); // Read post-command delay time (ms)
			if(ms == 255) ms = 500;     // If 255, delay for 500 ms
			delay(ms);
		}
	}
}

// Initialization code common to both 'B' and 'R' type displays
void KA_TFT_ST7735::commonInit(const uint8_t *cmdList) 
{

	colstart  = rowstart = 0; // May be overridden in init func

	pinMode(_rs, OUTPUT);
	pinMode(_cs, OUTPUT);
	csport    = portOutputRegister(digitalPinToPort(_cs));
	cspinmask = digitalPinToBitMask(_cs);
	rsport    = portOutputRegister(digitalPinToPort(_rs));
	rspinmask = digitalPinToBitMask(_rs);


    pinMode(_sclk, OUTPUT);
    pinMode(_sid , OUTPUT);
    clkport     = portOutputRegister(digitalPinToPort(_sclk));
    clkpinmask  = digitalPinToBitMask(_sclk);
    dataport    = portOutputRegister(digitalPinToPort(_sid));
    datapinmask = digitalPinToBitMask(_sid);
    *clkport   &= ~clkpinmask;
    *dataport  &= ~datapinmask;


  // toggle RST low to reset; CS low so it'll listen to us
	*csport &= ~cspinmask;
	if(cmdList) commandList(cmdList);
}

// Initialization for ST7735B screens
void KA_TFT_ST7735::initB(void) 
{
	commonInit(Bcmd);
}

// Initialization for ST7735B screens
void KA_TFT_ST7735::initG(void) 
{
	commonInit(Gcmd);
}

// Initialization for ST7735R screens (green or red tabs)
void KA_TFT_ST7735::initR(uint8_t options) 
{
	commonInit(Rcmd1);
	if(options == INITR_GREENTAB) 
	{
		commandList(Rcmd2green);
		colstart = 2;
		rowstart = 1;
	} 
	else 
	{
		// colstart, rowstart left at default '0' values
		commandList(Rcmd2red);
	}
	commandList(Rcmd3);
	tabcolor = options;
}

void KA_TFT_ST7735::setAddrWindow(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1) 
{
	writecommand(ST7735_CASET); // Column addr set
	writedata(0x00);
	writedata(x0+colstart);     // XSTART 
	writedata(0x00);
	writedata(x1+colstart);     // XEND

	writecommand(ST7735_RASET); // Row addr set
	writedata(0x00);
	writedata(y0+rowstart);     // YSTART
	writedata(0x00);
	writedata(y1+rowstart);     // YEND

	writecommand(ST7735_RAMWR); // write to RAM
}

void KA_TFT_ST7735::pushColor(uint16_t color)
{
	*rsport |=  rspinmask;
	*csport &= ~cspinmask;

	if (tabcolor == INITR_BLACKTAB)   color = swapcolor(color);
	spiwrite(color >> 8);
	spiwrite(color);

	*csport |= cspinmask;
}

void KA_TFT_ST7735::drawPixel(int16_t x, int16_t y, uint16_t color)
{

	if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;

	setAddrWindow(x,y,x+1,y+1);


	*rsport |=  rspinmask;
	*csport &= ~cspinmask;

	if (tabcolor == INITR_BLACKTAB)   color = swapcolor(color);

	spiwrite(color >> 8);
	spiwrite(color);

	*csport |= cspinmask;

}

void KA_TFT_ST7735::drawFastVLine(int16_t x,int16_t y,int16_t h,uint16_t color) 
{

	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) return;
	if((y+h-1) >= _height) h = _height-y;
	setAddrWindow(x, y, x, y+h-1);

	if (tabcolor == INITR_BLACKTAB)   color = swapcolor(color);

	uint8_t hi = color >> 8, lo = color;

	*rsport |=  rspinmask;
	*csport &= ~cspinmask;
	while (h--) {
	spiwrite(hi);
	spiwrite(lo);
	}
	*csport |= cspinmask;

}

void KA_TFT_ST7735::drawFastHLine(int16_t x,int16_t y,int16_t w,uint16_t color) 
{

	// Rudimentary clipping
	if((x >= _width) || (y >= _height)) return;
	if((x+w-1) >= _width)  w = _width-x;
	setAddrWindow(x, y, x+w-1, y);

	if (tabcolor == INITR_BLACKTAB)   color = swapcolor(color);

	uint8_t hi = color >> 8, lo = color;

	*rsport |=  rspinmask;
	*csport &= ~cspinmask;
	while (w--) {
	spiwrite(hi);
	spiwrite(lo);
	}
	*csport |= cspinmask;

}

void KA_TFT_ST7735::fillScreen(uint16_t color) 
{
	fillRect(0, 0,  _width, _height, color);
}

// fill a rectangle
void KA_TFT_ST7735::fillRect(int16_t x,int16_t y,int16_t w,int16_t h,uint16_t color) 
{

	// rudimentary clipping (drawChar w/big text requires this)
	if((x >= _width) || (y >= _height)) return;
	if((x + w - 1) >= _width)  w = _width  - x;
	if((y + h - 1) >= _height) h = _height - y;

	if (tabcolor == INITR_BLACKTAB)   color = swapcolor(color);

	setAddrWindow(x, y, x+w-1, y+h-1);

	uint8_t hi = color >> 8, lo = color;

	*rsport |=  rspinmask;
	*csport &= ~cspinmask;
	for(y=h; y>0; y--) 
	{
		for(x=w; x>0; x--) 
		{
			spiwrite(hi);
			spiwrite(lo);
		}
	}

	*csport |= cspinmask;

}

void KA_TFT_ST7735::setRotation(uint8_t m) 
{
	writecommand(ST7735_MADCTL);
	rotation = m % 4; // can't be higher than 3
	switch (rotation) 
	{
		case 0:
			writedata(MADCTL_MX | MADCTL_MY | MADCTL_RGB);
			_width  = ST7735_TFTWIDTH;
			_height = ST7735_TFTHEIGHT;
		break;
		case 1:
			writedata(MADCTL_MY | MADCTL_MV | MADCTL_RGB);
			_width  = ST7735_TFTHEIGHT;
			_height = ST7735_TFTWIDTH;
		break;
		case 2:
			writedata(MADCTL_RGB);
			_width  = ST7735_TFTWIDTH;
			_height = ST7735_TFTHEIGHT;
		break;
		case 3:
			writedata(MADCTL_MX | MADCTL_MV | MADCTL_RGB);
			_width  = ST7735_TFTHEIGHT;
			_height = ST7735_TFTWIDTH;
		break;
	}
}

void KA_TFT_ST7735::invertDisplay(boolean i) 
{
	writecommand(i ? ST7735_INVON : ST7735_INVOFF);
}


#if defined(__SD_H__)  // Arduino SD library

static uint16_t PImage::read16(File f) 
{
	uint16_t result;
	((uint8_t *)&result)[0] = f.read(); // LSB
	((uint8_t *)&result)[1] = f.read(); // MSB
	return result;
}

static uint32_t PImage::read32(File f) 
{
	uint32_t result;
	((uint8_t *)&result)[0] = f.read(); // LSB
	((uint8_t *)&result)[1] = f.read();
	((uint8_t *)&result)[2] = f.read();
	((uint8_t *)&result)[3] = f.read(); // MSB
	return result;
}

void KA_TFT_GF::image(PImage & img, uint16_t x, uint16_t y) 
{
	int      w, h, row, col;
	uint8_t  r, g, b;
	uint32_t pos = 0;
	uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
	uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer

	// Crop area to be loaded
	w = img._bmpWidth;
	h = img._bmpHeight;
	if((x+w-1) >= width())  w = width()  - x;
	if((y+h-1) >= height()) h = height() - y;

	/*
	// Set TFT address window to clipped image bounds
	setAddrWindow(x, y, x+w-1, y+h-1);
	*/
  
  for (row=0; row<h; row++) { // For each scanline...
    // Seek to start of scan line.  It might seem labor-
    // intensive to be doing this on every line, but this
    // method covers a lot of gritty details like cropping
    // and scanline padding.  Also, the seek only takes
    // place if the file position actually needs to change
    // (avoids a lot of cluster math in SD library).
    if(img._flip) // Bitmap is stored bottom-to-top order (normal BMP)
      pos = img._bmpImageoffset + (img._bmpHeight - 1 - row) * img._rowSize;
    else     // Bitmap is stored top-to-bottom
      pos = img._bmpImageoffset + row * img._rowSize;
    if(img._bmpFile.position() != pos) { // Need seek?
      img._bmpFile.seek(pos);
      buffidx = sizeof(sdbuffer); // Force buffer reload
    }

    for (col=0; col<w; col++) { // For each pixel...
      // Time to read more pixel data?
      if (buffidx >= sizeof(sdbuffer)) { // Indeed
        img._bmpFile.read(sdbuffer, sizeof(sdbuffer));
        buffidx = 0; // Set index to beginning
      }

      // Convert pixel from BMP to TFT format, push to display
      b = sdbuffer[buffidx++];
      g = sdbuffer[buffidx++];
      r = sdbuffer[buffidx++];
      //pushColor(tft.Color565(r,g,b));
      drawPixel(x + col, y + row, newColor(r, g, b));
      
    } // end pixel
  } // end scanline

}

PImage PImage::loadImage(const char * fileName) {
	File     bmpFile;
	int      bmpWidth, bmpHeight;   // W+H in pixels
	uint8_t  bmpDepth;              // Bit depth (currently must be 24)
	uint32_t bmpImageoffset;        // Start of image data in file
	uint32_t rowSize;               // Not always = bmpWidth; may have padding
	bool     flip    = true;        // BMP is stored bottom-to-top

  // Open requested file on SD card
	if ((bmpFile = SD.open(fileName)) == NULL) {
		Serial.print(F("loadImage: file not found: "));
		Serial.println(fileName);
		return PImage(); // load error
	}
  
	// Parse BMP header
	if(read16(bmpFile) != 0x4D42) { // BMP signature
		Serial.println(F("loadImage: file doesn't look like a BMP"));
		return PImage();
	}
  
	Serial.print(F("File size: ")); Serial.println(read32(bmpFile));
	(void)read32(bmpFile); // Read & ignore creator bytes
	bmpImageoffset = read32(bmpFile); // Start of image data
	Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
	// Read DIB header
	Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
	bmpWidth  = read32(bmpFile);
	bmpHeight = read32(bmpFile);
	if(read16(bmpFile) != 1) { // # planes -- must be '1'
		Serial.println(F("loadImage: invalid n. of planes"));
		return PImage();
	}
  
	bmpDepth = read16(bmpFile); // bits per pixel
	Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
	if((bmpDepth != 24) || (read32(bmpFile) != 0)) { // 0 = uncompressed {
		Serial.println(F("loadImage: invalid pixel format"));
		return PImage();
	}

	Serial.print(F("Image size: "));
	Serial.print(bmpWidth);
	Serial.print('x');
	Serial.println(bmpHeight);

	// BMP rows are padded (if needed) to 4-byte boundary
	rowSize = (bmpWidth * 3 + 3) & ~3;

	// If bmpHeight is negative, image is in top-down order.
	// This is not canon but has been observed in the wild.
	if(bmpHeight < 0) {
		bmpHeight = -bmpHeight;
		flip      = false;
	}
  
	return PImage(bmpFile, bmpWidth, bmpHeight, bmpDepth, bmpImageoffset, rowSize, flip);
}

#endif


////////// stuff not actively being used, but kept for posterity
/*

 uint8_t KA_TFT_ST7735::spiread(void) {
 uint8_t r = 0;
 if (_sid > 0) {
 r = shiftIn(_sid, _sclk, MSBFIRST);
 } else {
 //SID_DDR &= ~_BV(SID);
 //int8_t i;
 //for (i=7; i>=0; i--) {
 //  SCLK_PORT &= ~_BV(SCLK);
 //  r <<= 1;
 //  r |= (SID_PIN >> SID) & 0x1;
 //  SCLK_PORT |= _BV(SCLK);
 //}
 //SID_DDR |= _BV(SID);
 
 }
 return r;
 }
 
 
 void KA_TFT_ST7735::dummyclock(void) {
 
 if (_sid > 0) {
 digitalWrite(_sclk, LOW);
 digitalWrite(_sclk, HIGH);
 } else {
 // SCLK_PORT &= ~_BV(SCLK);
 //SCLK_PORT |= _BV(SCLK);
 }
 }
 uint8_t KA_TFT_ST7735::readdata(void) {
 *portOutputRegister(rsport) |= rspin;
 
 *portOutputRegister(csport) &= ~ cspin;
 
 uint8_t r = spiread();
 
 *portOutputRegister(csport) |= cspin;
 
 return r;
 
 } 
 
 uint8_t KA_TFT_ST7735::readcommand8(uint8_t c) {
 digitalWrite(_rs, LOW);
 
 *portOutputRegister(csport) &= ~ cspin;
 
 spiwrite(c);
 
 digitalWrite(_rs, HIGH);
 pinMode(_sid, INPUT); // input!
 digitalWrite(_sid, LOW); // low
 spiread();
 uint8_t r = spiread();
 
 
 *portOutputRegister(csport) |= cspin;
 
 
 pinMode(_sid, OUTPUT); // back to output
 return r;
 }
 
 
 uint16_t KA_TFT_ST7735::readcommand16(uint8_t c) {
 digitalWrite(_rs, LOW);
 if (_cs)
 digitalWrite(_cs, LOW);
 
 spiwrite(c);
 pinMode(_sid, INPUT); // input!
 uint16_t r = spiread();
 r <<= 8;
 r |= spiread();
 if (_cs)
 digitalWrite(_cs, HIGH);
 
 pinMode(_sid, OUTPUT); // back to output
 return r;
 }
 
 uint32_t KA_TFT_ST7735::readcommand32(uint8_t c) {
 digitalWrite(_rs, LOW);
 if (_cs)
 digitalWrite(_cs, LOW);
 spiwrite(c);
 pinMode(_sid, INPUT); // input!
 
 dummyclock();
 dummyclock();
 
 uint32_t r = spiread();
 r <<= 8;
 r |= spiread();
 r <<= 8;
 r |= spiread();
 r <<= 8;
 r |= spiread();
 if (_cs)
 digitalWrite(_cs, HIGH);
 
 pinMode(_sid, OUTPUT); // back to output
 return r;
 }
 
 */
