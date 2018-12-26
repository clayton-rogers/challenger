#include <iostream>
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
	c.square[0*4 + 1] = 3;
	c.square[1*4 + 3] = 7;
	c.square[2*4 + 2] = 8;
	c.square[3*4 + 0] = 8;

	c.side[0] = 14;
	c.side[1] = 27;
	c.side[2] = 15;
	c.side[3] = 32;

	c.bottom[0] = 12;
	c.bottom[1] = 26;
	c.bottom[2] = 33;
	c.bottom[3] = 17;
	
	c.top_corner = 24;
	c.bottom_corner = 25;

	c.solve();

	print_challenge(&c);

	return 0;

}
