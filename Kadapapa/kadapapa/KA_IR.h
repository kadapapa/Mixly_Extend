/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   KA_IR
 * \brief   Driver for KA_ IR module.
 * @file    KA_IR.h
 * @author  MakeBlock
 * @version V1.0.4
 * @date    2015/11/16
 * @brief   Header for KA_IR.cpp module
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
 * This file is a drive for KA_ IR device, The IR inherited the 
 * KA_Serial class from SoftwareSerial.
 *
 * \par KA_thod List:
 *
 *    1. ErrorStatus KA_IR::decode();
 *    2. void KA_IR::begin();
 *    3. void KA_IR::end();
 *    4. void KA_IR::loop();
 *    5. boolean KA_IR::keyPressed(unsigned char r);
 *    6. String KA_IR::getString();
 *    7. unsigned char KA_IR::getCode()
 *    8. void KA_IR::sendString(String s);
 *    9. void KA_IR::sendString(float v);
 *    10. void KA_IR::sendNEC(unsigned long data, int nbits);
 *    11. void KA_IR::sendRaw(unsigned int buf[], int len, uint8_t hz);
 *    12. void KA_IR::enableIROut(uint8_t khz);
 *    13. void KA_IR::enableIRIn();
 *    14. void KA_IR::mark(uint16_t us);
 *    15. void KA_IR::space(uint16_t us);
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan        2015/10/09     1.0.0            Bulid the new.
 * Mark Yan        2015/10/29     1.0.1            Fix minor errors on format.
 * Mark Yan        2015/11/02     1.0.2            Fix bug that IRsend and IRreceive can't work at the same time.
 * forfish         2015/11/09     1.0.3            Add description.
 * Mark Yan        2015/11/16     1.0.4            add data recovery when timeout.
 * </pre>
 *
 */
 
#ifndef __KA_IR_H
#define __KA_IR_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "KA_Port.h"

// The following are compile-time library options.
// If you change them, recompile the library.
// If DEBUG is defined, a lot of debugging output will be printed during decoding.
// TEST must be defined for the IRtest unittests to work.  It will make some
// methods virtual, which will be slightly slower, which is why it is optional.
// #define DEBUG
// #define TEST

// Values for decode_type
#define NEC 1
#define SONY 2
#define RC5 3
#define RC6 4
#define DISH 5
#define SHARP 6
#define PANASONIC 7
#define JVC 8
#define SANYO 9
#define MITSUBISHI 10
#define SAMSUNG 11
#define LG 12
#define UNKNOWN -1

#define TOPBIT 0x80000000

// Decoded value for NEC when a repeat code is received
#define REPEAT 0xffffffff

// Only used for testing; can remove virtual for shorter code
#ifdef TEST
#define VIRTUAL virtual
#else
#define VIRTUAL
#endif
// Some useful constants

#define USECPERTICK 50  // microseconds per clock interrupt tick
#define RAWBUF 100 // Length of raw duration buffer

// Marks tend to be 100us too long, and spaces 100us too short
// when received due to sensor lag.
#define MARK_EXCESS 100


#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// define which timer to use
//
// Uncomment the timer you wish to use on your board.  If you
// are using another library which uses timer2, you have options
// to switch IRremote to use a different timer.

// Arduino Mega
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  //#define IR_USE_TIMER1   // tx = pin 11
  #define IR_USE_TIMER2     // tx = pin 9
  //#define IR_USE_TIMER3   // tx = pin 5
  //#define IR_USE_TIMER4   // tx = pin 6
  //#define IR_USE_TIMER5   // tx = pin 46

// Teensy 1.0
#elif defined(__AVR_AT90USB162__)
  #define IR_USE_TIMER1     // tx = pin 17

// Teensy 2.0
#elif defined(__AVR_ATmega32U4__)
  //#define IR_USE_TIMER1   // tx = pin 14
  //#define IR_USE_TIMER3   // tx = pin 9
  #define IR_USE_TIMER4_HS  // tx = pin 10

// Teensy++ 1.0 & 2.0
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
  //#define IR_USE_TIMER1   // tx = pin 25
  #define IR_USE_TIMER2     // tx = pin 1
  //#define IR_USE_TIMER3   // tx = pin 16

