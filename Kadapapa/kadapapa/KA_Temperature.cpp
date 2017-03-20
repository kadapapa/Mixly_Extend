/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class KA_Temperature
 * \brief   Driver for temperature sensor device.
 * @file    KA_Temperature.cpp
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2015/09/08
 * @brief   Driver for temperature sensor device.
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
 * This file is a drive for temperature sensor device, It supports temperature sensor
 * 18B20 provided by the MakeBlock.
 *
 * \par KA_thod List:
 *
 *    1. void KA_Temperature::reset(uint8_t port)
 *    2. void KA_Temperature::reset(uint8_t port, uint8_t slot)
 *    3. void KA_Temperature::setpin(uint8_t port)
 *    4. float KA_Temperature::temperature(void)
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan         2015/09/08     1.0.0            Rebuild the old lib.
 * </pre>
 *
 * @example TemperatureTest.ino
 */
#include "KA_Temperature.h"
/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
KA_Temperature::KA_Temperature(void) : KA_Port(0)
{
    Device_Address = TEMPERATURE_DEFAULT_ADDRESS;
}

/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port,
 * the slot2 pin will be used here since specify slot is not be set.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
KA_Temperature::KA_Temperature(uint8_t port) : KA_Port(port)
{
    Device_Address = TEMPERATURE_DEFAULT_ADDRESS;
}

/**
 * Alternate Constructor which can call your own function to map the temperature sensor to arduino port.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   slot - SLOT1 or SLOT2
 */
KA_Temperature::KA_Temperature(uint8_t port, uint8_t address) : KA_Port(port)
{
	Device_Address = address;
}

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
void KA_Temperature::reset(uint8_t port)
{
	KA_Port::reset(port);
}

/**
 * \par Function
 *   reset
 * \par Description
 *   Reset the available PIN for temperature sensor by its RJ25 port.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   slot - SLOT1 or SLOT2
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   None
 */
void KA_Temperature::reset(uint8_t port, uint8_t slot)
{
	KA_Port::reset(port, slot);
}

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
void KA_Temperature::setpin(void)
{
//  _AD0 = AD0;
//  _INT = INT;

//  s1 = AD0;
//  s2 = INT;

}

/**
 * \par Function
 *   temperature
 * \par Description
 *   Get the celsius of temperature
 * \par Output
 *   None
 * \return
 *   The temperature value get from the sensor.
 * \par Others
 *   None
 */
void KA_Temperature::begin(void)
{
	Wire.begin();
    Device_Address = TEMPERATURE_DEFAULT_ADDRESS;
}
 
/**
 * \par Function
 *   temperature
 * \par Description
 *   Get the celsius of temperature
 * \par Output
 *   None
 * \return
 *   The temperature value get from the sensor.
 * \par Others
 *   None
 */ 
int KA_Temperature::RegDataInteger(uint8_t reg)
{
	uint8_t quantity = 0x02;
	Wire.beginTransmission(Device_Address);
	Wire.write(reg);	
	Wire.endTransmission();

	Wire.requestFrom(Device_Address,quantity);
	int regdata = (Wire.read() << 8) | Wire.read();
	return regdata;
}

/**
 * \par Function
 *   temperature
 * \par Description
 *   Get the celsius of temperature
 * \par Output
 *   None
 * \return
 *   The temperature value get from the sensor.
 * \par Others
 *   None
 */ 
float KA_Temperature::RegDataFloat(int regdata)
{
//	return ((float)(int)regdata / 32) / 8;
	return ((float)(regdata >> 5)) * 0.125;
}

/**
 * \par Function
 *   temperature
 * \par Description
 *   Get the celsius of temperature
 * \par Output
 *   None
 * \return
 *   The temperature value get from the sensor.
 * \par Others
 *   None
 */ 
float KA_Temperature::get_temp(void) 
{
	return RegDataFloat(RegDataInteger(LM75_TEMP_REGISTER));
}
 

