/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class KA_AirMonitors
 * \brief   Driver for serial.
 * @file    KA_AirMonitors.cpp
 * @author  MakeBlock
 * @version V1.0.1
 * @date    2016/01/20
 * @brief   this file is a drive for serial
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
 * This file is a drive for serial, It support hardware and software serial
 *
 * \par KA_thod List:
 *
 *    1. void KA_AirMonitors::setHardware(bool mode)
 *    2. void KA_AirMonitors::begin(long baudrate)
 *    3. void KA_AirMonitors::end(void)
 *    4. size_t KA_AirMonitors::write(uint8_t byte)
 *    5. int16_t KA_AirMonitors::read(void)
 *    6. int16_t KA_AirMonitors::available(void)
 *    7. bool KA_AirMonitors::listen(void)
 *    8. bool KA_AirMonitors::isListening(void)
 *    9. int16_t KA_AirMonitors::poll(void)
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan         2015/09/08     1.0.0            Rebuild the old lib.
 * Mark Yan         2016/01/20     1.0.1            support arduino pin-setting.
 * </pre>
 * @example KA_SerialReceiveTest.ino
 * @example KA_SerialTransmitTest.ino
 */
#include "KA_AirMonitors.h"
/**
 * Alternate Constructor which can call your own function to map the serial to arduino port,
 * no pins are used or initialized here. hardware serial will be used by default.
 * \param[in]
 *   None
 */
KA_AirMonitors::KA_AirMonitors(void) : KA_Port()
{

}

/**
 * Alternate Constructor which can call your own function to map the serial to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
KA_AirMonitors::KA_AirMonitors(uint8_t port) : KA_Port(port)
{

}

/**
 * \par Function
 *   setHardware
 * \par Description
 *   if need change the hardware and software serial, this function can be used.
 * \param[in]
 *   mode - if need use hardware serial this value should set to true, or set it false.
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void KA_AirMonitors::readSerial(void)
{
	isAvailable1 = false;
	for(uint8_t i = 0;Serial1.available() > 0 && i < 16;i++)// && Serial.find("BI"))
	{
		isAvailable1 = true;
		Byte_Buffer[i] = Serial1.read();
		delay(1);
	}	
}

/**
 * \par Function
 *   begin
 * \par Description
 *   Sets the speed (baud rate) for the serial communication. Supported baud 
 *   rates are 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 
 *   38400, 57600, and 115200.
 * \param[in]
 *   baudrate - he baud rate (long)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void KA_AirMonitors::begin()
{
	Serial1.begin(9600);	
}

/**
 * \par Function
 *   begin
 * \par Description
 *   Sets the speed (baud rate) for the serial communication. Supported baud 
 *   rates are 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 
 *   38400, 57600, and 115200.
 * \param[in]
 *   baudrate - he baud rate (long)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void KA_AirMonitors::begin(uint8_t index)
{
	switch(index)
	{
		case 1:Serial1.begin(115200);break;
		case 2:Serial1.begin(115200);break;
		default:Serial1.begin(9600);break;
	}
}

/**
 * \par Function
 *   analysis
 * \par Description
 *   Return a character that was received on the RX pin of the software serial port. 
 *   Note that only one SoftwareSerial instance can receive incoming data at a time 
 *  (select which one with the listen() function).
 * \par Output
 *   None
 * \return
 *   The character analysis, or -1 if none is available
 * \par Others
 *   None
 */
