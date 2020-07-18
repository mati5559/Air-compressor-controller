#include "eeprom.hpp"

namespace eeprom
{
	void write(unsigned int address, unsigned int data)
	{
		// wait for previous write end
		while(EECR & 0b00000010){};

		// put address and data to registers
		EEAR = address;
		EEDR = data;

		// write
		EECR |= 0b00000100;
		EECR |= 0b00000010;
	}

	unsigned int read(unsigned int address)
	{
		// wait for write end
		while(EECR & 0b00000010){};

		// enter address
		EEAR = address;

		// start read
		EECR |= 0b00000001;

		// return data
		return EEDR;
	}

	unsigned long int get_time()
	{
		unsigned int address = eeprom::read(0x00);
		unsigned long int time = (((unsigned long int) eeprom::read(address))<<16) + (eeprom::read(address+1)<<8) + eeprom::read(address+2);
		return time;
	}


	void add_time(unsigned long int time)
	{
		unsigned int address = eeprom::read(0x00);

		unsigned long int actual_time = (((unsigned long int) eeprom::read(address))<<16) + (eeprom::read(address+1)<<8) + eeprom::read(address+2);
		actual_time += time;

		eeprom::write(address, (actual_time>>16));
		eeprom::write(address+1, ((actual_time>>8) & 0xff));
		eeprom::write(address+2, (actual_time & 0xff));
	}

	void reset_time()
	{
		unsigned int address = eeprom::read(0x00);

		eeprom::write(0x00, address+3);
		eeprom::write(address+3, 0x00);
		eeprom::write(address+4, 0x00);
		eeprom::write(address+5, 0x00);
	}
}
