/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   KA_IR
 * \brief   Driver for KA_ IR module.
 * @file    KA_IR.cpp
 * @author  MakeBlock
 * @version V1.0.4
 * @date    2015/11/16
 * @brief   Driver for KA_ IR module.
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

#include "KA_IR.h"

// Provides ISR
#include <avr/interrupt.h>

volatile irparams_t irparams;

/**
// These versions of MATCH, MATCH_MARK, and MATCH_SPACE are only for debugging.
// To use them, set DEBUG in IRremoteInt.h
// Normally macros are used for efficiency
*/
int MATCH(int measured, int desired) {return measured >= TICKS_LOW(desired) && measured <= TICKS_HIGH(desired);}
int MATCH_MARK(int measured_ticks, int desired_us) {return MATCH(measured_ticks, (desired_us + MARK_EXCESS));}
int MATCH_SPACE(int measured_ticks, int desired_us) {return MATCH(measured_ticks, (desired_us - MARK_EXCESS));}

/**
// TIMER2 interrupt code to collect raw data.
// Widths of alternating SPACE, MARK are recorded in rawbuf.
// Recorded in ticks of 50 microseconds.
// rawlen counts the number of entries recorded so far.
// First entry is the SPACE between transmissions.
// As soon as a SPACE gets long, ready is set, state switches to IDLE, timing of SPACE continues.
// As soon as first MARK arrives, gap width is recorded, ready is cleared, and new logging starts
*/
ISR(TIMER_INTR_NAME)
{
  TIMER_RESET;

  uint8_t irdata = (uint8_t)digitalRead(irparams.recvpin);

  irparams.timer++; // One more 50us tick
  if (irparams.rawlen >= RAWBUF) {
    // Buffer overflow
    irparams.rcvstate = STATE_STOP;
  }
  switch(irparams.rcvstate) {
  case STATE_IDLE: // In the middle of a gap
    if (irdata == MARK) {
      if (irparams.timer < GAP_TICKS) {
        // Not big enough to be a gap.
        irparams.timer = 0;
      } 
      else {
        // gap just ended, record duration and start recording transmission
        irparams.rawlen = 0;
        irparams.rawbuf[irparams.rawlen++] = irparams.timer;
        irparams.timer = 0;
        irparams.rcvstate = STATE_MARK;
      }
    }
    break;
  case STATE_MARK: // timing MARK
    if (irdata == SPACE) {   // MARK ended, record time
      irparams.rawbuf[irparams.rawlen++] = irparams.timer;
      irparams.timer = 0;
      irparams.rcvstate = STATE_SPACE;
    }
    break;
  case STATE_SPACE: // timing SPACE
    if (irdata == MARK) { // SPACE just ended, record it
      irparams.rawbuf[irparams.rawlen++] = irparams.timer;
      irparams.timer = 0;
      irparams.rcvstate = STATE_MARK;
    } 
    else { // SPACE
      if (irparams.timer > GAP_TICKS) {
        // big SPACE, indicates gap between codes
        // Mark current code as ready for processing
        // Switch to STOP
        // Don't reset timer; keep counting space width
        irparams.rcvstate = STATE_STOP;
      } 
    }
    break;
  case STATE_STOP: // waiting, measuring gap
    if (irdata == MARK) { // reset gap timer
      irparams.timer = 0;
    }
    break;
  }

  /*
  if (irparams.blinkflag) {
    if (irdata == MARK) {
      BLINKLED_ON();  // turn pin 13 LED on
    } 
    else {
      BLINKLED_OFF();  // turn pin 13 LED off
    }
  }
  */
}

/**
 * Alternate Constructor which can call your own function to map the IR to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
KA_IR::KA_IR(void) : KA_Port()
{

}

/**
 * Alternate Constructor which can call your own function to map the IR to arduino port,
 * no pins are used or initialized here.
 * \param[in]
 *   None
 */
KA_IR::KA_IR(uint8_t port) : KA_Port(port)
{
	irparams.recvpin = s1;
	pinMode(irparams.recvpin, INPUT);
}

