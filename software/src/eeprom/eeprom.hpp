#ifndef EEPROM_EEPROM_HPP_
#define EEPROM_EEPROM_HPP_

#include <avr/io.h>

namespace eeprom
{
	void write(unsigned int address, unsigned int data);
	unsigned int read(unsigned int address);
	unsigned long int get_time();
	void add_time(unsigned long int time);
	void reset_time();
}



#endif /* EEPROM_EEPROM_HPP_ */
