/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   KA_TouchKey
 * \brief   Driver for KA_ 7-Segment Serial Display module.
 * @file    KA_TouchKey.cpp
 * @author  MakeBlock
 * @version V1.0.4
 * @date    2015/11/12
 * @brief   Driver for KA_ 7 Segment Serial Display module.
 *
 * \par Copyright
 * This software is Copyright (C), 2012-2016, MakeBlock. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * \par Description
 * Driver for KA_ 7 Segment Serial Display module.
 * \par KA_thod List:
 *
 *    1.    void    KA_TouchKey::init(void);
 *    2.    void    KA_TouchKey::set(uint8_t brightness, uint8_t SetData, uint8_t SetAddr);
 *    3.    void    KA_TouchKey::reset(uint8_t port);
 *    4.    void    KA_TouchKey::setpin(uint8_t dataPin, uint8_t clkPin);
 *    5.    void    KA_TouchKey::write(uint8_t SegData[]);
 *    6.    void    KA_TouchKey::write(uint8_t BitAddr, uint8_t SegData);
 *    7.    void    KA_TouchKey::display(uint16_t value);
 *    8.    void    KA_TouchKey::display(int16_t value);
 *    9.    void    KA_TouchKey::display(float value);
 *    10.   int16_t KA_TouchKey::checkNum(float v,int16_t b);
 *    11.   void    KA_TouchKey::display(double value, uint8_t digits);
 *    12.   void    KA_TouchKey::display(uint8_t DispData[]);
 *    13.   void    KA_TouchKey::display(uint8_t BitAddr, uint8_t DispData);
 *    14.   void    KA_TouchKey::display(uint8_t BitAddr, uint8_t DispData, uint8_t point_on);
 *    15.   void    KA_TouchKey::clearDisplay(void);
 *    16.   void    KA_TouchKey::setBrightness(uint8_t brightness);
 *    17.   void    KA_TouchKey::coding(uint8_t DispData[]);
 *    18.   uint8_t KA_TouchKey::coding(uint8_t DispData);
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan         2015/07/24     1.0.0            Rebuild the old lib.
 * Rafael Lee       2015/09/02     1.0.1            Added some comments and macros. Some bug fixed in coding function.
 * Mark Yan         2015/10/29     1.0.2            fix issue when display negative data.
 * Mark Yan         2015/11/09     1.0.3            fix some comments error.
 * Mark Yan         2015/11/12     1.0.4            fix driver API.
 * </pre>
 *
 * @example NumberDisplay.ino
 * @example NumberFlow.ino
 * @example TimeDisplay.ino
 */

/* Includes ------------------------------------------------------------------*/
#include "KA_TouchKey.h"
/* Private variables ---------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/**
 * Alternate Constructor which can call your own function to map the 7-Segment display to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
KA_TouchKey::KA_TouchKey(void) : KA_Port()
{

}

/**
 * Alternate Constructor which can call your own function to map the 7-Segment display to arduino port,
 * the slot1 will be used for data pin and slot2 will used for clk pin.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */ 
KA_TouchKey::KA_TouchKey(uint8_t port) : KA_Port(port)
{
	_dataPin = s1;
	_clkPin = s2;
	pinMode(_clkPin, OUTPUT);
	pinMode(_dataPin, OUTPUT);
	set();
}

/**
 * Alternate Constructor which can call your own function to map the 7-Segment display to arduino port. 
 * \param[in]
 *    dataPin - The DATA pin for Seven-Segment LED module(arduino port).
 * \param[in]
 *    clkPin - The CLK pin for Seven-Segment LED module(arduino port).
 */
KA_TouchKey::KA_TouchKey(uint8_t dataPin, uint8_t clkPin)
{
	_dataPin = dataPin;
	_clkPin = clkPin;
	pinMode(_clkPin, OUTPUT);
	pinMode(_dataPin, OUTPUT);
	set();
}

/**
 * \par Function
 *    reset
 * \par Description
 *    Reset the port for Seven-Segment LED module, the prot here is RJ25 port from PORT_1 to M2.
 * \param[in]
 *    port - RJ25 port from PORT_1 to M2
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    Set global variable _dataPin and _clkPin
 */
void KA_TouchKey::reset(void)
{
	//  _port = port;
	//  s2    = icPort[port].s2;
	//  s1    = icPort[port].s1;
	_dataPin = s1;
	_clkPin = s2;
	pinMode(_clkPin, OUTPUT);
	pinMode(_dataPin, OUTPUT);
	set();
}

/**
 * \par Function
 *    setpin
 * \par Description
 *    Reset Seven-Segment LED module's data pin and its clock pin then clear display.
 * \param[in]
 *    dataPin - The DATA pin for Seven-Segment LED module(arduino port).
 * \param[in]
 *    clkPin - The CLK pin for Seven-Segment LED module(arduino port).
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    Set global variable _KeyPin and _clkPin
 */
void KA_TouchKey::setpin(uint8_t dataPin, uint8_t clkPin)
{
	_dataPin = dataPin;
	_clkPin = clkPin;
	pinMode(_clkPin, OUTPUT);
	pinMode(_dataPin, OUTPUT);
	// s1 = dataPin;
	// s2 = clkPin;
}


/**
 * \par Function
 *    writeByte
 * \par Description
 *    Write one byte to TM1637.
 * \param[in]
 *    wr_data - Data to write to module.
 * \par Output
 *    None
 * \return
 *    None
 * \others
 *    None
 */
