/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class KA_Humiture
 * \brief   Driver for humiture sensor device.
 * @file    MeHumitureSensor.h
 * @author  MakeBlock
 * @version V1.0.1
 * @date    2015/11/18
 * @brief   Header for for KA_Humiture.cpp module
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
 * This file is a drive for humiture sensor device, It supports humiture sensor
 * provided by the MakeBlock.
 *
 * \par Method List:
 *
 *    1. void KA_Humiture::setpin(uint8_t port)
 *    2. void KA_Humiture::update(void)
 *    3. uint8_t KA_Humiture::getHumidity(void)
 *    4. uint8_t KA_Humiture::getTemperature(void)
 *    5. uint8_t KA_Humiture::getValue(uint8_t index)
 *    6. double KA_Humiture::getFahrenheit(void)
 *    7. double KA_Humiture::getKelvin(void)
 *    8. double KA_Humiture::getdewPoint(void)
 *    9. double KA_Humiture::getPointFast()
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan         2015/09/08     1.0.0            Rebuild the old lib.
 * forfish          2015/11/18     1.0.1            Add some functions.
 * </pre>
 */
#ifndef __KA_Humiture_H_
#define __KA_Humiture_H_

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>

#include "KA_Port.h"


/**
 * Class: KA_Humiture
 * \par Description
 * Declaration of Class KA_Humiture.
 */

class KA_Humiture : public KA_Port
{
public:

/**
 * Alternate Constructor which can call your own function to map the humiture sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
  KA_Humiture(void);
 
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * the slot2 pin will be used here since specify slot is not be set.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  KA_Humiture(uint8_t port);
  
/**
 * \par Function
 *   setpin
 * \par Description
 *   Reset available PIN for temperature sensor by its arduino port.
 * \param[in]
 *   port - arduino port(should digital pin)
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void setpin(uint8_t port);

/**
 * \par Function
 *   reset
 * \par Description
 *   Reset the available PIN for temperature sensor by its RJ25 port,
 *   the slot2 pin will be used here since specify slot is not be set
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void reset(uint8_t port);

/**
 * \par Function
 *   getPort
 * \par Description
 *   Get current valid port of current RJ25 object
 * \par Output
 *   None
 * \return
 *   Port bumber from PORT_1 to M2
 * \par Others
 *   None
 */
uint8_t getPort(void);
  
/**
 * \par Function
 *   update
 * \par Description
 *   Use this function to update the sensor data
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
  void update(void);

/**
 * \par Function
 *   getHumidity
 * \par Description
 *   Use this function to Get the Humidity data
 * \par Output
 *   None
 * \return
 *   The value of Humidity
 * \par Others
 *   None
 */
  uint8_t getHumidity(void);

/**
 * \par Function
 *   getTemperature
 * \par Description
 *   Use this function to Get the Temperature data
 * \par Output
 *   None
 * \return
 *   The value of Temperature
 * \par Others
 *   None
 */
  uint8_t getTemperature(void);

/**
 * \par Function
 *   getValue
 * \par Description
 *   Use this function to Get the Temperature data or Humidity data
 * \param[in]
 *   index - The value '0' means get the value of Humidity data and '1' used to get the
 *   Temperature data.
 * \par Output
 *   None
 * \return
 *   The value of Temperature
 * \par Others
 *   None
 */
  uint8_t getValue(uint8_t index);

/**
 * \par Function
 *    Fahrenheit
 * \par Description
 *    Change celsius degrees into Fahrenheit.
 * \param[in]
 *    celsius - The number of celsius degrees.
 * \par Output
 *    None
 * \par Return
 *    Return the number of Fahrenheit
 * \par Others
 *    None
 */
  double getFahrenheit(void);//Celsius degrees to Fahrenheit

/**
 * \par Function
 *    Kelvin
 * \par Description
 *    Change celsius degrees into Kelvin.
 * \param[in]
 *    celsius - The number of celsius degrees.
 * \par Output
 *    None
 * \par Return
 *    Return the number of Kelvin temperature.
 * \par Others
 *    None
 */
  double getKelvin(void);

/**
 * \par Function
 *    dewPoint
 * \par Description
 *    The dew-point temperature (Point at this temperature, the air is saturated and produce dew).
 * \param[in]
 *    celsius - The celsius degrees of air.
  * \param[in]
 *    humidity - The humidity of air.
 * \par Output
 *    None
 * \par Return
 *    Return the dew-point of air.
 * \par Others
 *    None
 */
  double getdewPoint(void);

/**
 * \par Function
 *    dewPointFast
 * \par Description
 *    Fast calculating dew point, Speed is 5 times to dewPoint().
 * \param[in]
 *    celsius - The celsius degrees of air.
  * \param[in]
 *    humidity - The humidity of air.
 * \par Output
 *    None
 * \par Return
 *    Return the Fast calculating dew point of air.
 * \par Others
 *    None
 */
  double getPointFast(void);

  

private:

	uint8_t Humidity;
	uint8_t Temperature;
	uint8_t _DataPin;
	uint8_t _port;
	unsigned long Time1;
};

#endif

