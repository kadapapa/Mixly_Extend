/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   KA_Gyro
 * \brief   Driver for KA_Gyro module.
 * @file    KA_Gyro.h
 * @author  MakeBlock
 * @version V1.0.3
 * @date    2016/03/09
 * @brief   Header for KA_Gyro.cpp module.
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
 * This file is a drive for KA_Gyro module, It supports KA_Gyro V1.0 device provided
 * by MakeBlock.
 *
 * \par KA_thod List:
 *
 *    1. void KA_Gyro::setpin(uint8_t AD0, uint8_t INT)
 *    2. void KA_Gyro::begin(void)
 *    3. void KA_Gyro::update(void)
 *    4. void KA_Gyro::fast_update(void)
 *    5. uint8_t KA_Gyro::getDevAddr(void)
 *    6. double KA_Gyro::getAngleX(void)
 *    7. double KA_Gyro::getAngleY(void)
 *    8. double KA_Gyro::getAngleZ(void)
 *    9. double KA_Gyro::getGyroX(void)
 *    10. double KA_Gyro::getGyroY(void)
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 *  Lawrence         2015/09/02          1.0.0         rebuild the old lib.
 *  Lawrence         2015/09/10          1.0.1         Added some comments and macros.
 *  Mark Yan         2016/03/09          1.0.2         Add function fast_update.
 *  Mark Yan         2016/03/09          1.0.3         Add function getGyroX and getGyroY.
 * </pre>
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KA_GYRO_H
#define __KA_GYRO_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <Wire.h>
#include "KA_Port.h"
//#include "KA_Wire.h"

/* Exported macro ------------------------------------------------------------*/
#define I2C_ERROR                  (-1)
#define GYRO_DEFAULT_ADDRESS       (0x68)

/**
 * Class: KA_Gyro
 * \par Description
 * Declaration of Class KA_Gyro
 */
