/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   KA_Buzzer
 * \brief   Driver for KA_ Buzzer module.
 * @file    KA_Buzzer.h
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2015/11/09
 * @brief   Header for KA_Buzzer.cpp module
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
 * This file is a drive for KA_ Buzzer device, The KA_ Buzzer inherited the 
 * KA_Serial class from SoftwareSerial.
 *
 * \par KA_thod List:
 *
 *    1. void KA_Buzzer::setpin(int pin);
 *	  2. void KA_Buzzer::tone(int pin, uint16_t frequency, uint32_t duration);
 *	  3. void KA_Buzzer::tone(uint16_t frequency, uint32_t duration)
 *	  4. void KA_Buzzer::noTone(int pin);
 *	  5. void KA_Buzzer::noTone();
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * forfish         2015/11/09     1.0.0            Add description
 * </pre>
 *
 * @example BuzzerTest.ino
 */
#ifndef __KA_BUZZER_H
#define __KA_BUZZER_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "KA_Port.h"


/**
 * Class: KA_Buzzer
 * \par Description
 * Declaration of Class KA_Buzzer.
 */
class KA_Buzzer : public KA_Port
{
public:
/**
 * Alternate Constructor which can call your own function to map the buzzer to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
*/
  KA_Buzzer();

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
*/
  KA_Buzzer(uint8_t port);

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * you can set any slot for the buzzer device. 
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   slot - SLOT1 or SLOT2
 */
  KA_Buzzer(uint8_t port, uint8_t slot);

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * \param[in]
 *   switchPin - arduino port for buzzer detect pin.
*/
  KA_Buzzer(int pin);

/**
 * \par Function
 *    setpin
 * \par Description
 *    Reset the buzzer available pin by its arduino port.
 * \param[in]
 *    pin - arduino port for buzzer detect pin.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void setpin(int pin);

/**
 * \par Function
 *    tone
 * \par Description
 *    Playing the tones.
 * \param[in]
 *    pin - Which pin on board that buzzer is connecting to.
 * \param[in]
 *    frequency - The speed of buzzer's tone play.
 * \param[in]
 *    duration - Time of a tone play.
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    Frequency (in hertz) and duration (in milliseconds).
 */
  void tone(int pin, uint16_t frequency, uint32_t duration);

/**
 * \par Function
 *    tone
 * \par Description
 *    Playing the tones.
 * \param[in]
 *    frequency - The speed of buzzer's tone play.
 * \param[in]
 *    duration - Time of a tone play.
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    Frequency (in hertz) and duration (in milliseconds).
 */
  void tone(uint16_t frequency, uint32_t duration = 0);

/**
 * \par Function
 *    noTone
 * \par Description
 *    Do not playing the tones.
 * \param[in]
 *    pin - Which pin on board that buzzer is connecting to.
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    None
 */
  void noTone(int pin);

/**
 * \par Function
 *    noTone
 * \par Description
 *    Do not playing the tones.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \Return
 *    None.
 * \par Others
 *    None
 */
  void noTone();
};

#endif
