/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   KA_Buzzer
 * \brief   Driver for KA_ Buzzer module.
 * @file    KA_Buzzer.cpp
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2015/11/09
 * @brief   Driver for KA_ Buzzer module.
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
 * @example MbotBuzzerTest.ino
 * @example MbotBuzzerTest2.ino
 */
#include "KA_Buzzer.h"
#include <avr/wdt.h>

uint8_t buzzer_pin;

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * Buzzer pins are used and initialized here.
 * \param[in]
 *   None
 */
KA_Buzzer::KA_Buzzer()
{
#if defined(__AVR_ATmega32U4__) //MeBaseBoard use ATmega32U4 as MCU
	buzzer_pin = 12;
#else // else ATmega328
	buzzer_pin = 11;
#endif	
}

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 */
KA_Buzzer::KA_Buzzer(uint8_t port):KA_Port(port)
{
	buzzer_pin = s1;
}

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * you can set any slot for the buzzer device. 
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   slot - SLOT1 or SLOT2
 */
KA_Buzzer::KA_Buzzer(uint8_t port, uint8_t slot):KA_Port(port)
{
  buzzer_pin = s1;
  if(slot == SLOT2)
  {   
    buzzer_pin = s2;
  }
  else
  {
    buzzer_pin = s1;
  }
}

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * \param[in]
 *   switchPin - arduino port for buzzer detect pin.
 */
KA_Buzzer::KA_Buzzer(int pin)
{
  buzzer_pin = pin;
}

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
void KA_Buzzer::setpin(int pin)
{
  buzzer_pin = pin;
}

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
void KA_Buzzer::tone(int pin, uint16_t frequency, uint32_t duration)
{
  buzzer_pin = pin;
  int period = 1000000L / frequency;
  int pulse = period / 2;
  pinMode(buzzer_pin, OUTPUT);
  for (uint32_t i = 0; i < duration * 1000L; i += period) 
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(pulse);
//    wdt_reset();
  }
}

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
void KA_Buzzer::tone(uint16_t frequency, uint32_t duration)
{
  int period = 1000000L / frequency;
  int pulse = period / 2;
  pinMode(buzzer_pin, OUTPUT);
  for (uint32_t i = 0; i < duration * 1000L; i += period) 
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(pulse);
//    wdt_reset();
  }
}

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
void KA_Buzzer::noTone(int pin)
{
  buzzer_pin = pin;
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW);
}

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
void KA_Buzzer::noTone()
{
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(buzzer_pin, LOW);
}