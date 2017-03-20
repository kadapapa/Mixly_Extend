/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   KA_Digitron
 * \brief   Driver for KA_ 7-Segment Serial Display module.
 * @file    KA_Digitron.h
 * @author  MakeBlock
 * @version V1.0.4
 * @date    2015/11/12
 * @brief   Header file for KA_Digitron.cpp.
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
 *    1.    void    KA_Digitron::init(void);
 *    2.    void    KA_Digitron::set(uint8_t brightness, uint8_t SetData, uint8_t SetAddr);
 *    3.    void    KA_Digitron::reset(uint8_t port);
 *    4.    void    KA_Digitron::setpin(uint8_t dataPin, uint8_t clkPin);
 *    5.    void    KA_Digitron::write(uint8_t SegData[]);
 *    6.    void    KA_Digitron::write(uint8_t BitAddr, uint8_t SegData);
 *    7.    void    KA_Digitron::display(uint16_t value);
 *    8.    void    KA_Digitron::display(int16_t value);
 *    9.    void    KA_Digitron::display(float value);
 *    10.   int16_t KA_Digitron::checkNum(float v,int16_t b);
 *    11.   void    KA_Digitron::display(double value, uint8_t digits);
 *    12.   void    KA_Digitron::display(uint8_t DispData[]);
 *    13.   void    KA_Digitron::display(uint8_t BitAddr, uint8_t DispData,);
 *    14.   void    KA_Digitron::display(uint8_t BitAddr, uint8_t DispData, uint8_t point_on);
 *    15.   void    KA_Digitron::clearDisplay(void);
 *    16.   void    KA_Digitron::setBrightness(uint8_t brightness);
 *    17.   void    KA_Digitron::coding(uint8_t DispData[]);
 *    18.   uint8_t KA_Digitron::coding(uint8_t DispData);
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
#ifndef __KA_DIGITRON_H
#define __KA_DIGITRON_H

//************definitions for TM1637*********************
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "KA_Port.h"

/* Exported constants --------------------------------------------------------*/
/******************definitions for TM1637**********************/
const uint8_t SEG_ADDR   = 0X48;   //Automatic address increment mode
const uint8_t KEY_ADDR   = 0X49;   //Fixed address mode
/**************definitions for brightness***********************/
const uint8_t BRIGHTNESS_0 = 0X00;
const uint8_t BRIGHTNESS_1 = 0X10;
const uint8_t BRIGHTNESS_2 = 0X20;
const uint8_t BRIGHTNESS_3 = 0X30;
const uint8_t BRIGHTNESS_4 = 0X40;
const uint8_t BRIGHTNESS_5 = 0X50;
const uint8_t BRIGHTNESS_6 = 0X60;
const uint8_t BRIGHTNESS_7 = 0X70;
/**************definitions for brightness***********************/
const uint8_t SEGMENT_7 = 0X08;
const uint8_t SEGMENT_8 = 0X00;
/**** definitions for the clock point of the digit tube *******/
const uint8_t SEGDIS_ON  = 0X01;   //diplay on
const uint8_t SEGDIS_OFF = 0X00;   //diplay off
/**************definitions for brightness***********************/
const uint8_t SEGDIS_ADDR_1  = 0X68;   //start address of display register
const uint8_t SEGDIS_ADDR_2  = 0X6A;   //start address of display register
const uint8_t SEGDIS_ADDR_3  = 0X6C;   //start address of display register
const uint8_t SEGDIS_ADDR_4  = 0X6E;   //start address of display register
/**** definitions for the clock point of the digit tube *******/
const uint8_t POINT_ON  = 0X01;
const uint8_t POINT_OFF = 0X00;
///@brief Class for numeric display module

/**
 * Class: KA_Digitron
 * \par Description
 * Declaration of Class KA_Digitron.
 */

