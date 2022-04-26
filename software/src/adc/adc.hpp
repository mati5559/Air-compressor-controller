#ifndef ADC_ADC_HPP_
#define ADC_ADC_HPP_

#include <avr/io.h>
#include <util/delay.h>

#include "../config.hpp"

// Read value form speed sensor
#define READ_SPEED adc::read_adc(3)

// Read value from potentiometer
#define READ_SPEED_REGULATOR adc::read_adc(0)

// Temperature sensors
#define READ_TMP_1 adc::read_adc(1)
#define READ_TMP_2 adc::read_adc(2)


namespace adc
{
	void init();
	int read_adc(uint8_t channel);
}

#endif /* ADC_ADC_HPP_ */
