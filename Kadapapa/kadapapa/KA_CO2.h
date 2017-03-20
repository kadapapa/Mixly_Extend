/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class KA_CO2
 * \brief   Driver for serial.
 * @file    KA_CO2.h
 * @author  MakeBlock
 * @version V1.0.1
 * @date    2015/01/20
 * @brief   Header for for KA_CO2.cpp module
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
 */
#ifndef __KA_CO2_H
#define __KA_CO2_H

#include <Arduino.h>
#include <stdint.h>
#include <stdbool.h>
#include "KA_Port.h"

/**
 * Class: KA_CO2
 * \par Description
 * Declaration of Class KA_CO2.
 */

class KA_CO2 : public KA_Port
{
public:
/**
 * Alternate Constructor which can call your own function to map the serial to arduino port,
 * no pins are used or initialized here. hardware serial will be used by default.
 * \param[in]
 *   None
 */
  KA_CO2(void);
	
/**
 * Alternate Constructor which can call your own function to map the serial to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  KA_CO2(uint8_t port);

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
  void begin();
  
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
  void begin(uint8_t index);

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
  void analysis(void);
  
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
  void parseData(void);
 
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
 uint16_t getValue(uint8_t index);


 void writeCmd(uint8_t index);
  
private:
	boolean isStart = false;
	boolean isAvailable1 = false;
	
	const uint8_t CMD[16]  = {0XFF,0X01,0X86,0X00,0X00,0X00,0X00,0X00,0X79,0X00,0X00,0X00,0X00,0X00,0X00,0X00};
	const uint8_t CMD1[16] = {0XFF,0XFF,0X10,0X00,0X01,0XFF,0X01,0X86,0X00,0X00,0X00,0X00,0X00,0X79,0X32,0X28};
	const uint8_t CMD2[16] = {0XFF,0XFF,0X10,0X00,0X02,0XFF,0X01,0X86,0X00,0X00,0X00,0X00,0X00,0X79,0XC2,0X27};
	
	uint8_t checksum = 0x86;
	uint8_t dataLen = 0x07;
	uint8_t Byte_Buffer[65];
	uint8_t buffer[33];
	uint8_t index = 0;
	uint8_t prevc;
	uint8_t serialRead;
	
	uint16_t Value_CO2;

	void readSerial(void);
	boolean verify(void);
	uint8_t readBuffer(unsigned char index);
};
#endif

