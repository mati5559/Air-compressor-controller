#ifndef ADC_ADC_HPP_
#define ADC_ADC_HPP_

#include <avr/io.h>
#include <util/delay.h>

#include "../config.hpp"

namespace adc
{
	extern void init();
	extern int read_speed();
	extern int read_speed_regulator();
	extern int read_tmp_1();
	extern int read_tmp_2();
}




#endif /* ADC_ADC_HPP_ */
