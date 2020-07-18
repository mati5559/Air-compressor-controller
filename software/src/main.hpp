#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "adc/adc.hpp"
#include "motor/motor.hpp"
#include "eeprom/eeprom.hpp"

// Some definitions
#define OIL_SWITCH_STATE ((PINB & 0b00000010)>>1)
#define PRESSURE_SENSOR_STATE ((PINB & 0b00100000)>>5)

#define OVERHEAT_LED_ON PORTB |= 0b00000100
#define OVERHEAT_LED_OFF PORTB &= 0b11111011

#define FAN_ON PORTB |= 0b00001000
#define FAN_OFF PORTB &= 0b11110111

#define OIL_LED_ON PORTB |= 0b00010000
#define OIL_LED_OFF PORTB &= 0b11101111


#endif /* MAIN_HPP_ */
