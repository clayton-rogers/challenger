#ifndef SOLVER_H
#define SOLVER_H

#if defined(ARDUINO_AVR_UNO)

#include <Arduino.h>

#else

#include <cstdint>
#define byte std::uint8_t
#include <cstring>

#endif

struct Challenger {
	byte square[4*4] = { 0 };
	bool is_orig[4*4] = { false };
	byte side[4] = { 0 };
	byte bottom[4] = { 0 };
	byte top_corner = 0;
	byte bottom_corner = 0;

	int operator==(const Challenger& other) {
		return memcmp(this, &other, sizeof(Challenger));
	}

	//******
	// checks if the current state is good
	//******
	bool is_good();

	//******
	// solves the puzzle
	//******
	bool solve();

private:
	//******
	// increments the first two non original values
	//******
	bool increment_row(byte row);
};

#endif // SOLVER_H
