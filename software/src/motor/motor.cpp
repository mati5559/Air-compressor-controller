#include "motor.hpp"


namespace motor
{
	int on_time = 0; // Time in us * 2

	int timer2_counter = 0;

	int speed_regulator_state = 0;

	int speed_sensor_state = 0;

	int state = MOTOR_STATE_OFF;

	unsigned long int working_time = 0;

	void init()
	{
		// PD0 as output
		DDRD |= 0b00000001;

		// Analog comparator
		SFIOR &= 0b11110111;
		ACSR = 0b00001010;


		// Timer 1
		TCCR1A = 0b00000000;
		TCCR1B = 0b00001000;

		// Timer 2
		TCCR2 = 0b00001111; // prescaler 1024
		OCR2 = 156; // about 20 ms

		// Turn on interrupts from timers
		TIMSK = 0b10010000;
	}

}


// Executed when zero cross detected
ISR(ANA_COMP_vect)
{
	if(motor::on_time > (MAX_TRIAC_DELAY *2)) motor::on_time = MAX_TRIAC_DELAY * 2;
	if(motor::on_time <= 1) return;


	OCR1A = ((MAX_TRIAC_DELAY * 2) - (motor::on_time))+1; // Time in us * 2
	TCCR1B |= 0b00000010; // Start timer
}



// Executed some time after zero cross
ISR(TIMER1_COMPA_vect)
{
	TCCR1B &= 0b11111000; // Stop timer
	TCNT1 = 0x0000; // Reset timer

	PORTD |= 0b00000001;

	_delay_us(PULSE_TIME);

	PORTD &= 0b11111110;

	if(motor::state == MOTOR_STATE_ON)
	{
		motor::working_time++;
	}
}



// Executed every 20ms
ISR(TIMER2_COMP_vect)
{
	// Timer 2 is 8-bit timer so additional variable is needed to execute instructions every 100ms
	motor::timer2_counter++;

	// Executed every 100ms
	if(motor::timer2_counter>=5)
	{
		motor::timer2_counter = 0;


		// PID algorithm
		static int prev_error = 0;
		static int integral = 0;

		int error = ((TARGET_SPEED + (motor::speed_regulator_state / SPEED_REGULATION_RANGE)) - motor::speed_sensor_state);

		integral += error;

		if(motor::state == MOTOR_STATE_ON)
		{
			motor::on_time += (int) ((double) MOTOR_GAIN_P * error) + ((double) MOTOR_GAIN_I * integral) + ((double) MOTOR_GAIN_D * (error-prev_error));
		}
		else if(motor::state == MOTOR_STATE_OFF)
		{
			integral = 0;
			motor::on_time = 0;
		}


		// Turn off and blink overheat LED if motor would be stuck or if speed sensor would be broken
		if(motor::on_time>9000 && error > 350 && motor::working_time > 400)
		{
			motor::on_time = 0;
			cli();
			wdt_reset();

			while(1)
			{
				for(int i = 0; i < 10; i++)
				{
					_delay_ms(100);
					wdt_reset();
				}

				OVERHEAT_LED_ON;

				for(int i = 0; i < 10; i++)
				{
					_delay_ms(100);
					wdt_reset();
				}

				OVERHEAT_LED_OFF;
			}
		}

		prev_error = error;

	}
}
