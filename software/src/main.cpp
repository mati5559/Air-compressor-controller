/*
 * main.cpp
 *
 * Author: mati5559
 */

#include "main.hpp"


int main()
{
	// Clear watchdog flag
	MCUCSR = 0x00;
	wdt_disable();

	cli();

	// Initialize everything
	_delay_ms(500);
	DDRB 	= 0b00011100; // 0-NC 1-reset oil switch 2-overheat LED 3-fan 4-oil LED 5-pressure sensor
	PORTB 	= 0b00100010; // Pull up oil switch and pressure sensor

	adc::init();
	motor::init();

	sei();

	_delay_ms(500);


	wdt_enable(WDTO_500MS);

	int pressure_sensor_prev_state = 1;
	int thread1 = 0;


	while(1)
	{
		wdt_reset();

		// Make measurements for motor controller
		motor::set_speed_regulator_state(READ_SPEED_REGULATOR);
		motor::set_speed_sensor_state(READ_SPEED);


		// Read pressure sensor and turn on/off motor and fan
		if((PRESSURE_SENSOR_STATE == 1) && (pressure_sensor_prev_state == 0))
		{
			pressure_sensor_prev_state = 1;
			motor::stop();

			_delay_ms(200);
			wdt_reset();

			// Add current working time to EEPROM
			if(motor::working_time > 0)
			{
				eeprom::add_time(motor::working_time/100);
				motor::working_time = 0;
			}

			// Fan will work for some time after motor stop
			for(int a = 0; a < (FAN_OFF_DELAY/100); a++)
			{
				wdt_reset();
				_delay_ms(100);
			}
			FAN_OFF;
		}
		if((PRESSURE_SENSOR_STATE == 0) && (pressure_sensor_prev_state == 1))
		{
			pressure_sensor_prev_state = 0;
			FAN_ON;
			motor::start();

			wdt_reset();
			_delay_ms(100);
			wdt_reset();
		}

		// "Pseudo-multithreading"
		if(thread1>20)
		{
			thread1 = 0;

			// Temperature protection
			if(READ_TMP_1 > MAX_TMP_1)
			{
				motor::stop();
				OVERHEAT_LED_ON;
				FAN_ON;

				while((MAX_TMP_1 - READ_TMP_1) < TMP_HYSTERESIS_1)
				{
					wdt_reset();
					_delay_ms(150);
				}

				pressure_sensor_prev_state = 1;
				FAN_OFF;
				OVERHEAT_LED_OFF;
			}
			if(READ_TMP_2 > MAX_TMP_2)
			{
				motor::stop();
				OVERHEAT_LED_ON;
				FAN_ON;

				while((MAX_TMP_2 - READ_TMP_2) < TMP_HYSTERESIS_2)
				{
					wdt_reset();
					_delay_ms(150);
				}

				pressure_sensor_prev_state = 1;
				FAN_OFF;
				OVERHEAT_LED_OFF;
			}




			// Read working time from EEPROM and check if it is greater than time between oil changes
			if(eeprom::get_time() > OIL_INTERVAL)
			{
				OIL_LED_ON;
			}

			wdt_reset();

			// Reset working time if button is pressed
			if(OIL_SWITCH_STATE == 0)
			{
				_delay_us(100);
				eeprom::reset_time();
				OIL_LED_OFF;

				while(OIL_SWITCH_STATE == 0)
				{
					wdt_reset();
				}
			}
		}

		thread1++;
	}

	return 0;
}