// Sanguino
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__)
  //#define IR_USE_TIMER1   // tx = pin 13
  #define IR_USE_TIMER2     // tx = pin 14

// Atmega8
#elif defined(__AVR_ATmega8P__) || defined(__AVR_ATmega8__)
  #define IR_USE_TIMER1   // tx = pin 9

// Arduino Duemilanove, Diecimila, LilyPad, Mini, Fio, etc
#else
  //#define IR_USE_TIMER1   // tx = pin 9
  #define IR_USE_TIMER2     // tx = pin 3
#endif


#ifdef F_CPU
#define SYSCLOCK F_CPU     // main Arduino clock
#else
#define SYSCLOCK 16000000  // main Arduino clock
#endif

#define ERR 0
#define DECODED 1


// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// Pulse parms are *50-100 for the Mark and *50+100 for the space
// First MARK is the one after the long gap
// pulse parameters in usec
#define NEC_HDR_MARK	9000
#define NEC_HDR_SPACE	4500
#define NEC_BIT_MARK	560
#define NEC_ONE_SPACE	1600
#define NEC_ZERO_SPACE	560
#define NEC_RPT_SPACE	2250

#define SONY_HDR_MARK	2400
#define SONY_HDR_SPACE	600
#define SONY_ONE_MARK	1200
#define SONY_ZERO_MARK	600
#define SONY_RPT_LENGTH 45000
#define SONY_DOUBLE_SPACE_USECS  500  // usually ssee 713 - not using ticks as get number wrapround

// SA 8650B
#define SANYO_HDR_MARK	3500  // seen range 3500
#define SANYO_HDR_SPACE	950 //  seen 950
#define SANYO_ONE_MARK	2400 // seen 2400  
#define SANYO_ZERO_MARK 700 //  seen 700
#define SANYO_DOUBLE_SPACE_USECS  800  // usually ssee 713 - not using ticks as get number wrapround
#define SANYO_RPT_LENGTH 45000

// Mitsubishi RM 75501
// 14200 7 41 7 42 7 42 7 17 7 17 7 18 7 41 7 18 7 17 7 17 7 18 7 41 8 17 7 17 7 18 7 17 7 

// #define MITSUBISHI_HDR_MARK	250  // seen range 3500
#define MITSUBISHI_HDR_SPACE	350 //  7*50+100
#define MITSUBISHI_ONE_MARK	1950 // 41*50-100
#define MITSUBISHI_ZERO_MARK  750 // 17*50-100
// #define MITSUBISHI_DOUBLE_SPACE_USECS  800  // usually ssee 713 - not using ticks as get number wrapround
// #define MITSUBISHI_RPT_LENGTH 45000


#define RC5_T1		889
#define RC5_RPT_LENGTH	46000

#define RC6_HDR_MARK	2666
#define RC6_HDR_SPACE	889
#define RC6_T1		444
#define RC6_RPT_LENGTH	46000

#define SHARP_BIT_MARK 245
#define SHARP_ONE_SPACE 1805
#define SHARP_ZERO_SPACE 795
#define SHARP_GAP 600000
#define SHARP_TOGGLE_MASK 0x3FF
#define SHARP_RPT_SPACE 3000

#define DISH_HDR_MARK 400
#define DISH_HDR_SPACE 6100
#define DISH_BIT_MARK 400
#define DISH_ONE_SPACE 1700
#define DISH_ZERO_SPACE 2800
#define DISH_RPT_SPACE 6200
#define DISH_TOP_BIT 0x8000

#define PANASONIC_HDR_MARK 3502
#define PANASONIC_HDR_SPACE 1750
#define PANASONIC_BIT_MARK 502
#define PANASONIC_ONE_SPACE 1244
#define PANASONIC_ZERO_SPACE 400

#define JVC_HDR_MARK 8000
#define JVC_HDR_SPACE 4000
#define JVC_BIT_MARK 600
#define JVC_ONE_SPACE 1600
#define JVC_ZERO_SPACE 550
#define JVC_RPT_LENGTH 60000