/**
 Decodes the received IR message
 Returns 0 if no data ready, 1 if data ready.
 Results of decoding are stored in results
*/
int KA_IR::decode(decode_results *results) 
{
  results->rawbuf = irparams.rawbuf;
  results->rawlen = irparams.rawlen;
  if (irparams.rcvstate != STATE_STOP) {
    return ERR;
  }

  if (decodeNEC(results)) {
    return DECODED;
  }
/*
  if (decodeSony(results)) {
    return DECODED;
  }
  if (decodeSanyo(results)) {
    return DECODED;
  }
  if (decodeMitsubishi(results)) {
    return DECODED;
  }
  if (decodeRC5(results)) {
    return DECODED;
  }
  if (decodeRC6(results)) {
    return DECODED;
  }
  if (decodePanasonic(results)) {
	return DECODED;
  }
  if (decodeJVC(results)) {
	return DECODED;
  }
  
  // decodeHash returns a hash on any input.
  // Thus, it needs to be last in the list.
  // If you add any decodes, add them before this.
*/  
  if (decodeHash(results)) {
    return DECODED;
  }
  // Throw away and start over
  resume();
  return ERR;
}

/**
 Decodes the received IR message
 Returns 0 if no data ready, 1 if data ready.
 Results of decoding are stored in results
*/
/*
ErrorStatus KA_IR::decode(void) 
{
  rawbuf = irparams.rawbuf;
  rawlen = irparams.rawlen;
  if (irparams.rcvstate != STATE_STOP) {
    return ERROR;
  }
  if (decodeNEC()) {
    return SUCCESS;
  }  
  if (decodeHash()) {
    return SUCCESS;
  }
  // Throw away and start over
  resume();
  return ERROR;
}
*/
ErrorStatus KA_IR::decode()
{
  rawbuf = irparams.rawbuf;
  rawlen = irparams.rawlen;
  if (irparams.rcvstate != STATE_STOP)
  {
    return ERROR;
  }

  if (decodeNEC())
  {
    begin();
    return SUCCESS;
  }
  begin();
  return ERROR;
}

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
 /*
ErrorStatus KA_IR::decode()
{  
  rawbuf = irparams.rawbuf;
  rawlen = irparams.rawlen;
  if (irparams.rcvstate != STATE_STOP)
  {
    return ERROR;
  }

  if (decodeNEC())
  {
//    begin();
    return SUCCESS;
  }
  //    begin();
    irparams.rcvstate = STATE_IDLE;
  irparams.rawlen = 0;
  return ERROR;
}
*/

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
void KA_IR::begin()
{ 
  irDelayTime = 0;
  irIndex = 0;
  irRead = 0;
  irReady = false;
  irBuffer = "";
  irPressed = false;
	
  enableIRIn() ;
  pinMode(irparams.recvpin, INPUT);
}

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
void KA_IR::begin(int pin)
{
  irDelayTime = 0;
  irIndex = 0;
  irRead = 0;
  irReady = false;
  irBuffer = "";
  irPressed = false;
	
  enableIRIn() ;

  irparams.recvpin = pin;
  pinMode(pin, INPUT);
}

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
void KA_IR::end()
{
  EIMSK &= ~(1 << INT0);
}


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
void KA_IR::sendString(String s)
{
  unsigned long l;
  uint8_t data;
  s.concat('\n');
  for(unsigned char i = 0;i < s.length();i++)
  {
    data = s.charAt(i);
    l = 0x0000ffff & (uint8_t)(~data);
    l = l << 8;
    l = l + ((uint8_t)data);
    l = l << 16;
    l = l | 0x000000ff;
    sendNEC(l,32);
    delay(20);
  }
  enableIRIn();
}

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
void KA_IR::sendString(float v)
{
  dtostrf(v,5, 2, floatString);
  sendString(floatString);
}

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
void KA_IR::sendNEC(unsigned long data, int nbits)
{
  enableIROut(38);
  mark(NEC_HDR_MARK);
  space(NEC_HDR_SPACE);
  for (int i = 0; i < nbits; i++)
  {
    if (data & 1) 
    {
      mark(NEC_BIT_MARK);
      space(NEC_ONE_SPACE);
    } 
    else 
    {
      mark(NEC_BIT_MARK);
      space(NEC_ZERO_SPACE);
    }
    data >>= 1;
  }
  mark(NEC_BIT_MARK);
  space(0);
}

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
void KA_IR::sendRaw(unsigned int buf[], int len, uint8_t hz)
{
  enableIROut(hz);
  for (int i = 0; i < len; i++)
  {
    if (i & 1)
    {
      space(buf[i]);
    } 
    else
    {
      mark(buf[i]);
    }
  }
  space(0); // Just to be sure
}

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
void KA_IR::enableIROut(uint8_t khz)
{
  TIMER_DISABLE_INTR; //Timer2 disable Interrupt
  TIMER_CONFIG_KHZ(khz);
}

