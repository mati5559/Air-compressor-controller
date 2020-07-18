/*
 * config.hpp
 *
 * Author: mati5559
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_


// It defines how accurate voltage measurements should be
// 10-15 is optimal value
// Too high value will slow down uC
#define SPEED_MEASUREMENT_ACCURACY 10
#define VOLTAGE_MEASUREMENT_ACCURACY 10



// Delay between motor off and fan off [ms]
#define FAN_OFF_DELAY 5000



// Time of triac gate pulse [us]
#define PULSE_TIME 500



// Max time between zero cross detection and turn on triac [us]
// It should be lower than 10000 (for 50Hz) because of zero crossing detector imperfection
#define MAX_TRIAC_DELAY 9000



// Target voltage on speed sensor
//
// TARGED_SPEED = (int) 33,6 * U
// U - speed sensor voltage for target RPM
#define TARGET_SPEED 650



// Gain of PID regulator
#define MOTOR_GAIN_P 0.4
#define MOTOR_GAIN_I 0.002
#define MOTOR_GAIN_D 11.0



// Range of speed regulation potentiometer
// Lower number = wider regulation range
// It must be integer greater than 0
// In my case 5 seems regulation range about 1000 RPM
#define SPEED_REGULATION_RANGE 5



// Circuit has two temperature sensors
// Motor stop if MAX_TMP_x exceed values below
// Motor automatically starts if temperature falls below MAX_TMP_x - TMP_HYSERERSIS_x
//
// MAX_TMP_x = 2250600 / (Rt + 2200)
// TMP_HYSTERESIS_x = (2250600 / (Rt + 2200)) - (2250600 / (Rm + 2200))
// Rt - resistance of sensor in max temperature [ohm]
// Rm - resistance of sensor in temperature, that motor should turn on
#define MAX_TMP_1 600
#define TMP_HYSTERESIS_1 150

#define MAX_TMP_2 600
#define TMP_HYSTERESIS_2 150



// Lifetime of air pump oil [s]
// After this time oil change led will turn on
// 180000 is about 50 hours
#define OIL_INTERVAL 180000

#endif /* CONFIG_HPP_ */