void KA_AirMonitors::analysis(void)
{	
	readSerial();
    if(isAvailable1)
    {
		for(uint8_t i = 0,c = 0;i < 16;i++)
		{
			c = Byte_Buffer[i] & 0xff;
			if((c == 0x18) && (isStart == false))
			{
				if(prevc == 0xff)
				{
					index = 1;
					isStart = true;
				}
			}
			else
			{
				prevc = c; // 00 63 63 00 01 03 vf
				if(isStart)
				{
					buffer[index] = c;
					
					if(index < 7)
					{
						checksum += c;
					}
					else if(index == 7)
					{	
						uint8_t v = ~checksum + 1;
						if(c == v)
						{
//							parseData();
							PM25H = readBuffer(2);
							PM25L = readBuffer(3);
							PM25 = (((PM25H & 0xffff) << 8) + PM25L);	
							TVOC = readBuffer(6);
							break;
						}
					}

					index++;
				}
			}
		}
		index = 0;
		checksum = 0x18;
		isStart = false;		
    }
}


  /**
 * \par Function
 *   analysis
 * \par Description
 *   Return a character that was received on the RX pin of the software serial port. 
 *   Note that only one SoftwareSerial instance can receive incoming data at a time 
 *  (select which one with the listen() function).
 * \par Output
 *   None
 * \return
 *   The character analysis, or -1 if none is available
 * \par Others
 *   None
 */  
void KA_AirMonitors:: parseData(void)
{
	/**************************************************
		42     4D     len0   len1.......PM1.0H PM1.0L PM2.5H PM2.5L PM10H PM10L.......METHANAL  checksum
		0      1      2      3   .......10     11     12     13     14    15   .......28   29   30   31
		0x42   0x4D   0x00   0x1c.......0x02   0x22   0x09   0x00   0x00   0x0a
    ***************************************************/
	PM25H = readBuffer(2);
	PM25L = readBuffer(3);
	PM25 = (((PM25H & 0xffff) << 8) + PM25L);	
	TVOC = readBuffer(6);
}

  /**
 * \par Function
 *   analysis
 * \par Description
 *   Return a character that was received on the RX pin of the software serial port. 
 *   Note that only one SoftwareSerial instance can receive incoming data at a time 
 *  (select which one with the listen() function).
 * \par Output
 *   None
 * \return
 *   The character analysis, or -1 if none is available
 * \par Others
 *   None
 */ 
String KA_AirMonitors:: getPM25Value()
{
	if((PM25H > 0) && (PM25H <= 2))
	{
		return "Best";
	}
	else if((PM25H > 2) && (PM25H <= 4))
	{
		return "Good";
	}
	else if((PM25H > 4) && (PM25H <= 6))
	{
		return "Moderate";
	}
	else if(PM25H > 6)
	{
		return "Bad";
	}
	else
	{
		return "NULL";
	}
}

  /**
 * \par Function
 *   analysis
 * \par Description
 *   Return a character that was received on the RX pin of the software serial port. 
 *   Note that only one SoftwareSerial instance can receive incoming data at a time 
 *  (select which one with the listen() function).
 * \par Output
 *   None
 * \return
 *   The character analysis, or -1 if none is available
 * \par Others
 *   None
 */ 
String KA_AirMonitors:: getTVOCValue()
{
	switch(TVOC)
	{
		case 0x00: return "Best";
		case 0x01: return "Good";
		case 0x02: return "Moderate";
		case 0x03: return "Bad";
		default:   return "NULL";
	}
}

  /**
 * \par Function
 *   analysis
 * \par Description
 *   Return a character that was received on the RX pin of the software serial port. 
 *   Note that only one SoftwareSerial instance can receive incoming data at a time 
 *  (select which one with the listen() function).
 * \par Output
 *   None
 * \return
 *   The character analysis, or -1 if none is available
 * \par Others
 *   None
 */ 
String KA_AirMonitors::getValue(uint8_t index)
{
	if(index == 2)
	{
		return getPM25Value();
	}
	else if(index == 4)
	{
		return getTVOCValue();
	}

	return "Error";
}


/**
 * \par Function
 *   printf
 * \par Description
 *   Printf format string (of which "printf" stands for "print formatted") 
 *   refers to a control parameter used by a class of functions in the 
 *   string-processing libraries of various programming languages.
 * \param[in]
 *   fmt - A string that specifies the format of the output. The formatting 
 *   string determines what additional arguments you need to provide.
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
uint8_t KA_AirMonitors:: readBuffer(unsigned char index)
{
    return buffer[index];
}
