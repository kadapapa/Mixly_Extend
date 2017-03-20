/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class KA_Ultrasonic
 * \brief   Driver for KA_ ultrasonic sensor device.
 * @file    KA_Ultrasonic.cpp
 * @author  MakeBlock
 * @version V1.0.2
 * @date    2016/06/25
 * @brief   Driver for KA_ ultrasonic sensor device.
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
 * This file is a drive for KA_ ultrasonic sensor device, It supports ultrasonic sensor
 * V3.0 provided by the MakeBlock.
 *
 * \par KA_thod List:
 *
 *    1. void KA_Ultrasonic::setpin(uint8_t SignalPin)
 *    2. double KA_Ultrasonic::distanceCm(uint16_t MAXcm)
 *    3. double KA_Ultrasonic::distanceInch(uint16_t MAXinch)
 *    4. long KA_Ultrasonic::measure(unsigned long timeout)
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan         2015/09/04     1.0.0            Rebuild the old lib.
 * Mark Yan         2015/11/16     1.0.1            Increase 100us delay, avoid ultrasonic read exception.
 * Mark Yan         2016/06/25     1.0.2            Modify Read mechanism of ultrasonic waves.
 * </pre>
 *
 * @example UltrasonicSensorTest.ino
 */
#include "KA_Ultrasonic.h"

/**
 * Alternate Constructor which can call your own function to map the ultrasonic sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
KA_Ultrasonic::KA_Ultrasonic(void) : KA_Port(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the ultrasonic Sensor to arduino port,
 * it will assigned the signal pin.
 * \param[in]
 *   port - arduino port(should analog pin)
 */
KA_Ultrasonic::KA_Ultrasonic(uint8_t port) : KA_Port(port)
{
  _SignalPin = s2;
  _lastEnterTime = millis();
  _measureFlag = true;
  _measureValue = 0;
}

/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset the ultrasonic Sensor available PIN by its arduino port.
 * \param[in]
 *   SignalPin - arduino port for sensor read(should analog pin)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void KA_Ultrasonic::setpin(uint8_t SignalPin)
{
  _SignalPin = SignalPin;
  _lastEnterTime = millis();
  _measureFlag = true;
  _measureValue = 0;
  s2 = _SignalPin;
}

/**
 * \par Function
 *   distanceCm
 * \par Description
 *   Centimeters return the distance
 * \param[in]
 *   MAXcm - The Max centimeters can be measured, the default value is 400.
 * \par Output
 *   None
 * \return
 *   The distance measurement in centimeters
 * \par Others
 *   None
 */
double KA_Ultrasonic::distanceCm(uint16_t MAXcm)
{
  long distance = measure(MAXcm * 55 + 200);
  return( (double)distance / 58.0);
}

/**
 * \par Function
 *   distanceInch
 * \par Description
 *   Inch return the distance
 * \param[in]
 *   MAXinch - The Max inch can be measured, the default value is 180.
 * \par Output
 *   None
 * \return
 *   The distance measurement in inch
 * \par Others
 *   None
 */
double KA_Ultrasonic::distanceInch(uint16_t MAXinch)
{
  long distance = measure(MAXinch * 145 + 200);
  return( (double)(distance / 148.0) );
}

/**
 * \par Function
 *   measure
 * \par Description
 *   To get the duration of the ultrasonic sensor
 * \param[in]
 *   timeout - This value is used to define the measurement range, The
 *   default value is 30000.
 * \par Output
 *   None
 * \return
 *   The duration value associated with distance
 * \par Others
 *   None
 */
long KA_Ultrasonic::measure(unsigned long timeout)
{
  long duration;
  if(millis() - _lastEnterTime > 23)
  {
    _measureFlag = true; 
  }

  if(_measureFlag == true)
  {
    _lastEnterTime = millis();
    _measureFlag = false;
    KA_Port::dWrite1(LOW);
    delayMicroseconds(2);
    KA_Port::dWrite1(HIGH);
    delayMicroseconds(10);
    KA_Port::dWrite1(LOW);
    pinMode(s2, INPUT);
    duration = pulseIn(s2, HIGH, timeout);
    _measureValue = duration;
  }
  else
  {
    duration = _measureValue;
  }
  return(duration);
}