/**
 * Alternate Constructor which can call your own function to map the IR to arduino port,
 * no pins are used or initialized here.// initialization
 * \param[in]
 *   None
 */
void KA_IR::enableIRIn() 
{
  cli();
  // setup pulse clock timer interrupt
  //Prescale /8 (16M/8 = 0.5 microseconds per tick)
  // Therefore, the timer interval can range from 0.5 to 128 microseconds
  // depending on the reset value (255 to 0)
  TIMER_CONFIG_NORMAL();

  //Timer2 Overflow Interrupt Enable
  TIMER_ENABLE_INTR;

  TIMER_RESET;

  sei();  // enable interrupts

  // initialize state machine variables
  irparams.rcvstate = STATE_IDLE;
  irparams.rawlen = 0;

  // set pin modes
  //pinMode(irparams.recvpin, INPUT);
}

/**
 * Alternate Constructor which can call your own function to map the IR to arduino port,
 * no pins are used or initialized here.// initialization
 * \param[in]
 *   None
 */
void KA_IR::resume() 
{
  irparams.rcvstate = STATE_IDLE;
  irparams.rawlen = 0;
}

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
void KA_IR::mark(uint16_t us)
{
  // Sends an IR mark for the specified number of microseconds.
  // The mark output is modulated at the PWM frequency.
  TIMER_ENABLE_PWM; // Enable pin 3 PWM output
  delayMicroseconds(us);
}

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
 *
 Leave pin off for time (given in microseconds) 
 */
void KA_IR::space(uint16_t us)
{
  // Sends an IR space for the specified number of microseconds.
  // A space is no output, so the PWM output is disabled.
  TIMER_DISABLE_PWM; // Disable pin 3 PWM output
  delayMicroseconds(us);
}

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

unsigned char KA_IR::getCode()
{
	irIndex = 0;
	loop();
	return irRead;	
}
/*
unsigned char KA_IR::getCode()
{
	irRead = 0;
  if(decode())
  {
    irRead = ((value >> 8) >> 8) & 0xff;	
//    irPressed = true;
//    if(irRead == 0xa || irRead == 0xd)
//    {
//      irIndex = 0;
//      irReady = true;
//    }
    else
    {
      irBuffer += irRead; 
      irIndex++;
      if(irIndex > 64)
      {
        irIndex = 0;
        irBuffer = "";
      }
    }
    irDelayTime =  millis();
  }


}
  resume();	
//millis();
delay(100);
	return irRead;	
}
*/
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
String KA_IR::getString()
{
  if(decode())
  {
    irRead = ((value >> 8) >> 8) & 0xff;
    if(irRead == 0xa || irRead == 0xd)
    {
      irIndex = 0;
      irReady = true;
    }
    else
    {
      irBuffer += irRead; 
      irIndex++;
    }
    irDelayTime = millis();
  }
  else
  {
    if(irRead > 0)
    {
      if(millis() - irDelayTime > 100)
      {
        irPressed = false;
        irRead = 0;
        irDelayTime = millis();
        Pre_Str = "";
      }
    }
  }
  if(irReady)
  {
    irReady = false;
    String s = String(irBuffer);
    Pre_Str = s;
    irBuffer = "";
    return s;
  }
  return Pre_Str;
}

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
boolean KA_IR::keyPressed(unsigned char r)
{
  irIndex = 0;
  loop();
  return irRead == r;
}

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
void KA_IR::loop()
{
  if(decode())
  {
    irRead = ((value >> 8) >> 8) & 0xff;
    irPressed = true;
    if(irRead == 0xa || irRead == 0xd)
    {
      irIndex = 0;
      irReady = true;
    }
    else
    {
      irBuffer += irRead; 
      irIndex++;
      if(irIndex > 64)
      {
        irIndex = 0;
        irBuffer = "";
      }
    }
    irDelayTime =  millis();
  }
  else
  {
    if(irRead > 0)
    {
      if(millis() - irDelayTime > 200)
      {
        irPressed = false;
        irRead = 0;
        irDelayTime = millis();
      }
    }
  }
//  resume();	
}

