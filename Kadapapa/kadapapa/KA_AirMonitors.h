/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class KA_AirMonitors
 * \brief   Driver for serial.
 * @file    KA_AirMonitors.h
 * @author  MakeBlock
 * @version V1.0.1
 * @date    2015/01/20
 * @brief   Header for for KA_AirMonitors.cpp module
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
 */
#ifndef __KA_AIRMONITORS_H
#define __KA_AIRMONITORS_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "KA_Port.h"

/**
 * Class: KA_AirMonitors
 * \par Description
 * Declaration of Class KA_AirMonitors.
 */

class KA_AirMonitors : public KA_Port
{
public:
/**
 * Alternate Constructor which can call your own function to map the serial to arduino port,
 * no pins are used or initialized here. hardware serial will be used by default.
 * \param[in]
 *   None
 */
  KA_AirMonitors(void);
	
/**
 * Alternate Constructor which can call your own function to map the serial to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  KA_AirMonitors(uint8_t port);

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
String getPM25Value(void);

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
String getTVOCValue(void);

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
String getValue(uint8_t index);
  
private:
	boolean isStart = false;
	boolean isAvailable1 = false;
	uint8_t checksum = 0x18;
	uint8_t Byte_Buffer[65];
	uint8_t buffer[33];
	uint8_t index = 0;
	uint8_t prevc;
	uint8_t serialRead;
	
	uint16_t PM25;
	uint8_t  PM25H;
	uint8_t  PM25L;
	uint8_t  TVOC;

	void readSerial(void);
	uint8_t readBuffer(unsigned char index);
};
#endif

