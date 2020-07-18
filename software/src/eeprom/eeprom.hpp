#ifndef EEPROM_EEPROM_HPP_
#define EEPROM_EEPROM_HPP_

#include <avr/io.h>

namespace eeprom
{
	extern void write(unsigned int address, unsigned int data);
	extern unsigned int read(unsigned int address);
	extern unsigned long int get_time();
	extern void add_time(unsigned long int time);
	extern void reset_time();
}



#endif /* EEPROM_EEPROM_HPP_ */
