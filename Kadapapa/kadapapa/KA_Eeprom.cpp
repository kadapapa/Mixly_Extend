/*
* File:   KA_Eeprom.cpp
* Author: Manjunath CV
*
* Created on February 16, 2016, 12:19 AM
*/

//#include "utility/Wire.h"
#include <Wire.h>
#include "KA_Eeprom.h"

KA_Eeprom::KA_Eeprom(uint8_t i2c_address)
{
	Wire.begin();
	this->i2c_address = i2c_address;
}

KA_Eeprom::KA_Eeprom(uint8_t i2c_address, uint8_t eeprom_size)
{
	Wire.begin();
	this->i2c_address = i2c_address;
	this->eeprom_size = eeprom_size;
}

uint8_t KA_Eeprom::read(uint16_t address)
{
	uint8_t first,second,data;
	uint8_t amount = 0x01;
	
	Wire.beginTransmission(i2c_address);
	
	first = highByte(address);
	second = lowByte(address);
	
	Wire.write(first);      //First Word Address
	Wire.write(second);      //Second Word Address
	
	Wire.endTransmission();
	delay(10);

	Wire.requestFrom(i2c_address, amount);
	delay(10);
	
	data = Wire.read();
	delay(10);
	
	return data;
}

void KA_Eeprom::write(uint16_t address, uint8_t value)
{
	uint8_t first,second;
	Wire.beginTransmission(i2c_address);

	first = highByte(address);
	second = lowByte(address);

	Wire.write(first);      //First Word Address
	Wire.write(second);      //Second Word Address

	Wire.write(value);     

	delay(10);

	Wire.endTransmission();
	delay(10);
}

void KA_Eeprom::update(uint16_t address, uint8_t value)
{
	uint8_t first,second,data;
	uint8_t amount = 0x01;
	Wire.beginTransmission(i2c_address);

	first = highByte(address);
	second = lowByte(address);

	Wire.write(first);      //First Word Address
	Wire.write(second);      //Second Word Address

	Wire.endTransmission();
	delay(10);

	Wire.requestFrom(i2c_address, amount);
	delay(10);

	data = Wire.read();	
	delay(10);
	
	/* Checking Value */
	if (data != value)
	{
		/* Writing Value */
		Wire.beginTransmission(i2c_address);

		first = highByte(address);
		second = lowByte(address);

		Wire.write(first);      //First Word Address
		Wire.write(second);      //Second Word Address

		Wire.write(value);

		delay(10);

		Wire.endTransmission();
		delay(10);	
	}
}

uint16_t KA_Eeprom::length()
{
	return eeprom_size * 1024;	
}


/*
KA_Eeprom::KA_Eeprom(const KA_Eeprom& orig) {
}

KA_Eeprom::~KA_Eeprom() {
}
*/