#define SHARP_BITS 15
#define DISH_BITS 16

#define TOLERANCE 25  // percent tolerance in measurements
#define LTOL (1.0 - TOLERANCE/100.) 
#define UTOL (1.0 + TOLERANCE/100.) 

#define _GAP 5000 // Minimum map between transmissions
#define GAP_TICKS (_GAP/USECPERTICK)

#define TICKS_LOW(us) (int) (((us)*LTOL/USECPERTICK))
#define TICKS_HIGH(us) (int) (((us)*UTOL/USECPERTICK + 1))

// receiver states
#define STATE_IDLE     2
#define STATE_MARK     3
#define STATE_SPACE    4
#define STATE_STOP     5

// IR detector output is active low
#define MARK  0
#define SPACE 1

#define TOPBIT 0x80000000

#define NEC_BITS 32
#define SONY_BITS 12
#define SANYO_BITS 12
#define MITSUBISHI_BITS 16
#define MIN_RC5_SAMPLES 11
#define MIN_RC6_SAMPLES 1
#define PANASONIC_BITS 48
#define JVC_BITS 16


// defines for timer2 (8 bits)
#if defined(IR_USE_TIMER2)
#define TIMER_RESET
#define TIMER_ENABLE_PWM     (TCCR2A |= _BV(COM2B1))
#define TIMER_DISABLE_PWM    (TCCR2A &= ~(_BV(COM2B1)))
#define TIMER_ENABLE_INTR    (TIMSK2 = _BV(OCIE2A))
#define TIMER_DISABLE_INTR   (TIMSK2 = 0)
#define TIMER_INTR_NAME      TIMER2_COMPA_vect
#define TIMER_CONFIG_KHZ(val) ({ \
  const uint8_t pwmval = SYSCLOCK / 2000 / (val); \
  TCCR2A = _BV(WGM20); \
  TCCR2B = _BV(WGM22) | _BV(CS20); \
  OCR2A = pwmval; \
  OCR2B = pwmval / 3; \
})
#define TIMER_COUNT_TOP      (SYSCLOCK * USECPERTICK / 1000000)
#if (TIMER_COUNT_TOP < 256)
#define TIMER_CONFIG_NORMAL() ({ \
  TCCR2A = _BV(WGM21); \
  TCCR2B = _BV(CS20); \
  OCR2A = TIMER_COUNT_TOP; \
  TCNT2 = 0; \
})
#else
#define TIMER_CONFIG_NORMAL() ({ \
  TCCR2A = _BV(WGM21); \
  TCCR2B = _BV(CS21); \
  OCR2A = TIMER_COUNT_TOP / 8; \
  TCNT2 = 0; \
})
#endif
#if defined(CORE_OC2B_PIN)
#define TIMER_PWM_PIN        CORE_OC2B_PIN  /* Teensy */
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define TIMER_PWM_PIN        9  /* Arduino Mega */
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__)
#define TIMER_PWM_PIN        14 /* Sanguino */
#else
#define TIMER_PWM_PIN        3  /* Arduino Duemilanove, Diecimila, LilyPad, etc */
#endif


// defines for timer1 (16 bits)
#elif defined(IR_USE_TIMER1)
#define TIMER_RESET
#define TIMER_ENABLE_PWM     (TCCR1A |= _BV(COM1A1))
#define TIMER_DISABLE_PWM    (TCCR1A &= ~(_BV(COM1A1)))
#if defined(__AVR_ATmega8P__) || defined(__AVR_ATmega8__)
  #define TIMER_ENABLE_INTR    (TIMSK = _BV(OCIE1A))
  #define TIMER_DISABLE_INTR   (TIMSK = 0)
#else
  #define TIMER_ENABLE_INTR    (TIMSK1 = _BV(OCIE1A))
  #define TIMER_DISABLE_INTR   (TIMSK1 = 0)
