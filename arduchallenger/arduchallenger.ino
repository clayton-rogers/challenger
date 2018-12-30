/*
	 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 *
 * 10K pot:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 *
 * button minus one pin 8
 * button plus one pin 9
 * button plus five pin 10
 * button enter pin 11
 */

#include <LiquidCrystal.h>
#include "solver.h"

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const byte PIN_MINUS_ONE = 8;
const byte PIN_PLUS_ONE = 9;
const byte PIN_PLUS_FIVE = 10;
const byte PIN_ENTER = 11;

enum class Input_pin {
	MINUS_ONE,
	PLUS_ONE,
	PLUS_FIVE,
	ENTER
};

void setup() {
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);

	// setup buttons
	pinMode(PIN_MINUS_ONE, INPUT_PULLUP);
	pinMode(PIN_PLUS_ONE, INPUT_PULLUP);
	pinMode(PIN_PLUS_FIVE, INPUT_PULLUP);
	pinMode(PIN_ENTER, INPUT_PULLUP);
}

Input_pin get_next_input() {
	Input_pin ret_val;
	while (1) {
		if (digitalRead(PIN_MINUS_ONE) == LOW) {
			ret_val = Input_pin::MINUS_ONE;
			break;
		}
		if (digitalRead(PIN_PLUS_ONE) == LOW) {
			ret_val = Input_pin::PLUS_ONE;
			break;
		}
		if (digitalRead(PIN_PLUS_FIVE) == LOW) {
			ret_val = Input_pin::PLUS_FIVE;
			break;
		}
		if (digitalRead(PIN_ENTER) == LOW) {
			ret_val = Input_pin::ENTER;
			break;
		}
	}
	// wait for debounce
	delay(200);
	while (digitalRead(PIN_MINUS_ONE) == LOW ||
			digitalRead(PIN_PLUS_ONE) == LOW ||
			digitalRead(PIN_PLUS_FIVE) == LOW ||
			digitalRead(PIN_ENTER) == LOW) {}

	return ret_val;
}

void wait_for_enter() {
	while (get_next_input() != Input_pin::ENTER) {}
}

void enter_values(
		byte* values,
		const String prompt,
		const byte max_value,
		bool single_value = false) {
	lcd.clear();
	lcd.setCursor(0,0);

	lcd.print(prompt);

	for (int col = 0; col < 4; ++col) {
		bool finished = false;
		while(!finished) {
			lcd.setCursor(col*3,1);
			lcd.print(values[col]);
			auto input = get_next_input();
			switch(input) {
				case Input_pin::MINUS_ONE:
					if (values[col] == 0) {
						values[col] = max_value+1;
					}
					--values[col];
					break;
				case Input_pin::PLUS_ONE:
					++values[col];
					if (values[col] > max_value) {
						values[col] = 0;
					}
					break;
				case Input_pin::PLUS_FIVE:
					values[col] += 5;
					if (values[col] > max_value) {
						values[col] = 0;
					}
					break;
				case Input_pin::ENTER:
					finished = true;
					break;
			}
		}
		if (single_value) {
			break;
		}
	}
}

Challenger solutions[10];

void loop() {
	Challenger c;
	int num_solutions = 0;

	for (byte row = 0; row < 4; ++row) {
		enter_values(&c.square[row*4], String(F("Enter row ")) + (row+1) + ":", 9);
	}
	enter_values(&c.side[0], String(F("Enter side:")), 36);
	enter_values(&c.bottom[0], String(F("Enter bottom:")), 36);

	enter_values(&c.top_corner, String(F("Enter top corner")), 36, true);
	enter_values(&c.bottom_corner, String(F("Enter bot corner")), 36, true);

	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(F("Solving..."));
	const unsigned long begin = millis();
	while (c.solve()) {
		solutions[num_solutions++] = c;
	}
	const unsigned long end = millis();
	const unsigned long delta_t = end - begin;

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(String(F("Found ")) + num_solutions + F(" solutions"));
	lcd.setCursor(0,1);
	lcd.print(String("In: ") + delta_t + " ms");

	wait_for_enter();

	for (int sol = 0; sol < num_solutions; ++sol) {
		lcd.clear();
		lcd.setCursor(0,0);
		for (int i = 0; i < 4; ++i) {
			lcd.print(solutions[sol].square[0*4 + i]);
			lcd.print(" ");
		}
		for (int i = 0; i < 4; ++i) {
			lcd.print(solutions[sol].square[2*4 + i]);
			lcd.print(" ");
		}
		lcd.setCursor(0,1);
		for (int i = 0; i < 4; ++i) {
			lcd.print(solutions[sol].square[1*4 + i]);
			lcd.print(" ");
		}
		for (int i = 0; i < 4; ++i) {
			lcd.print(solutions[sol].square[3*4 + i]);
			lcd.print(" ");
		}

		wait_for_enter();
	}
}