void KA_TouchKey::writeByte(uint8_t wr_data)
{
  uint8_t i;
 // uint8_t cnt0;
  for (i = 0; i < 8; i++)  //sent 8bit data
  {
    digitalWrite(_clkPin, LOW);
    if (wr_data & 0x80)
    {
      digitalWrite(_dataPin, HIGH); //LSB first
    }
    else
    {
      digitalWrite(_dataPin, LOW);
    }
    wr_data <<= 1;
    digitalWrite(_clkPin, HIGH);

  }
  digitalWrite(_clkPin, LOW); //wait for ACK
  digitalWrite(_clkPin, HIGH);
  digitalWrite(_clkPin, LOW);
 /* 
  pinMode(_dataPin, INPUT);
  while (digitalRead(_dataPin))
  {
    cnt0 += 1;
    if (cnt0 == 200)
    {
      pinMode(_dataPin, OUTPUT);
      digitalWrite(_dataPin, LOW);
      cnt0 = 0;
    }
  }
  pinMode(_dataPin, OUTPUT);
*/
}

/**
 * \par Function
 *    coding
 * \par Description
 *    Return display data from look up table.
 * \param[in]
 *    DispData - Data need be transcoded.
 * \par Output
 *    None
 * \return
 *    Return the value of transcoding
 * \par Others
 *    None
 */
uint16_t KA_TouchKey::readByte(void)
{
	uint8_t i;
	uint16_t dat = 0;
	digitalWrite(_dataPin, HIGH); //LSB first	
	pinMode(_dataPin, INPUT); 		  		  
	for(i = 0;i < 16;i++)
	{
		digitalWrite(_clkPin, HIGH);                        //时钟上沿
		dat <<= 1;
		if(digitalRead(_dataPin))
		{
			dat++;
		}
		digitalWrite(_clkPin, LOW);
	}
	
	digitalWrite(_clkPin, LOW); //wait for ACK
	digitalWrite(_clkPin, HIGH);
	digitalWrite(_clkPin, LOW);
	
	pinMode(_dataPin, OUTPUT);
	return dat ;
}  

/**
 * \par Function
 *    start
 * \par Description
 *    Send start signal to TM1637
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    None
 * \others
 *    None
 */
void KA_TouchKey::start(void)
{
	digitalWrite(_clkPin, HIGH); //send start signal to TM1637
	digitalWrite(_dataPin, HIGH);
	digitalWrite(_dataPin, LOW);
	digitalWrite(_clkPin, LOW);
}

/**
 * \par Function
 *    stop
 * \par Description
 *    Send the stop signal to TM1637.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \return
 *    None
 * \others
 *    None
 */
void KA_TouchKey::stop(void)
{
	digitalWrite(_clkPin, LOW);
	digitalWrite(_dataPin, LOW);
	digitalWrite(_clkPin, HIGH);
	digitalWrite(_dataPin, HIGH);
}


/**
 * \par Function
 *    coding
 * \par Description
 *    Return display data from look up table.
 * \param[in]
 *    DispData - Data need be transcoded.
 * \par Output
 *    None
 * \return
 *    Return the value of transcoding
 * \par Others
 *    None
 */
uint16_t KA_TouchKey::coding(void)
{
	start();
	writeByte(ASEL_N_READ);
	key = readByte();
	stop();
	return key;	
}

/**
 * \par Function
 *    set
 * \par Description
 *    Set brightness, data and address.
 * \param[in]
 *    brightness - Brightness, defined in KA_TouchKey.h from BRIGHTNESS_0 to BRIGHTNESS_7.
 * \param[in]
 *    SetData - First address for display data
 * \param[in]
 *    SetAddr - First address for display
 * \par Output
 *    Cmd_SetData - Private variable Cmd_SetData of class KA_TouchKey.
 *    Cmd_SetAddr - Private variable Cmd_SetAddr of class KA_TouchKey.
 *    Cmd_DispCtrl - Control command for KA_ 7 Segment Serial Display module.
 * \return
 *    None
 * \par Others
 *    None
 */
void KA_TouchKey::set(uint8_t SetAddr)
{
	Cmd_SetAddr = SetAddr;
}

/**
 * \par Function
 *    coding
 * \par Description
 *    Return display data from look up table.
 * \param[in]
 *    DispData - Data need be transcoded.
 * \par Output
 *    None
 * \return
 *    Return the value of transcoding
 * \par Others
 *    None
 */
 
uint8_t KA_TouchKey::getkey(void)
{
	switch(key)
	{
		case PAD0:return 1;
		case PAD1:return 2;
		case PAD2:return 3;
		case PAD3:return 4;
		case PAD4:return 5;
		case PAD5:return 6;
		case PAD6:return 7;
		case PAD7:return 8;
		case PAD8:return 9;
		case PAD9:return 10;
		case PAD10:return 11;
		case PAD11:return 12;
		default :return 0;
	}
}
 
 /*
uint8_t KA_TouchKey::getkey(void)
{
	int16_t val = analogRead(s2);
	if((122 < val) && (val < 132))
	{
		return 1;
	}
	else if((186 < val) && (val < 196))
	{
		return 2;
	}
	else if((250 < val) && (val < 260))
	{
		return 3;
	}
	else if((314 < val) && (val < 324))
	{
		return 4;
	}
	else if((378 < val) && (val < 388))
	{
		return 5;
	}
	else if((442 < val) && (val < 452))
	{
		return 6;
	}
	else if((506 < val) && (val < 516))
	{
		return 7;
	}
	else if((570 < val) && (val < 580))
	{
		return 8;
	}
	else if((634 < val) && (val < 644))
	{
		return 9;
	}
	else if((698 < val) && (val < 708))
	{
		return 10;
	}
	else if((762 < val) && (val < 772))
	{
		return 11;
	}
	else if((826 < val) && (val < 836))
	{
		return 12;
	}
	else
	{
		return 0;
	}
}
*/