class KA_Gyro : public KA_Port
{
public:

/**
 * Alternate Constructor which can call your own function to map the KA_Compass to arduino port,
 * no pins are used or initialized here
 */
  KA_Gyro(void);

/**
 * Alternate Constructor which can call your own function to map the KA_Compass to arduino port,
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
  KA_Gyro(uint8_t port);

/**
 * Alternate Constructor which can call your own function to map the KA_Compass to arduino port
 * and change the i2c device address
 * no pins are used or initialized here, but PWM frequency set to 976 Hz
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   address - the i2c address you want to set
 */
  KA_Gyro(uint8_t port, uint8_t address);

/**
 * \par Function
 *   setpin
 * \par Description
 *   Set the PIN of the button module.
 * \param[in]
 *   AD0 - pin mapping for arduino
 * \param[in]
 *   INT - pin mapping for arduino
 * \par Output
 *   None
 * \return
 *   None.
 * \par Others
 *   Set global variable _AD0, _INT, s1 and s2
 */
  void setpin(uint8_t AD0, uint8_t INT);

/**
 * \par Function
 *   begin
 * \par Description
 *   Initialize the KA_Gyro.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   You can check the MPU6050 datasheet for the registor address.
 */
  void begin();

/**
 * \par Function
 *   update
 * \par Description
 *   Update some calculated angle values to the variable.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   The angle values are calculated by complementary filter.
 *   The time constant of filter is set to 0.5 second, but period dt is not a constant, 
 *   so the filter coefficient will be calculated dynamically.
 */
  void update(void);

/**
 * \par Function
 *   fast_update
 * \par Description
 *   Fast update some calculated angle values to the variable.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None
 * \par Others
 *   The angle values are calculated by complementary filter.
 *   The time constant of filter is set to 0.5 second, but period dt is not a constant, 
 *   so the filter coefficient will be calculated dynamically.
 */
  void fast_update(void);

/**
 * \par Function
 *   getDevAddr
 * \par Description
 *   Get the device address of Gyro.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   The device address of Gyro
 * \par Others
 *   None
 */
  uint8_t getDevAddr(void);

/**
 * \par Function
 *   getAngleX
 * \par Description
 *   Get the angle value of X-axis.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   The angle value of X-axis
 * \par Others
 *   X-axis angle value is calculated by complementary filter.
 */
  double getAngleX(void);

/**
 * \par Function
 *   getAngleY
 * \par Description
 *   Get the angle value of Y-axis.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   The angle value of Y-axis
 * \par Others
 *   Y-axis angle value is calculated by complementary filter.
 */
  double getAngleY(void);

/**
 * \par Function
 *   getAngleZ
 * \par Description
 *   Get the angle value of Z-axis.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   The angle value of Z-axis
 * \par Others
 *   Z-axis angle value is integral of Z-axis angular velocity.
 */
  double getAngleZ(void);

/**
 * \par Function
 *   getGyroX
 * \par Description
 *   Get the data of gyroXrate.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   The data of gyroXrate
 * \par Others
 *   None
 */
  double getGyroX(void);

/**
 * \par Function
 *   getGyroY
 * \par Description
 *   Get the data of gyroYrate.
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   The data of gyroYrate
 * \par Others
 *   None
 */
  double getGyroY(void);

/**
 * \par Function
 *   getAngle
 * \par Description
 *   Get the angle value of setting axis.
 * \param[in]
 *   index - Axis settings(1:X-axis, 2:Y-axis, 3:Z-axis)
 * \par Output
 *   None
 * \return
 *   The angle value of setting axis
 * \par Others
 *   Z-axis angle value is integral of Z-axis angular velocity.
 */
  double getAngle(uint8_t index);

private:
  volatile uint8_t  _AD0;
  volatile uint8_t  _INT;
  double  gSensitivity; /* for 500 deg/s, check data sheet */
  double  gx, gy, gz;
  double  gyrX, gyrY, gyrZ;
  int16_t accX, accY, accZ;
  double  gyrXoffs, gyrYoffs, gyrZoffs;
  uint8_t i2cData[14];
  uint8_t Device_Address;
  
/**
 * \par Function
 *   deviceCalibration
 * \par Description
 *   Calibration function for the KA_Gyro. 
 * \param[in]
 *   None
 * \par Output
 *   None
 * \return
 *   None.
 * \par Others
 *   The calibration function will be called in initial process, please keep the 
 *   device in a rest status at that time.
 */
  void deviceCalibration(void);

/**
 * \par Function
 *   writeReg
 * \par Description
 *   Write the registor of i2c device.
 * \param[in]
 *   reg - the address of registor.
 * \param[in]
 *   data - the data that will be written to the registor.
 * \par Output
 *   None
 * \return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * \par Others
 *   To set the registor for initializing.
 */
  int8_t writeReg(int16_t reg, uint8_t data);

/**
 * \par Function
 *   readData
 * \par Description
 *   Write the data to i2c device.
 * \param[in]
 *   start - the address which will write the data to.
 * \param[in]
 *   pData - the head address of data array.
 * \param[in]
 *   size - set the number of data will be written to the devide.
 * \par Output
 *   None
 * \return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * \par Others
 *   Calling the official i2c library to read data.
 */
  int8_t readData(uint8_t start, uint8_t *buffer, uint8_t size);

/**
 * \par Function
 *   writeData
 * \par Description
 *   Write the data to i2c device.
 * \param[in]
 *   start - the address which will write the data to.
 * \param[in]
 *   pData - the head address of data array.
 * \param[in]
 *   size - set the number of data will be written to the devide.
 * \par Output
 *   None
 * \return
 *   Return the error code.
 *   the definition of the value of variable return_value:
 *   0:success
 *   1:BUFFER_LENGTH is shorter than size
 *   2:address send, nack received
 *   3:data send, nack received
 *   4:other twi error
 *   refer to the arduino official library twi.c
 * \par Others
 *   Calling the official i2c library to write data.
 */
  int8_t writeData(uint8_t start, const uint8_t *pData, uint8_t size);
};
#endif //  KA_Gyro_H