#endif
#define TIMER_INTR_NAME      TIMER1_COMPA_vect
#define TIMER_CONFIG_KHZ(val) ({ \
  const uint16_t pwmval = SYSCLOCK / 2000 / (val); \
  TCCR1A = _BV(WGM11); \
  TCCR1B = _BV(WGM13) | _BV(CS10); \
  ICR1 = pwmval; \
  OCR1A = pwmval / 3; \
})
#define TIMER_CONFIG_NORMAL() ({ \
  TCCR1A = 0; \
  TCCR1B = _BV(WGM12) | _BV(CS10); \
  OCR1A = SYSCLOCK * USECPERTICK / 1000000; \
  TCNT1 = 0; \
})
#if defined(CORE_OC1A_PIN)
#define TIMER_PWM_PIN        CORE_OC1A_PIN  /* Teensy */
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define TIMER_PWM_PIN        11  /* Arduino Mega */
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__)
#define TIMER_PWM_PIN        13 /* Sanguino */
#else
#define TIMER_PWM_PIN        9  /* Arduino Duemilanove, Diecimila, LilyPad, etc */
#endif


// defines for timer3 (16 bits)
#elif defined(IR_USE_TIMER3)
#define TIMER_RESET
#define TIMER_ENABLE_PWM     (TCCR3A |= _BV(COM3A1))
#define TIMER_DISABLE_PWM    (TCCR3A &= ~(_BV(COM3A1)))
#define TIMER_ENABLE_INTR    (TIMSK3 = _BV(OCIE3A))
#define TIMER_DISABLE_INTR   (TIMSK3 = 0)
#define TIMER_INTR_NAME      TIMER3_COMPA_vect
#define TIMER_CONFIG_KHZ(val) ({ \
  const uint16_t pwmval = SYSCLOCK / 2000 / (val); \
  TCCR3A = _BV(WGM31); \
  TCCR3B = _BV(WGM33) | _BV(CS30); \
  ICR3 = pwmval; \
  OCR3A = pwmval / 3; \
})
#define TIMER_CONFIG_NORMAL() ({ \
  TCCR3A = 0; \
  TCCR3B = _BV(WGM32) | _BV(CS30); \
  OCR3A = SYSCLOCK * USECPERTICK / 1000000; \
  TCNT3 = 0; \
})
#if defined(CORE_OC3A_PIN)
#define TIMER_PWM_PIN        CORE_OC3A_PIN  /* Teensy */
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define TIMER_PWM_PIN        5  /* Arduino Mega */
#else
#error "Please add OC3A pin number here\n"
#endif


// defines for timer4 (10 bits, high speed option)
#elif defined(IR_USE_TIMER4_HS)
#define TIMER_RESET
#define TIMER_ENABLE_PWM     (TCCR4A |= _BV(COM4A1))
#define TIMER_DISABLE_PWM    (TCCR4A &= ~(_BV(COM4A1)))
#define TIMER_ENABLE_INTR    (TIMSK4 = _BV(TOIE4))
#define TIMER_DISABLE_INTR   (TIMSK4 = 0)
#define TIMER_INTR_NAME      TIMER4_OVF_vect
#define TIMER_CONFIG_KHZ(val) ({ \
  const uint16_t pwmval = SYSCLOCK / 2000 / (val); \
  TCCR4A = (1<<PWM4A); \
  TCCR4B = _BV(CS40); \
  TCCR4C = 0; \
  TCCR4D = (1<<WGM40); \
  TCCR4E = 0; \
  TC4H = pwmval >> 8; \
  OCR4C = pwmval; \
  TC4H = (pwmval / 3) >> 8; \
  OCR4A = (pwmval / 3) & 255; \
})
#define TIMER_CONFIG_NORMAL() ({ \
  TCCR4A = 0; \
  TCCR4B = _BV(CS40); \
  TCCR4C = 0; \
  TCCR4D = 0; \
  TCCR4E = 0; \
  TC4H = (SYSCLOCK * USECPERTICK / 1000000) >> 8; \
  OCR4C = (SYSCLOCK * USECPERTICK / 1000000) & 255; \
  TC4H = 0; \
  TCNT4 = 0; \
})
#if defined(CORE_OC4A_PIN)
#define TIMER_PWM_PIN        CORE_OC4A_PIN  /* Teensy */
#elif defined(__AVR_ATmega32U4__)
#define TIMER_PWM_PIN        13  /* Leonardo */
#else
#error "Please add OC4A pin number here\n"
#endif


