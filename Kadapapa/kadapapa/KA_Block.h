///@file Makeblock.h head file of Makeblock Library V2.1.0625
///Define the interface of Makeblock Library

//#include <inttypes.h>

#ifndef __KA_BLOCK_H
#define __KA_BLOCK_H

#include "KA_Port.h"
//#include "KA_7SegmentDisplay.h"
//#include "KA_Buzzer.h"
//#include "KA_DCMotor.h"
//#include "KA_Gyro.h"
//#include "KA_HumitureSensor.h"
//#include "KA_InfraredReceiver.h"
//#include "KA_Mpr121.h"
//#include "KA_OneWire.h"
//#include "KA_RGBLed.h"
//#include "KA_Serial.h"
//#include "KA_Servo.h"
//#include "KA_Temperature.h"
//#include "KA_Ultrasonic.h"
//#include "KA_Wire.h"
//#include "KA_IR.h"

//#include <Arduino.h>
//#include <Wire.h>
//#include <Servo.h>
//#include <SoftwareSerial.h>

//#include <avr/interrupt.h>
//#include <avr/io.h>
//#ifndef F_CPU
//#define  F_CPU 16000000UL
//#endif
//#include <util/delay.h>
//#include <stdint.h>
//#include <stdlib.h>

// Platform specific I/O definitions
// #define PIN_TO_BASEREG(pin)             (portInputRegister(digitalPinToPort(pin)))
// #define PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
// #define IO_REG_TYPE uint8_t
// #define IO_REG_ASM asm("r30")
// #define DIRECT_READ(base, mask)         (((*(base)) & (mask)) ? 1 : 0)
// #define DIRECT_MODE_INPUT(base, mask)   ((*((base)+1)) &= ~(mask))
// #define DIRECT_MODE_OUTPUT(base, mask)  ((*((base)+1)) |= (mask))
// #define DIRECT_WRITE_LOW(base, mask)    ((*((base)+2)) &= ~(mask))
// #define DIRECT_WRITE_HIGH(base, mask)   ((*((base)+2)) |= (mask))

//#define FALSE 0
//#define TRUE  1

//#define __ICBRICK_BOARD
//#include "KA_Port.h"
////@brief Class for KA_Board
//class KA_Board
//{
//public:
//    KA_Board(uint8_t boards);
//};

/*
	//The PWM frequency is 976 Hz
#if defined(__AVR_ATmega32U4__) //KA_BaseBoard use ATmega32U4 as MCU
  TCCR1A =  _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);

  TCCR3A = _BV(WGM30);
  TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32);

  TCCR4B = _BV(CS42) | _BV(CS41) | _BV(CS40);
  TCCR4D = 0;

#elif defined(__AVR_ATmega328__) // else ATmega328

  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);

  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);

#elif defined(__AVR_ATmega2560__) //else ATmega2560
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);

  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
#endif
*/
#endif
