#include <iostream>
typedef unsigned int byte;
#include "solver.h"


void print_challenge(const Challenger* c) {
	for (int row = 0; row<4; ++row) {
		for (int col = 0; col<4; ++col) {
			std::cout << c->square[row*4 + col] << " ";
		}
		std::cout << std::endl;
	}
}


int main(void) {

	Challenger c;
	c.square[0*4 + 2] = 4;
	c.square[1*4 + 1] = 6;
	c.square[2*4 + 3] = 5;
	c.square[3*4 + 0] = 5;

	c.side[0] = 28;
	c.side[1] = 12;
	c.side[2] = 20;
	c.side[3] = 23;

	c.bottom[0] = 20;
	c.bottom[1] = 16;
	c.bottom[2] = 26;
	c.bottom[3] = 21;

	c.top_corner = 18;
	c.bottom_corner = 31;

	while (c.solve()) {
		print_challenge(&c);
	}

	return 0;

}