// defines for timer4 (16 bits)
#elif defined(IR_USE_TIMER4)
#define TIMER_RESET
#define TIMER_ENABLE_PWM     (TCCR4A |= _BV(COM4A1))
#define TIMER_DISABLE_PWM    (TCCR4A &= ~(_BV(COM4A1)))
#define TIMER_ENABLE_INTR    (TIMSK4 = _BV(OCIE4A))
#define TIMER_DISABLE_INTR   (TIMSK4 = 0)
#define TIMER_INTR_NAME      TIMER4_COMPA_vect
#define TIMER_CONFIG_KHZ(val) ({ \
  const uint16_t pwmval = SYSCLOCK / 2000 / (val); \
  TCCR4A = _BV(WGM41); \
  TCCR4B = _BV(WGM43) | _BV(CS40); \
  ICR4 = pwmval; \
  OCR4A = pwmval / 3; \
})
#define TIMER_CONFIG_NORMAL() ({ \
  TCCR4A = 0; \
  TCCR4B = _BV(WGM42) | _BV(CS40); \
  OCR4A = SYSCLOCK * USECPERTICK / 1000000; \
  TCNT4 = 0; \
})
#if defined(CORE_OC4A_PIN)
#define TIMER_PWM_PIN        CORE_OC4A_PIN
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define TIMER_PWM_PIN        6  /* Arduino Mega */
#else
#error "Please add OC4A pin number here\n"
#endif


// defines for timer5 (16 bits)
#elif defined(IR_USE_TIMER5)
#define TIMER_RESET
#define TIMER_ENABLE_PWM     (TCCR5A |= _BV(COM5A1))
#define TIMER_DISABLE_PWM    (TCCR5A &= ~(_BV(COM5A1)))
#define TIMER_ENABLE_INTR    (TIMSK5 = _BV(OCIE5A))
#define TIMER_DISABLE_INTR   (TIMSK5 = 0)
#define TIMER_INTR_NAME      TIMER5_COMPA_vect
#define TIMER_CONFIG_KHZ(val) ({ \
  const uint16_t pwmval = SYSCLOCK / 2000 / (val); \
  TCCR5A = _BV(WGM51); \
  TCCR5B = _BV(WGM53) | _BV(CS50); \
  ICR5 = pwmval; \
  OCR5A = pwmval / 3; \
})
#define TIMER_CONFIG_NORMAL() ({ \
  TCCR5A = 0; \
  TCCR5B = _BV(WGM52) | _BV(CS50); \
  OCR5A = SYSCLOCK * USECPERTICK / 1000000; \
  TCNT5 = 0; \
})
#if defined(CORE_OC5A_PIN)
#define TIMER_PWM_PIN        CORE_OC5A_PIN
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define TIMER_PWM_PIN        46  /* Arduino Mega */
#else
#error "Please add OC5A pin number here\n"
#endif


#else // unknown timer
#error "Internal code configuration error, no known IR_USE_TIMER# defined\n"
#endif

/*
// defines for blinking the LED
#if defined(CORE_LED0_PIN)
#define BLINKLED       CORE_LED0_PIN
#define BLINKLED_ON()  (digitalWrite(CORE_LED0_PIN, HIGH))
#define BLINKLED_OFF() (digitalWrite(CORE_LED0_PIN, LOW))
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define BLINKLED       13
#define BLINKLED_ON()  (PORTB |= B10000000)
#define BLINKLED_OFF() (PORTB &= B01111111)
#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644__)
#define BLINKLED       0
#define BLINKLED_ON()  (PORTD |= B00000001)
#define BLINKLED_OFF() (PORTD &= B11111110)
#else
#define BLINKLED       13
#define BLINKLED_ON()  (PORTB |= B00100000)
#define BLINKLED_OFF() (PORTB &= B11011111)
#endif
*/

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