/**
// NECs have a repeat only 4 items long
*/
long KA_IR::decodeNEC(decode_results *results) {
  long data = 0;
  int offset = 1; // Skip first space
  // Initial mark
  if (!MATCH_MARK(results->rawbuf[offset], NEC_HDR_MARK)) {
    return ERR;
  }
  offset++;
  // Check for repeat
  if (irparams.rawlen == 4 &&
    MATCH_SPACE(results->rawbuf[offset], NEC_RPT_SPACE) &&
    MATCH_MARK(results->rawbuf[offset+1], NEC_BIT_MARK)) {
    results->bits = 0;
    results->value = REPEAT;
    results->decode_type = NEC;
    return DECODED;
  }
  if (irparams.rawlen < 2 * NEC_BITS + 4) {
    return ERR;
  }
  // Initial space  
  if (!MATCH_SPACE(results->rawbuf[offset], NEC_HDR_SPACE)) {
    return ERR;
  }
  offset++;
  for (int i = 0; i < NEC_BITS; i++) {
    if (!MATCH_MARK(results->rawbuf[offset], NEC_BIT_MARK)) {
      return ERR;
    }
    offset++;
    if (MATCH_SPACE(results->rawbuf[offset], NEC_ONE_SPACE)) {
      data = (data << 1) | 1;
    } 
    else if (MATCH_SPACE(results->rawbuf[offset], NEC_ZERO_SPACE)) {
      data <<= 1;
    } 
    else {
      return ERR;
    }
    offset++;
  }
  // Success
  results->bits = NEC_BITS;
  results->value = data;
  results->decode_type = NEC;
  return DECODED;
}

/**
// NECs have a repeat only 4 items long
*/

ErrorStatus KA_IR::decodeNEC()
{
	
  uint32_t data = 0;
  int offset = 1; // Skip first space
  // Initial mark
  if (!MATCH(rawbuf[offset], NEC_HDR_MARK)) 
  {
    return ERROR;
  }
  offset++;
  // Check for repeat
  if (rawlen == 4 &&
    MATCH(rawbuf[offset], NEC_RPT_SPACE) &&
    MATCH(rawbuf[offset+1], NEC_BIT_MARK)) 
  {
    bits = 0;
	//value = REPEAT;
    // Serial.println("REPEAT");
    decode_type = NEC;
    return SUCCESS;
  }
  if (rawlen < (2 * NEC_BITS + 4)) 
  {
    return ERROR;
  }
  // Initial space  
  if (!MATCH(rawbuf[offset], NEC_HDR_SPACE)) 
  {
    return ERROR;
  }
  offset++;
  for (int i = 0; i < NEC_BITS; i++)
  {
    if (!MATCH(rawbuf[offset], NEC_BIT_MARK)) 
    {
      return ERROR;
    }
    offset++;
    if (MATCH(rawbuf[offset], NEC_ONE_SPACE))
    {
     // data = (data << 1) | 1;
      data = (data >> 1) | 0x80000000;
    } 
    else if (MATCH(rawbuf[offset], NEC_ZERO_SPACE))
    {
      //data <<= 1;
      data >>= 1;
    } 
    else 
    {
      return ERROR;
    }
    offset++;
  }
  // Success
  bits = NEC_BITS;
  value = data;
  decode_type = NEC;
  return SUCCESS;
}

/*
ErrorStatus KA_IR::decodeNEC()
{
  uint32_t data = 0;
  int offset = 0; // Skip first space
  // Initial mark
  if (!MATCH(rawbuf[offset], NEC_HDR_MARK/50)) 
  {
    return ERROR;
  }
  offset++;
  // Check for repeat
  if (rawlen == 3 &&
    MATCH(rawbuf[offset], NEC_RPT_SPACE/50) &&
    MATCH(rawbuf[offset+1], NEC_BIT_MARK/50)) 
  {
    bits = 0;
    // results->value = REPEAT;
	// Serial.println("REPEAT");
	decode_type = NEC;
    return SUCCESS;
  }
  if (rawlen < (2 * NEC_BITS + 3)) 
  {
    return ERROR;
  }
  // Initial space  
  if (!MATCH(rawbuf[offset], NEC_HDR_SPACE/50)) 
  {
    return ERROR;
  }
  offset++;
  for (int i = 0; i < NEC_BITS; i++)
  {
    if (!MATCH(rawbuf[offset], NEC_BIT_MARK/50)) 
	{
      return ERROR;
    }
    offset++;
    if (MATCH(rawbuf[offset], NEC_ONE_SPACE/50))
	{
      //data = (data << 1) | 1;
      data = (data >> 1) | 0x80000000;
    } 
    else if (MATCH(rawbuf[offset], NEC_ZERO_SPACE/50))
	{
      //data <<= 1;
      data >>= 1;
    } 
    else 
	{
      return ERROR;
    }
    offset++;
  }
  // Success
  bits = NEC_BITS;
  value = data;
  decode_type = NEC;
  return SUCCESS;
}
*/