class KA_Digitron :public KA_Port
{
public:
/**
 * Alternate Constructor which can call your own function to map the 7-Segment display to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  KA_Digitron(void);
  
/**
 * Alternate Constructor which can call your own function to map the 7-Segment display to arduino port,
 * the slot1 will be used for data pin and slot2 will used for clk pin.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  KA_Digitron(uint8_t port);
  
/**
 * Alternate Constructor which can call your own function to map the 7-Segment display to arduino port. 
 * \param[in]
 *    dataPin - The DATA pin for Seven-Segment LED module(arduino port).
 * \param[in]
 *    clkPin - The CLK pin for Seven-Segment LED module(arduino port).
 */
  KA_Digitron(uint8_t dataPin, uint8_t clkPin);
  
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
  void reset();
  
/**
 * \par Function
 *    init
 * \par Description
 *    Initialization the display, here just call function clearDisplay.
 * \par Output  
 *    None
 * \return
 *    None
 * \others
 *    None
 */
  void init(void); // Clear display
  
/**
 * \par Function
 *    set
 * \par Description
 *    Set brightness, data and address.
 * \param[in]
 *    brightness - Brightness, defined in KA_Digitron.h from BRIGHTNESS_0 to BRIGHTNESS_7.
 * \param[in]
 *    SetData - First address for display data
 * \param[in]
 *    SetAddr - First address for display
 * \par Output
 *    Cmd_SetData - Private variable Cmd_SetData of class KA_Digitron.
 *    Cmd_SetAddr - Private variable Cmd_SetAddr of class KA_Digitron.
 *    Cmd_DispCtrl - Control command for KA_ 7 Segment Serial Display module.
 * \return
 *    None
 * \par Others
 *    None
 */
  void set(uint8_t = BRIGHTNESS_0, uint8_t = SEG_ADDR, uint8_t = SEGDIS_ADDR_1);// Take effect next display cycle.
  
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
 *    write
 * \par Description
 *    White data array to certain address.
 * \param[in]
 *    SegData[] - Data array to write to module.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void write(uint8_t SegData[]);
  
/**
 * \par Function
 *    write
 * \par Description
 *    Write data to certain address.
 * \param[in]
 *    BitAddr - Bit address of data.
 * \param[in]
 *    SegData - Data to display.
 * \par Output
 *    None
 * \return
 *    None
 * \others
 *    None
 */
  void write(uint8_t BitAddr, uint8_t SegData);
  
/**
 * \par Function
 *    display
 * \par Description
 *    Display certain value, and this value type is uint16_t
 * \param[in]
 *    value - Value to display.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(uint16_t value);
  
/**
 * \par Function
 *    display
 * \par Description
 *    Display certain value, and this value type is int16_t
 * \param[in]
 *    value - Value to display.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(int16_t value);

/**
 * \par Function
 *    display
 * \par Description
 *    Display certain value, and this value type is float
 * \param[in]
 *    value - Value to display.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(float value);

/**
 * \par Function
 *    checkNum
 * \par Description
 *    Extraction values to be displayed of float data
 * \param[in]
 *    v - Value to display.
 * \param[in]
 *    b - Value to display.
 * \par Output
 *    None
 * \return
 *    The data removal of the decimal point
 * \par Others
 *    None
 */
  int16_t checkNum(float v,int16_t b);

/**
 * \par Function
 *    display
 * \par Description
 *    Display double number.
 * \param[in]
 *    value - Value to display.
 * \param[in]
 *    digits - Number of digits to display.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(double value, uint8_t = 1);

/**
 * \par Function
 *    display
 * \par Description
 *    Display 8 bit number array.
 * \param[in]
 *    DispData[] - The data that needs to be displayed store in this array.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(uint8_t DispData[]);

/**
 * \par Function
 *    display
 * \par Description
 *    Display data to certain digit.
 * \param[in]
 *    BitAddr - Address to display.
 * \param[in]
 *    DispData - Data to display.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */
  void display(uint8_t BitAddr, uint8_t DispData);

/**
 * \par Function
 *    display
 * \par Description
 *    Display data to certain digit.
 * \param[in]
 *    BitAddr - Address to display.
 * \param[in]
 *    DispData - Data to display.
 * \param[in]
 *    point_on - Display the point or not.
 * \par Output
 *    None
 * \return
 *    None
 * \par Others
 *    None
 */ 
  void display(uint8_t BitAddr, uint8_t DispData, uint8_t point_on);

/**
 * \Function
 *    clearDisplay
 * \Description
 *    Clear display.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void clearDisplay(void);
  
/**
 * \par Function
 *    setBrightness
 * \par Description
 *    Set brightness.
 * \param[in]
 *    brightness - Brightness, defined in KA_Digitron.h from BRIGHTNESS_0 to BRIGHTNESS_7.
 * \par Output
 *    Cmd_DispCtrl - Control command for KA_ 7 Segment Serial Display module.
 * \return
 *    None
 * \par Others
 *    None
 */
  void setBrightness(uint8_t brightness);
  
/**
 * \par Function
 *    coding
 * \par Description
 *    Set display data using look up table.
 * \param[in]
 *    DispData[] - DataArray to display.
 * \par Output
 *    DispData[] - DataArray be transcoded.
 * \return
 *    None
 * \par Others
 *    None
 */
  void coding(uint8_t DispData[]);

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
  uint8_t coding(uint8_t DispData);
  
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
  uint8_t Cmd_SetData;
  uint8_t Cmd_SetAddr;
  uint8_t Cmd_DispCtrl;
  uint8_t _clkPin;
  uint8_t _dataPin;
  bool _PointFlag; //_PointFlag=1:the clock point on

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
  uint8_t readByte(void);  

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
  void point(bool PointFlag);// Whether to light the clock point ":". Take effect next display cycle.
};
#endif