// information for the interrupt handler
typedef struct {
  uint8_t recvpin;           // pin for IR data from detector
  uint8_t rcvstate;          // state machine
  uint8_t blinkflag;         // TRUE to enable blinking of pin 13 on IR processing
  unsigned int timer;     // state timer, counts 50uS ticks.
  unsigned int rawbuf[RAWBUF]; // raw data
  uint8_t rawlen;         // counter of entries in rawbuf
} 
irparams_t;

// Results returned from the decoder
class decode_results {
public:
  int decode_type; // NEC, SONY, RC5, UNKNOWN
  unsigned int panasonicAddress; // This is only used for decoding Panasonic data
  unsigned long value; // Decoded value
  int bits; // Number of bits in decoded value
  volatile unsigned int *rawbuf; // Raw intervals in .5 us ticks
  int rawlen; // Number of records in rawbuf.
};

// main class for receiving IR
class KA_IR : public KA_Port
{
public:

/**
 * Alternate Constructor which can call your own function to map the IR to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
*/
  KA_IR(void);

/**
 * Alternate Constructor which can call your own function to map the IR to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
*/
  KA_IR(uint8_t port);   

/**
 * \par Function
 *    decode
 * \par Description
 *    Decodes the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns 0 if no data ready, 1 if data ready.
 * \par Others
 *    Results of decoding are stored in results.
 */
  int decode(decode_results *results);
  
/**
 * \par Function
 *    decode
 * \par Description
 *    Decodes the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns 0 if no data ready, 1 if data ready.
 * \par Others
 *    Results of decoding are stored in results.
 */
  ErrorStatus decode(void);

/**
 * \par Function
 *    begin
 * \par Description
 *    Initialize interrupt.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void begin();

/**
 * \par Function
 *    end
 * \par Description
 *    Close the interrupt.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void begin(int pin);  
  
/**
 * \par Function
 *    end
 * \par Description
 *    Close the interrupt.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void end();

/**
 * \par Function
 *    sendString
 * \par Description
 *    Send data.
 * \param[in]
 *    s - The string you want to send.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void sendString(String s);
  
/**
 * \par Function
 *    sendString
 * \par Description
 *    Send data.
 * \param[in]
 *    v - The string you want to send.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void sendString(float v);
  
/**
 * \par Function
 *    sendNEC
 * \par Description
 *    Send NEC.
 * \param[in]
 *    data - The data you want to send.
  * \param[in]
 *    nbits - The data bit you want to send.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void sendNEC(unsigned long data, int nbits);
  
/**
 * \par Function
 *    sendRaw
 * \par Description
 *    Send the length of data with hz.
 * \param[in]
 *    buf[] - The data's buffer.
  * \param[in]
 *    len - The data's length.
  * \param[in]
 *    hz - The hz for sending data.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void sendRaw(unsigned int buf[], int len, uint8_t hz);
  
/**
 * \par Function
 *    enableIROut
 * \par Description
 *    Enable an IR for the specified number of khz.
 * \param[in]
 *    us - THe time of a INTR.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void enableIROut(uint8_t khz);
  
/**
 * \par Function
 *    enableIRIn
 * \par Description
 *    Enable an IR to write in.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void enableIRIn();

/**
 * \par Function
 *    enableIRIn
 * \par Description
 *    Enable an IR to write in.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */  
  void resume();
 
/**
 * \par Function
 *    mark
 * \par Description
 *    Sends an IR mark for the specified number of microseconds.
 * \param[in]
 *    us - THe time of a PWM.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void mark(uint16_t us);
  
/**
 * \par Function
 *    space
 * \par Description
 *    Sends an IR mark for the specified number of microseconds.
 * \param[in]
 *    us - THe time of a PWM.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void space(uint16_t us);
   
/**
 * \par Function
 *    getCode
 * \par Description
 *    Get the reading code.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return the result of reading.
 * \par Others
 *    None
 */
  unsigned char getCode();  
  
/**
 * \par Function
 *    getString
 * \par Description
 *    Get string in a INTR.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return the result in a IRQ.
 * \par Others
 *    None
 */
  String getString();  
  
/**
 * \par Function
 *    keyPressed
 * \par Description
 *    Press key.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return you the pressed key or not.
 * \par Others
 *    None
 */
  boolean keyPressed(unsigned char r);  
  
/**
 * \par Function
 *    loop
 * \par Description
 *    A circle of operation.
 * \param[in]
 *    None
 * \par Output0
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
  void loop();
  
 
  int decode_type; // NEC, SONY, RC5, UNKNOWN
  unsigned int panasonicAddress; // This is only used for decoding Panasonic data
  unsigned long value; // Decoded value
  int bits; // Number of bits in decoded value
  volatile unsigned int *rawbuf; // Raw intervals in .5 us ticks
  int rawlen; // Number of records in rawbuf.
  
private:
  // These are called by decode
  int getRClevel(decode_results *results, int *offset, int *used, int t1);
  
/**
 * \par Function
 *    decodeNEC
 * \par Description
 *    Decodes NEC the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns ERROR if decode NEC no done, SUCCESS if decode NEC done.
 * \par Others
 *    Results of decode NEC.
 */
  ErrorStatus decodeNEC(void);  

/**
 * \par Function
 *    decodeNEC
 * \par Description
 *    Decodes NEC the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns ERROR if decode NEC no done, SUCCESS if decode NEC done.
 * \par Others
 *    Results of decode NEC.
 */  
  long decodeNEC(decode_results *results);
  
/**
 * \par Function
 *    decodeNEC
 * \par Description
 *    Decodes NEC the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns ERROR if decode NEC no done, SUCCESS if decode NEC done.
 * \par Others
 *    Results of decode NEC.
 */  
  //long decodeSony(decode_results *results);
  
/**
 * \par Function
 *    decodeNEC
 * \par Description
 *    Decodes NEC the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns ERROR if decode NEC no done, SUCCESS if decode NEC done.
 * \par Others
 *    Results of decode NEC.
 */  
  //long decodeSanyo(decode_results *results);

/**
 * \par Function
 *    decodeNEC
 * \par Description
 *    Decodes NEC the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns ERROR if decode NEC no done, SUCCESS if decode NEC done.
 * \par Others
 *    Results of decode NEC.
 */  
  //long decodeMitsubishi(decode_results *results);
  
