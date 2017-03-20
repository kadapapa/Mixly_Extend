/* 
 * File:   KA_Eeprom.h
 * Author: Manjunath CV
 *
 * Created on February 16, 2016, 12:19 AM
 */

#ifndef _KA_EEPROM_H
#define _KA_EEPROM_H

#include <Arduino.h>
//#include "utility/Wire.h"

class KA_Eeprom {
public:
    KA_Eeprom(uint8_t i2c_address);
    KA_Eeprom(uint8_t i2c_address, uint8_t eeprom_size);
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
    void update(uint16_t address, uint8_t value);
	uint16_t length(void);
    //void get();
    //void put();
    //KA_Eeprom(const KA_Eeprom& orig);
    //virtual ~KA_Eeprom();

protected:
    uint8_t eeprom_size;
	uint8_t i2c_address;
};

#endif /* AT24CXX_H */

