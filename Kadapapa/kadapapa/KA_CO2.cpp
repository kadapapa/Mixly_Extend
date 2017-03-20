/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class KA_CO2
 * \brief   Driver for serial.
 * @file    KA_CO2.cpp
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
 *    1. void KA_CO2::setHardware(bool mode)
 *    2. void KA_CO2::begin(long baudrate)
 *    3. void KA_CO2::end(void)
 *    4. size_t KA_CO2::write(uint8_t byte)
 *    5. int16_t KA_CO2::read(void)
 *    6. int16_t KA_CO2::available(void)
 *    7. bool KA_CO2::listen(void)
 *    8. bool KA_CO2::isListening(void)
 *    9. int16_t KA_CO2::poll(void)
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
#include "KA_CO2.h"

/**
 * Alternate Constructor which can call your own function to map the serial to arduino port,
 * no pins are used or initialized here. hardware serial will be used by default.
 * \param[in]
 *   None
 */
KA_CO2::KA_CO2(void) : KA_Port()
{

}

/**
 * Alternate Constructor which can call your own function to map the serial to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
KA_CO2::KA_CO2(uint8_t port) : KA_Port(port)
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
void KA_CO2::readSerial(void)
{
	isAvailable1 = false;
	for(uint8_t i = 0;(Serial1.available() > 0) && (i < 24);i++)
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
void KA_CO2::begin()
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
void KA_CO2::begin(uint8_t index)
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
void KA_CO2::analysis(void)
{	
	readSerial();
    if(isAvailable1)
    {
		for(uint8_t i = 0,c = 0;i < 65;i++)
		{
			c = Byte_Buffer[i] & 0xff;
			if(c == 0x86 && isStart == false)
			{
				if(prevc == 0xff)
				{
					index = 1;
					isStart = true;
				}
			}
			else
			{
				prevc = c; //42 4d 00 05 67 45 23 -- --
				if(isStart)
				{
					buffer[index] = c;
					dataLen--;
					if(dataLen)
					{
						checksum += c;
					}
				}
			}
			index++;
			if((isStart && dataLen == 0) || (index > 34))
			{	

				dataLen = 0x07;
				isStart = false;
				index = 0;
				if(verify())
				{				
					Value_CO2  = ((readBuffer(2) & 0xffff) << 8) + readBuffer(3);			
				}
				checksum = 0x86;
				break;
			}
		}
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
boolean KA_CO2::verify(void)
{	
	if((0xff - checksum) + 0x01 == readBuffer(8))
	{
		return true;
	}
	return false;
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
void KA_CO2:: parseData(void)
{
	/**************************************************
		42     4D     len0   len1.......PM1.0H PM1.0L PM2.5H PM2.5L PM10H PM10L.......METHANAL  checksum
		0      1      2      3   .......10     11     12     13     14    15   .......28   29   30   31
		0x42   0x4D   0x00   0x1c.......0x02   0x22   0x09   0x00   0x00   0x0a
    ***************************************************/
//	Value_CO2  = ((readBuffer(10) & 0xffff) << 8) + readBuffer(11);
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
uint16_t KA_CO2:: getValue(uint8_t index)
{
	writeCmd(index);
	delay(80);
	analysis();
	return Value_CO2;
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
uint8_t KA_CO2:: readBuffer(uint8_t index)
{
    return buffer[index];
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
void KA_CO2:: writeCmd(unsigned char index)
{
	switch(index)
	{
		case 1:
			for(uint8_t i = 0;i < 16; i++)
			{
				Serial1.write(CMD1[i]);
			};break;
		case 2:
			for(uint8_t i = 0;i < 16; i++)
			{
				Serial1.write(CMD2[i]);
			};break;		
		default:
			for(uint8_t i = 0;i < 16; i++)
			{
				Serial1.write(CMD[i]);
			};break;		
	}
}