 /**
 * \par Function
 *    decodeNEC
 * \par Description
 *    Decodes NEC the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns ERROR if decode NEC no done, SUCCESS if decode NEC done.
 * \par Others
 *    Results of decode NEC.
 */ 
  //long decodeRC5(decode_results *results);
  
/**
 * \par Function
 *    decodeNEC
 * \par Description
 *    Decodes NEC the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns ERROR if decode NEC no done, SUCCESS if decode NEC done.
 * \par Others
 *    Results of decode NEC.
 */  
  //long decodeRC6(decode_results *results);
  
/**
 * \par Function
 *    decodeNEC
 * \par Description
 *    Decodes NEC the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns ERROR if decode NEC no done, SUCCESS if decode NEC done.
 * \par Others
 *    Results of decode NEC.
 */  
  //long decodePanasonic(decode_results *results);
  
/**
 * \par Function
 *    decodeNEC
 * \par Description
 *    Decodes NEC the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns ERROR if decode NEC no done, SUCCESS if decode NEC done.
 * \par Others
 *    Results of decode NEC.
 */  
  //long decodeJVC(decode_results *results);
  
/**
 * \par Function
 *    decodeNEC
 * \par Description
 *    Decodes NEC the received IR message.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Returns ERROR if decode NEC no done, SUCCESS if decode NEC done.
 * \par Others
 *    Results of decode NEC.
 */  
  long decodeHash(decode_results *results);

/** Converts the raw code values into a 32-bit hash code.
 * Hopefully this code is unique for each button.
 * This isn't a "real" decoding, just an arbitrary value.
 */
	ErrorStatus decodeHash(void);   
  
  int compare(unsigned int oldval, unsigned int newval);
  
  int16_t irIndex;	
  char irRead;
  char floatString[5];
  boolean irReady;
  boolean irPressed;
  String irBuffer;
  String Pre_Str;
  double irDelayTime;  

};


#endif
