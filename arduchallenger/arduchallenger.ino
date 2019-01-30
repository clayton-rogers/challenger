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
#include "mario.h"

//#define OPT_SERIAL

const int rs = 2, en = 3, d4 = 4, d5 = 12, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int MAX_SOL = 25;
Challenger solutions[MAX_SOL];

const byte PIN_MINUS_ONE = 8;
const byte PIN_PLUS_ONE = 9;
const byte PIN_PLUS_FIVE = 10;
const byte PIN_ENTER = 11;
const byte PIN_BUZZER = 5;

enum class Input_pin {
	MINUS_ONE,
	PLUS_ONE,
	PLUS_FIVE,
	ENTER
};

Challenger bench_puzzle;

void setup() {
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);

#if defined(OPT_SERIAL)
	Serial.begin(115200);
#endif

	// setup buttons
	pinMode(PIN_MINUS_ONE, INPUT_PULLUP);
	pinMode(PIN_PLUS_ONE, INPUT_PULLUP);
	pinMode(PIN_PLUS_FIVE, INPUT_PULLUP);
	pinMode(PIN_ENTER, INPUT_PULLUP);
	pinMode(PIN_BUZZER, OUTPUT);

	// setup the benchmark puzzle
	bench_puzzle.square[0*4 + 0] = 9;
	bench_puzzle.square[1*4 + 1] = 9;
	bench_puzzle.square[2*4 + 2] = 7;
	bench_puzzle.square[3*4 + 3] = 2;

	bench_puzzle.side[0] = 15;
	bench_puzzle.side[1] = 27;
	bench_puzzle.side[2] = 18;
	bench_puzzle.side[3] = 13;

	bench_puzzle.bottom[0] = 28;
	bench_puzzle.bottom[1] = 15;
	bench_puzzle.bottom[2] = 15;
	bench_puzzle.bottom[3] = 15;

	bench_puzzle.top_corner = 17;
	bench_puzzle.bottom_corner = 27;
}

void play_mario() {

}

#if defined(OPT_SERIAL)
void print_challenger(const Challenger& c) {
	for (byte row = 0; row < 4; ++row) {
		for (byte col = 0; col < 4; ++col) {
			Serial.print(c.square[row*4 + col]);
			Serial.print(' ');
		}
		Serial.println();
	}
	Serial.println();
}
#endif

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

void wait_for_enter(bool& skip) {
	while (true) {
		auto input = get_next_input();
		switch(input) {
			case Input_pin::ENTER:
				skip = false;
				return;
			case Input_pin::MINUS_ONE:
				skip = true;
				return;
			default:
				break;
		}
	}
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

void enter_puzzle(Challenger& c) {
	for (byte row = 0; row < 4; ++row) {
		enter_values(&c.square[row*4], String(F("Enter row ")) + (row+1) + ":", 9);
	}
	enter_values(&c.side[0], String(F("Enter side:")), 36);
	enter_values(&c.bottom[0], String(F("Enter bottom:")), 36);

	enter_values(&c.top_corner, String(F("Enter top corner")), 36, true);
	enter_values(&c.bottom_corner, String(F("Enter bot corner")), 36, true);

}

void solve_and_display_puzzle(Challenger& c) {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print(F("Solving..."));

	int num_solutions = 0;
	const unsigned long begin = millis();
	while (c.solve()) {
#if defined(OPT_SERIAL)
		print_challenger(c);
#endif
		if (num_solutions < MAX_SOL) {
			solutions[num_solutions] = c;
		}
		++num_solutions;
	}
	const unsigned long end = millis();
	const unsigned long delta_t = end - begin;

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(String(F("Found ")) + num_solutions + F(" sol"));
	lcd.setCursor(0,1);
	lcd.print(String("In: ") + delta_t + " ms");
	bool unused;
	wait_for_enter(unused);

	if (num_solutions >= MAX_SOL) {
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print(F("Only showing the"));
		lcd.setCursor(0,1);
		lcd.print(String(F("first ")) + MAX_SOL);
		wait_for_enter(unused);
	}

	const int num_sol_to_display = (num_solutions < MAX_SOL) ? num_solutions : MAX_SOL;

	for (int sol = 0; sol < num_sol_to_display; ++sol) {
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

		bool skip;
		wait_for_enter(skip);
		if (skip) {
			break;
		}
	}
}

enum class Solve_Choice {
	SOLVE,
	BENCH
};

void loop() {
	play_mario(PIN_BUZZER);

	Solve_Choice solve_choice = Solve_Choice::SOLVE;
	bool done = false;
	while (!done) {
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print(F("Puzzle Solver"));
		lcd.setCursor(0,1);
		if (solve_choice == Solve_Choice::SOLVE) {
			lcd.print(F(">"));
		} else {
			lcd.print(F(" "));
		}
		lcd.print(F(" Solve "));
		if (solve_choice == Solve_Choice::BENCH) {
			lcd.print(F(">"));
		} else {
			lcd.print(F(" "));
		}
		lcd.print(F(" Bench "));

		auto input = get_next_input();
		switch (input) {
			case Input_pin::MINUS_ONE:
			case Input_pin::PLUS_ONE:
			case Input_pin::PLUS_FIVE:
				if (solve_choice == Solve_Choice::SOLVE) {
					solve_choice = Solve_Choice::BENCH;
				} else {
					solve_choice = Solve_Choice::SOLVE;
				}
				break;
			case Input_pin::ENTER:
				done = true;
				break;
		}
	}

	Challenger c;

	if (solve_choice == Solve_Choice::SOLVE) {
		enter_puzzle(c);
	} else {
		c = bench_puzzle;
	}
	solve_and_display_puzzle(c);
}