/*
ErrorStatus KA_IR::decodeNEC(void) {
  long data = 0;
  int offset = 1; // Skip first space
  // Initial mark
  if (!MATCH_MARK(rawbuf[offset], NEC_HDR_MARK)) {
    return ERROR;
  }
  offset++;
  // Check for repeat
  if (irparams.rawlen == 4 &&
    MATCH_SPACE(rawbuf[offset], NEC_RPT_SPACE) &&
    MATCH_MARK(rawbuf[offset+1], NEC_BIT_MARK)) {
    bits = 0;
    value = REPEAT;
    decode_type = NEC;
    return SUCCESS;
  }
  if (irparams.rawlen < 2 * NEC_BITS + 4) {
    return ERROR;
  }
  // Initial space  
  if (!MATCH_SPACE(rawbuf[offset], NEC_HDR_SPACE)) {
    return ERROR;
  }
  offset++;
  for (int i = 0; i < NEC_BITS; i++) {
    if (!MATCH_MARK(rawbuf[offset], NEC_BIT_MARK)) {
      return ERROR;
    }
    offset++;
    if (MATCH_SPACE(rawbuf[offset], NEC_ONE_SPACE)) {
      data = (data << 1) | 1;
    } 
    else if (MATCH_SPACE(rawbuf[offset], NEC_ZERO_SPACE)) {
      data <<= 1;
    } 
    else {
      return ERROR;
    }
    offset++;
  }
  // Success
  bits = NEC_BITS;
  value = data;
  decode_type = NEC;
  return SUCCESS;
}
*/
/*
long KA_IR::decodeSony(decode_results *results) {
  long data = 0;
  if (irparams.rawlen < 2 * SONY_BITS + 2) {
    return ERR;
  }
  int offset = 0; // Dont skip first space, check its size

  // Some Sony's deliver repeats fast after first
  // unfortunately can't spot difference from of repeat from two fast clicks
  if (results->rawbuf[offset] < SONY_DOUBLE_SPACE_USECS) {
    // Serial.print("IR Gap found: ");
    results->bits = 0;
    results->value = REPEAT;
    results->decode_type = SANYO;
    return DECODED;
  }
  offset++;

  // Initial mark
  if (!MATCH_MARK(results->rawbuf[offset], SONY_HDR_MARK)) {
    return ERR;
  }
  offset++;

  while (offset + 1 < irparams.rawlen) {
    if (!MATCH_SPACE(results->rawbuf[offset], SONY_HDR_SPACE)) {
      break;
    }
    offset++;
    if (MATCH_MARK(results->rawbuf[offset], SONY_ONE_MARK)) {
      data = (data << 1) | 1;
    } 
    else if (MATCH_MARK(results->rawbuf[offset], SONY_ZERO_MARK)) {
      data <<= 1;
    } 
    else {
      return ERR;
    }
    offset++;
  }

  // Success
  results->bits = (offset - 1) / 2;
  if (results->bits < 12) {
    results->bits = 0;
    return ERR;
  }
  results->value = data;
  results->decode_type = SONY;
  return DECODED;
}*/
/*
// I think this is a Sanyo decoder - serial = SA 8650B
// Looks like Sony except for timings, 48 chars of data and time/space different
long KA_IR::decodeSanyo(decode_results *results) {
  long data = 0;
  if (irparams.rawlen < 2 * SANYO_BITS + 2) {
    return ERR;
  }
  int offset = 0; // Skip first space
  // Initial space  
  // Put this back in for debugging - note can't use #DEBUG as if Debug on we don't see the repeat cos of the delay
  //Serial.print("IR Gap: ");
  //Serial.println( results->rawbuf[offset]);
  //Serial.println( "test against:");
  //Serial.println(results->rawbuf[offset]);
  
  if (results->rawbuf[offset] < SANYO_DOUBLE_SPACE_USECS) {
    // Serial.print("IR Gap found: ");
    results->bits = 0;
    results->value = REPEAT;
    results->decode_type = SANYO;
    return DECODED;
  }
  offset++;

  // Initial mark
  if (!MATCH_MARK(results->rawbuf[offset], SANYO_HDR_MARK)) {
    return ERR;
  }
  offset++;

  // Skip Second Mark
  if (!MATCH_MARK(results->rawbuf[offset], SANYO_HDR_MARK)) {
    return ERR;
  }
  offset++;

  while (offset + 1 < irparams.rawlen) {
    if (!MATCH_SPACE(results->rawbuf[offset], SANYO_HDR_SPACE)) {
      break;
    }
    offset++;
    if (MATCH_MARK(results->rawbuf[offset], SANYO_ONE_MARK)) {
      data = (data << 1) | 1;
    } 
    else if (MATCH_MARK(results->rawbuf[offset], SANYO_ZERO_MARK)) {
      data <<= 1;
    } 
    else {
      return ERR;
    }
    offset++;
  }

  // Success
  results->bits = (offset - 1) / 2;
  if (results->bits < 12) {
    results->bits = 0;
    return ERR;
  }
  results->value = data;
  results->decode_type = SANYO;
  return DECODED;
}
*/
/*
// Looks like Sony except for timings, 48 chars of data and time/space different
long KA_IR::decodeMitsubishi(decode_results *results) {
  // Serial.print("?!? decoding Mitsubishi:");Serial.print(irparams.rawlen); Serial.print(" want "); Serial.println( 2 * MITSUBISHI_BITS + 2);
  long data = 0;
  if (irparams.rawlen < 2 * MITSUBISHI_BITS + 2) {
    return ERR;
  }
  int offset = 0; // Skip first space
  // Initial space  
  // Put this back in for debugging - note can't use #DEBUG as if Debug on we don't see the repeat cos of the delay
  //Serial.print("IR Gap: ");
  //Serial.println( results->rawbuf[offset]);
  //Serial.println( "test against:");
  //Serial.println(results->rawbuf[offset]);
  
  // Not seeing double keys from Mitsubishi
  //if (results->rawbuf[offset] < MITSUBISHI_DOUBLE_SPACE_USECS) {
    // Serial.print("IR Gap found: ");
  //  results->bits = 0;
  //  results->value = REPEAT;
  //  results->decode_type = MITSUBISHI;
  //  return DECODED;
  //}
  
  offset++;

  // Typical
  // 14200 7 41 7 42 7 42 7 17 7 17 7 18 7 41 7 18 7 17 7 17 7 18 7 41 8 17 7 17 7 18 7 17 7 

  // Initial Space
  if (!MATCH_MARK(results->rawbuf[offset], MITSUBISHI_HDR_SPACE)) {
    return ERR;
  }
  offset++;
  while (offset + 1 < irparams.rawlen) {
    if (MATCH_MARK(results->rawbuf[offset], MITSUBISHI_ONE_MARK)) {
      data = (data << 1) | 1;
    } 
    else if (MATCH_MARK(results->rawbuf[offset], MITSUBISHI_ZERO_MARK)) {
      data <<= 1;
    } 
    else {
      // Serial.println("A"); Serial.println(offset); Serial.println(results->rawbuf[offset]);
      return ERR;
    }
    offset++;
    if (!MATCH_SPACE(results->rawbuf[offset], MITSUBISHI_HDR_SPACE)) {
      // Serial.println("B"); Serial.println(offset); Serial.println(results->rawbuf[offset]);
      break;
    }
    offset++;
  }

  // Success
  results->bits = (offset - 1) / 2;
  if (results->bits < MITSUBISHI_BITS) {
    results->bits = 0;
    return ERR;
  }
  results->value = data;
  results->decode_type = MITSUBISHI;
  return DECODED;
}*/

