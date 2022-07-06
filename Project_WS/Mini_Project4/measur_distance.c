/*
 ================================================================================================
 Name        : measure_distance.c
 Author      : Sama Mostafa
 Description : Measure distance using ultrasonic sensor and display it on LCD.
 ================================================================================================
 */
#include"lcd.h"
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */
#include "ultrasonic.h"

int main(void) {
	uint16 distance;
	/* Enable Global Interrupt I-Bit */
	SREG |= (1 << 7);
	/* Initialize Ultrasonic driver */
	Ultrasonic_init();
	/* Initialize LCD driver */
	LCD_init();
	LCD_moveCursor(1, 0);
	LCD_displayString("distance =    cm");

	while (1) {
		distance = Ultrasonic_readDistance(); //function return distance recieved from ultrasonic in cm
		/*Ultrasonic module HC - SR04 provides 2cm - 400cm  range for measuring distance */
		if (distance > 400 || distance < 2) {
			LCD_moveCursor(1, 10);
			LCD_displayString("--- ");
			LCD_moveCursor(0, 1);
			LCD_displayString(" out of range ");
		} else if (distance <= 400 && distance >= 2) {
			/* Maximum distance = 4 meter and minimum distance =2cm */
			LCD_moveCursor(1, 10);
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
			LCD_moveCursor(0, 1);
			LCD_displayString("Valid distance ");
		}
	}
}

