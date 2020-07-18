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
	extern int speed_regulator_state;
	extern int state;
	extern int speed_sensor_state;
	extern unsigned long int working_time;
	extern void init();
}


#endif /* MOTOR_MOTOR_HPP_ */