/**
// Gets one undecoded level at a time from the raw buffer.
// The RC5/6 decoding is easier if the data is broken into time intervals.
// E.g. if the buffer has MARK for 2 time intervals and SPACE for 1,
// successive calls to getRClevel will return MARK, MARK, SPACE.
// offset and used are updated to keep track of the current position.
// t1 is the time interval for a single bit in microseconds.
// Returns -1 for error (measured time interval is not a multiple of t1).
*/
int KA_IR::getRClevel(decode_results *results, int *offset, int *used, int t1) {
  if (*offset >= results->rawlen) {
    // After end of recorded buffer, assume SPACE.
    return SPACE;
  }
  int width = results->rawbuf[*offset];
  int val = ((*offset) % 2) ? MARK : SPACE;
  int correction = (val == MARK) ? MARK_EXCESS : - MARK_EXCESS;

  int avail;
  if (MATCH(width, t1 + correction)) {
    avail = 1;
  } 
  else if (MATCH(width, 2*t1 + correction)) {
    avail = 2;
  } 
  else if (MATCH(width, 3*t1 + correction)) {
    avail = 3;
  } 
  else {
    return -1;
  }

  (*used)++;
  if (*used >= avail) {
    *used = 0;
    (*offset)++;
  }
#ifdef DEBUG
  if (val == MARK) {
    Serial.println("MARK");
  } 
  else {
    Serial.println("SPACE");
  }
#endif
  return val;   
}
/*
long KA_IR::decodeRC5(decode_results *results) {
  if (irparams.rawlen < MIN_RC5_SAMPLES + 2) {
    return ERR;
  }
  int offset = 1; // Skip gap space
  long data = 0;
  int used = 0;
  // Get start bits
  if (getRClevel(results, &offset, &used, RC5_T1) != MARK) return ERR;
  if (getRClevel(results, &offset, &used, RC5_T1) != SPACE) return ERR;
  if (getRClevel(results, &offset, &used, RC5_T1) != MARK) return ERR;
  int nbits;
  for (nbits = 0; offset < irparams.rawlen; nbits++) {
    int levelA = getRClevel(results, &offset, &used, RC5_T1); 
    int levelB = getRClevel(results, &offset, &used, RC5_T1);
    if (levelA == SPACE && levelB == MARK) {
      // 1 bit
      data = (data << 1) | 1;
    } 
    else if (levelA == MARK && levelB == SPACE) {
      // zero bit
      data <<= 1;
    } 
    else {
      return ERR;
    } 
  }

  // Success
  results->bits = nbits;
  results->value = data;
  results->decode_type = RC5;
  return DECODED;
}*/
/*
long KA_IR::decodeRC6(decode_results *results) {
  if (results->rawlen < MIN_RC6_SAMPLES) {
    return ERR;
  }
  int offset = 1; // Skip first space
  // Initial mark
  if (!MATCH_MARK(results->rawbuf[offset], RC6_HDR_MARK)) {
    return ERR;
  }
  offset++;
  if (!MATCH_SPACE(results->rawbuf[offset], RC6_HDR_SPACE)) {
    return ERR;
  }
  offset++;
  long data = 0;
  int used = 0;
  // Get start bit (1)
  if (getRClevel(results, &offset, &used, RC6_T1) != MARK) return ERR;
  if (getRClevel(results, &offset, &used, RC6_T1) != SPACE) return ERR;
  int nbits;
  for (nbits = 0; offset < results->rawlen; nbits++) {
    int levelA, levelB; // Next two levels
    levelA = getRClevel(results, &offset, &used, RC6_T1); 
    if (nbits == 3) {
      // T bit is double wide; make sure second half matches
      if (levelA != getRClevel(results, &offset, &used, RC6_T1)) return ERR;
    } 
    levelB = getRClevel(results, &offset, &used, RC6_T1);
    if (nbits == 3) {
      // T bit is double wide; make sure second half matches
      if (levelB != getRClevel(results, &offset, &used, RC6_T1)) return ERR;
    } 
    if (levelA == MARK && levelB == SPACE) { // reversed compared to RC5
      // 1 bit
      data = (data << 1) | 1;
    } 
    else if (levelA == SPACE && levelB == MARK) {
      // zero bit
      data <<= 1;
    } 
    else {
      return ERR; // Error
    } 
  }
  // Success
  results->bits = nbits;
  results->value = data;
  results->decode_type = RC6;
  return DECODED;
}*/
/*
long KA_IR::decodePanasonic(decode_results *results) {
    unsigned long long data = 0;
    int offset = 1;
    
    if (!MATCH_MARK(results->rawbuf[offset], PANASONIC_HDR_MARK)) {
        return ERR;
    }
    offset++;
    if (!MATCH_MARK(results->rawbuf[offset], PANASONIC_HDR_SPACE)) {
        return ERR;
    }
    offset++;
    
    // decode address
    for (int i = 0; i < PANASONIC_BITS; i++) {
        if (!MATCH_MARK(results->rawbuf[offset++], PANASONIC_BIT_MARK)) {
            return ERR;
        }
        if (MATCH_SPACE(results->rawbuf[offset],PANASONIC_ONE_SPACE)) {
            data = (data << 1) | 1;
        } else if (MATCH_SPACE(results->rawbuf[offset],PANASONIC_ZERO_SPACE)) {
            data <<= 1;
        } else {
            return ERR;
        }
        offset++;
    }
    results->value = (unsigned long)data;
    results->panasonicAddress = (unsigned int)(data >> 32);
    results->decode_type = PANASONIC;
    results->bits = PANASONIC_BITS;
    return DECODED;
}*/
/*
long KA_IR::decodeJVC(decode_results *results) {
    long data = 0;
    int offset = 1; // Skip first space
    // Check for repeat
    if (irparams.rawlen - 1 == 33 &&
        MATCH_MARK(results->rawbuf[offset], JVC_BIT_MARK) &&
        MATCH_MARK(results->rawbuf[irparams.rawlen-1], JVC_BIT_MARK)) {
        results->bits = 0;
        results->value = REPEAT;
        results->decode_type = JVC;
        return DECODED;
    } 
    // Initial mark
    if (!MATCH_MARK(results->rawbuf[offset], JVC_HDR_MARK)) {
        return ERR;
    }
    offset++; 
    if (irparams.rawlen < 2 * JVC_BITS + 1 ) {
        return ERR;
    }
    // Initial space 
    if (!MATCH_SPACE(results->rawbuf[offset], JVC_HDR_SPACE)) {
        return ERR;
    }
    offset++;
    for (int i = 0; i < JVC_BITS; i++) {
        if (!MATCH_MARK(results->rawbuf[offset], JVC_BIT_MARK)) {
            return ERR;
        }
        offset++;
        if (MATCH_SPACE(results->rawbuf[offset], JVC_ONE_SPACE)) {
            data = (data << 1) | 1;
        } 
        else if (MATCH_SPACE(results->rawbuf[offset], JVC_ZERO_SPACE)) {
            data <<= 1;
        } 
        else {
            return ERR;
        }
        offset++;
    }
    //Stop bit
    if (!MATCH_MARK(results->rawbuf[offset], JVC_BIT_MARK)){
        return ERR;
    }
    // Success
    results->bits = JVC_BITS;
    results->value = data;
    results->decode_type = JVC;
    return DECODED;
}*/

