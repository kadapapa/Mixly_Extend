/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   KA_TouchKey
 * \brief   Driver for KA_ 7-Segment Serial Display module.
 * @file    KA_TouchKey.h
 * @author  MakeBlock
 * @version V1.0.4
 * @date    2015/11/12
 * @brief   Header file for KA_TouchKey.cpp.
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
 * Driver for KA_ 7-Segment Serial Display module.
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
 *    13.   void    KA_TouchKey::display(uint8_t BitAddr, uint8_t DispData,);
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
 * Rafael Lee       2015/09/02     1.0.1            Added some comments and macros.
 * Mark Yan         2015/10/29     1.0.2            fix issue when display negative data.
 * Mark Yan         2015/11/09     1.0.3            fix some comments error.
 * Mark Yan         2015/11/12     1.0.4            fix driver API.
 * </pre>
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KA_TOUCHKEY_H
#define __KA_TOUCHKEY_H

//************definitions for TM1637*********************
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "KA_Port.h"

/******************definitions for TM1637**********************/
const uint8_t ASEL_H_ADDR = 0X44;   //Automatic address increment mode
const uint8_t ASEL_L_ADDR = 0X42;   //Automatic address increment mode
const uint8_t ASEL_N_ADDR = 0X40;   //Automatic address increment mode
/**************definitions for brightness***********************/
const uint8_t ASEL_H_READ  = 0X89;   //start address of display register
const uint8_t ASEL_L_READ  = 0X85;   //start address of display register
const uint8_t ASEL_N_READ  = 0X81;   //start address of display register
/**************definitions for brightness***********************/
const uint16_t PAD0  = ~((1 << 15) & 0xFFFF);
const uint16_t PAD1  = ~((1 << 14) & 0xFFFF);
const uint16_t PAD2  = ~((1 << 13) & 0xFFFF);
const uint16_t PAD3  = ~((1 << 12) & 0xFFFF);
const uint16_t PAD4  = ~((1 << 11) & 0xFFFF);
const uint16_t PAD5  = ~((1 << 10) & 0xFFFF);
const uint16_t PAD6  = ~((1 << 9) & 0xFFFF);
const uint16_t PAD7  = ~((1 << 8) & 0xFFFF);
const uint16_t PAD8  = ~((1 << 7) & 0xFFFF);
const uint16_t PAD9  = ~((1 << 6) & 0xFFFF);
const uint16_t PAD10 = ~((1 << 5) & 0xFFFF);
const uint16_t PAD11 = ~((1 << 4) & 0xFFFF);

/**************definitions for brightness***********************/

/**** definitions for the clock point of the digit tube *******/

/**** definitions for the clock point of the digit tube *******/

///@brief Class for numeric display module

/**
 * Class: KA_Digitron
 * \par Description
 * Declaration of Class KA_Digitron.
 */


/**
 * Class: KA_TouchKey
 * \par Description
 * Declaration of Class KA_TouchKey.
 */

class KA_TouchKey :public KA_Port
{
public:

/**
 * Alternate Constructor which can call your own function to map the 7-Segment display to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  KA_TouchKey(void);
  
/**
 * Alternate Constructor which can call your own function to map the 7-Segment display to arduino port,
 * the slot1 will be used for data pin and slot2 will used for clk pin.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  KA_TouchKey(uint8_t port);
  
/**
 * Alternate Constructor which can call your own function to map the 7-Segment display to arduino port. 
 * \param[in]
 *    dataPin - The DATA pin for Seven-Segment LED module(arduino port).
 * \param[in]
 *    clkPin - The CLK pin for Seven-Segment LED module(arduino port).
 */
  KA_TouchKey(uint8_t dataPin, uint8_t clkPin);
  
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
  void reset(void);
  
  
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
  void set(uint8_t = ASEL_N_READ);// Take effect next display cycle.
  
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
  void setpin(uint8_t dataPin, uint8_t clkPin);
  

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
  uint16_t coding(void);
  
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
  uint8_t getkey(void); 
  
private:

  uint8_t Cmd_SetAddr;
  uint8_t _clkPin;
  uint8_t _dataPin;
  uint16_t key;
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
  void writeByte(uint8_t wr_data);// Write 8 bits data to tm1637.

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
  uint16_t readByte(void);  

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
  void start(void);// Send start bits

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
  void stop(void); // Send stop bits.

};
#endif
