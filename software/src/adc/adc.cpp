#include "adc.hpp"

namespace adc
{
	void init()
	{
		// init ADC in free running mode
		ADCSRA = 0b11100111;
		ADMUX = 0b01000000;
	}

	int read_speed()
	{
		// check if ADC input is set to 3
		if(ADMUX != 0b01000011)
		{
			ADMUX = 0b01000011;
			_delay_ms(5);
		}
		unsigned long int result = 0;

		// do a few measurements
		for(int a = 0; a<SPEED_MEASUREMENT_ACCURACY; a++)
		{
			result += ADC;
			_delay_ms(5);
		}

		// compute and return average of all measurements
		result /= SPEED_MEASUREMENT_ACCURACY;
		return (int) result;
	}

	int read_speed_regulator()
	{
		// check if ADC input is set to 0
		if(ADMUX != 0b01000000)
		{
			ADMUX = 0b01000000;
			_delay_ms(5);
		}
		unsigned long int result = 0;

		// do a few measurements
		for(int a = 0; a<VOLTAGE_MEASUREMENT_ACCURACY; a++)
		{
			result += ADC;
			_delay_ms(5);
		}

		// compute and return average of all measurements
		result /= VOLTAGE_MEASUREMENT_ACCURACY;
		return (int) result;
	}

	int read_tmp_1()
	{
		// check if ADC input is set to 1
		if(ADMUX != 0b01000001)
		{
			ADMUX = 0b01000001;
			_delay_ms(5);
		}
		unsigned long int result = 0;

		// do a few measurements
		for(int a = 0; a<VOLTAGE_MEASUREMENT_ACCURACY; a++)
		{
			result += ADC;
			_delay_ms(5);
		}

		// compute and return average of all measurements
		result /= VOLTAGE_MEASUREMENT_ACCURACY;
		return (int) result;
	}

	int read_tmp_2()
	{
		// check if ADC input is set to 2
		if(ADMUX != 0b01000010)
		{
			ADMUX = 0b01000010;
			_delay_ms(5);
		}
		unsigned long int result = 0;

		// do a few measurements
		for(int a = 0; a<VOLTAGE_MEASUREMENT_ACCURACY; a++)
		{
			result += ADC;
			_delay_ms(5);
		}

		// compute and return average of all measurements
		result /= VOLTAGE_MEASUREMENT_ACCURACY;
		return (int) result;
	}


}