/* -----------------------------------------------------------------------
 * hashdecode - decode an arbitrary IR code.
 * Instead of decoding using a standard encoding scheme
 * (e.g. Sony, NEC, RC5), the code is hashed to a 32-bit value.
 *
 * The algorithm: look at the sequence of MARK signals, and see if each one
 * is shorter (0), the same length (1), or longer (2) than the previous.
 * Do the same with the SPACE signals.  Hszh the resulting sequence of 0's,
 * 1's, and 2's to a 32-bit value.  This will give a unique value for each
 * different code (probably), for most code systems.
 *
 * http://arcfn.com/2010/01/using-arbitrary-remotes-with-arduino.html
 */

/**
// Compare two tick values, returning 0 if newval is shorter,
// 1 if newval is equal, and 2 if newval is longer
// Use a tolerance of 20%
*/
int KA_IR::compare(unsigned int oldval, unsigned int newval) {
  if (newval < oldval * .8) {
    return 0;
  } 
  else if (oldval < newval * .8) {
    return 2;
  } 
  else {
    return 1;
  }
}

// Use FNV hash algorithm: http://isthe.com/chongo/tech/comp/fnv/#FNV-param
#define FNV_PRIME_32 16777619
#define FNV_BASIS_32 2166136261

/** Converts the raw code values into a 32-bit hash code.
 * Hopefully this code is unique for each button.
 * This isn't a "real" decoding, just an arbitrary value.
 */
