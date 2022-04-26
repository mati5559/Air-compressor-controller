/*
 * config.hpp
 *
 * Author: mati5559
 */
 
#include "adc.hpp"

namespace adc
{
	void init()
	{
		ADCSRA = 0b10000111;
		ADMUX = 0b01000000;
	}

	int read_adc(uint8_t channel)
	{
		// Choose channel and reference voltage (AVcc with external capacitor)
		ADMUX = 0b01000000 | channel;

		// Start conversion
		ADCSRA |= 0b01000000;

		// Wait until conversion is done
		while ((ADCSRA & 0b00010000) == 0) {};

		return ADC;
	}
}

