#ifndef MOTOR_MOTOR_HPP_
#define MOTOR_MOTOR_HPP_

#define MOTOR_STATE_OFF 0
#define MOTOR_STATE_ON 1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../main.hpp"
#include "../config.hpp"
#include "../adc/adc.hpp"
#include "../eeprom/eeprom.hpp"

namespace motor
{
	extern unsigned long int working_time;
	void init();
	void set_speed_regulator_state(int state);
	void set_speed_sensor_state(int state);
	void start();
	void stop();
}


#endif /* MOTOR_MOTOR_HPP_ */