long KA_IR::decodeHash(decode_results *results) {
  // Require at least 6 samples to prevent triggering on noise
  if (results->rawlen < 6) {
    return ERR;
  }
  long hash = FNV_BASIS_32;
  for (int i = 1; i+2 < results->rawlen; i++) {
    int value =  compare(results->rawbuf[i], results->rawbuf[i+2]);
    // Add value into the hash
    hash = (hash * FNV_PRIME_32) ^ value;
  }
  results->value = hash;
  results->bits = 32;
  results->decode_type = UNKNOWN;
  return DECODED;
}

/** Converts the raw code values into a 32-bit hash code.
 * Hopefully this code is unique for each button.
 * This isn't a "real" decoding, just an arbitrary value.
 */
ErrorStatus KA_IR::decodeHash() 
{
  // Require at least 6 samples to prevent triggering on noise
  if (rawlen < 6) {
    return ERROR;
  }
  long hash = FNV_BASIS_32;
  for (int i = 1; i+2 < rawlen; i++) {
    int value =  compare(rawbuf[i], rawbuf[i+2]);
    // Add value into the hash
    hash = (hash * FNV_PRIME_32) ^ value;
  }
  value = hash;
  bits = 32;
  decode_type = UNKNOWN;
  return SUCCESS;
}
