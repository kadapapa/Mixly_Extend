/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class KA_Serial
 * \brief   Driver for serial.
 * @file    KA_Serial.cpp
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
 *    1. void KA_Serial::setHardware(bool mode)
 *    2. void KA_Serial::begin(long baudrate)
 *    3. void KA_Serial::end(void)
 *    4. size_t KA_Serial::write(uint8_t byte)
 *    5. int16_t KA_Serial::read(void)
 *    6. int16_t KA_Serial::available(void)
 *    7. bool KA_Serial::listen(void)
 *    8. bool KA_Serial::isListening(void)
 *    9. int16_t KA_Serial::poll(void)
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
#include "KA_Serial.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * Alternate Constructor which can call your own function to map the serial to arduino port,
 * no pins are used or initialized here. hardware serial will be used by default.
 * \param[in]
 *   None
 */
KA_Serial::KA_Serial(void) : KA_Port()//, SoftwareSerial(NC, NC)
{
  _hard = true;
  _scratch = true;
  _polling = false;
}

/**
 * Alternate Constructor which can call your own function to map the serial to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
KA_Serial::KA_Serial(uint8_t port) : KA_Port(port)//, SoftwareSerial(ka_Port[port].s2, ka_Port[port].s1)
{
  _scratch = false;
  _hard = false;
  _polling = false;
  _RxPin = s2;
  _TxPin = s1;
#if defined(__AVR_ATmega32U4__)
  //_polling = getPort() > PORT_5;
   _polling = false;
  _hard = getPort() == PORT_4;
#else
  _hard = getPort() == PORT_5;
#endif
}

/**
 * Alternate Constructor which can call your own function to map the serial to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   receivePin - the rx pin of serial(arduino port)
 * \param[in]
 *   transmitPin - the tx pin of serial(arduino port)
 * \param[in]
 *   inverse_logic - Whether the Serial level need inv.
 */
 /*
//KA_Serial::KA_Serial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic)\
//                  : SoftwareSerial(receivePin, transmitPin, inverse_logic)
*/
 KA_Serial::KA_Serial(uint8_t receivePin, uint8_t transmitPin)
{
  _scratch = false;
  _hard = false;
  _polling = false;
  _RxPin = receivePin;
  _TxPin = transmitPin;
#if defined(__AVR_ATmega32U4__)
   _polling = false;
  if((receivePin == 0) && (transmitPin == 1))
  {
    _hard = true;
  }
  else
  {
    _hard = false;
  }
#else
  if((receivePin == 0) && (transmitPin == 1))
  {
    _hard = true;
  }
  else
  {
    _hard = false;
  }
#endif
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
void KA_Serial::setHardware(bool mode)
{
  _hard = mode;
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
void KA_Serial::begin(long baudrate)
{
  _bitPeriod = 1000000 / baudrate;
  if (_hard)
  {
#if defined(__AVR_ATmega32U4__)
    _scratch ? Serial.begin(baudrate) : Serial1.begin(baudrate);
#elif defined(__AVR_ATmega2560__)
    Serial2.begin(baudrate);
#else
    Serial.begin(baudrate);
#endif
  }
  else
  {
//    SoftwareSerial::begin(baudrate);
  }
}

/**
 * \par Function
 *   end
 * \par Description
 *   Stop listening and release the object
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void KA_Serial::end(void)
{
  if (_hard)
  {
#if defined(__AVR_ATmega32U4__)
    Serial1.end();
#elif defined(__AVR_ATmega2560__)
    Serial2.end();
#else
    Serial.end();
#endif
  }
  else
  {
//    SoftwareSerial::end();
  }
}

/**
 * \par Function
 *   write
 * \par Description
 *   Writes binary data to the serial port. This data is sent as a byte or series of bytes; 
 * \param[in]
 *   byte - a value to send as a single byte
 * \par Output
 *   None
 * \return
 *   it will return the number of bytes written, though reading that number is optional
 * \par Others
 *   None
 */
size_t KA_Serial::write(uint8_t byte)
{
  if (_hard)
  {
#if defined(__AVR_ATmega32U4__)
    return (_scratch ? Serial.write(byte) : Serial1.write(byte) );
#elif defined(__AVR_ATmega2560__)
    return (Serial2.write(byte) );
#else
    return (Serial.write(byte) );
#endif
  }
  else
  {
//    return (SoftwareSerial::write(byte) );
  }
  return (Serial.write(byte) );
}

/**
 * \par Function
 *   read
 * \par Description
 *   Return a character that was received on the RX pin of the software serial port. 
 *   Note that only one SoftwareSerial instance can receive incoming data at a time 
 *  (select which one with the listen() function).
 * \par Output
 *   None
 * \return
 *   The character read, or -1 if none is available
 * \par Others
 *   None
 */
int16_t KA_Serial::read(void)
{
  if (_polling)
  {
    int16_t temp = _byte;
    _byte = -1;
    return (temp > -1 ? temp : poll() );
  }
  if (_hard)
  {
#if defined(__AVR_ATmega32U4__)
    return (_scratch ? Serial.read() : Serial1.read() );
#elif defined(__AVR_ATmega2560__)
    return (Serial2.read() );
#else
    return (Serial.read() );
#endif
  }
  else
  {
//    return (SoftwareSerial::read() );
  }
  return (Serial.read() );
}

/**
 * \par Function
 *   available
 * \par Description
 *   Get the number of bytes (characters) available for reading from a software
 *   serial port. This is data that's already arrived and stored in the serial 
 *   receive buffer.
 * \par Output
 *   None
 * \return
 *   The number of bytes available to read
 * \par Others
 *   None
 */
int16_t KA_Serial::available(void)
{
  if (_polling)
  {
    _byte = poll();
    return (_byte > -1 ? 1 : 0);
  }
  if (_hard)
  {
#if defined(__AVR_ATmega32U4__)
    return (_scratch ? Serial.available() : Serial1.available() );
#elif defined(__AVR_ATmega2560__)
    return (Serial2.available() );
#else
    return (Serial.available() );
#endif
  }
  else
  {
//    return (SoftwareSerial::available() );
  }
  return (Serial.available() );
}

/**
 * \par Function
 *   listen
 * \par Description
 *   Enables the selected software serial port to listen, used for software serial.
 *   Only one software serial port can listen at a time; data that arrives for other 
 *   ports will be discarded. Any data already received is discarded during the call 
 *   to listen() (unless the given instance is already listening).
 * \par Output
 *   None
 * \return
 *   This function sets the current object as the "listening"
 *   one and returns true if it replaces another
 * \par Others
 *   None
 */
bool KA_Serial::listen(void)
{
  if (_hard)
  {
    return (true);
  }
  else
  {
//    return (SoftwareSerial::listen() );
  }
    return false;
}

/**
 * \par Function
 *   isListening
 * \par Description
 *   Tests to see if requested software serial port is actively listening.
 * \par Output
 *   None
 * \return
 *   Returns true if we were actually listening.
 * \par Others
 *   None
 */
bool KA_Serial::isListening(void)
{
  if (_hard)
  {
    return (true);
  }
  else
  {
//    return (SoftwareSerial::isListening() );
  }
  return false;
}

/**
 * \par Function
 *   poll
 * \par Description
 *   If we used the serial as software serial port, and set the _polling mask true.
 *   we beed use this function to read the serial data.
 * \par Output
 *   None
 * \return
 *   The character read, or -1 if none is available
 * \par Others
 *   None
 */
int16_t KA_Serial::poll(void)
{
  int16_t val = 0;
  int16_t bitDelay = _bitPeriod - clockCyclesToMicroseconds(50);
  if (digitalRead(_RxPin) == LOW)
  {
    for (int16_t offset = 0; offset < 8; offset++)
    {
      delayMicroseconds(bitDelay);
      val |= digitalRead(_RxPin) << offset;
    }
    delayMicroseconds(bitDelay);
    return (val & 0xff);
  }
  return (-1);
}

/**
 * \par Function
 *   sendString
 * \par Description
 *   Send a string as a series of bytes, used for printf().
 * \param[in]
 *   str - A string to send as a series of bytes
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void KA_Serial::sendString(char *str)
{
  while(*str)
  {
    write(*str++);
  }
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
void KA_Serial::printf(char *fmt,...)
{
  va_list ap;
  char string[128];
  va_start(ap,fmt);
  vsprintf(string,fmt,ap);
  sendString(string);
  va_end(ap);
}

boolean KA_Serial::dataLineAvailable(void)
{
  if(available())
  {
    char c = read();
    if(c=='\n')
    {
      buffer[bufferIndex] = 0;
      return true;
    }
    else
    {
      buffer[bufferIndex]=c;
      bufferIndex++;
    }
  }
  return false;
}

String KA_Serial::readDataLine(void)
{
  if(bufferIndex>0)
  {
    lastLine = buffer;
  }
  bufferIndex = 0;
  memset(buffer,0,64);
  return lastLine;
}

float KA_Serial::getValue(String key)
{
  String s = readDataLine();
  if(stringLength(s)>2)
  {
    char * tmp;
    char * str;
    str = strtok_r((char*)s.c_str(), "=", &tmp);
    if(str!=NULL && strcmp(str,key.c_str())==0)
    {
      float v = atof(tmp);
      return v;
    }
  }
  return 0;
}

boolean KA_Serial::equalString(String s1,String s2)
{
  return s1.equals(s2);
}

String KA_Serial::concatenateWith(String s1,String s2)
{
  return s1+s2;
}

char KA_Serial::letterOf(int i,String s)
{
  return s.charAt(i);
}

int KA_Serial::stringLength(String s)
{
  return s.length();
}
