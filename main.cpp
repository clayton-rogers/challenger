#include <iostream>
typedef unsigned char byte;
#include "solver.h"


void print_challenge(const Challenger* c) {
	for (int row = 0; row<4; ++row) {
		for (int col = 0; col<4; ++col) {
			std::cout << static_cast<int>(c->square[row*4 + col]) << " ";
		}
		std::cout << std::endl;
	}
}

int main(void) {

	Challenger a;
	a.square[0*4 + 2] = 4;
	a.square[1*4 + 1] = 6;
	a.square[2*4 + 3] = 5;
	a.square[3*4 + 0] = 5;

	a.side[0] = 28;
	a.side[1] = 12;
	a.side[2] = 20;
	a.side[3] = 23;

	a.bottom[0] = 20;
	a.bottom[1] = 16;
	a.bottom[2] = 26;
	a.bottom[3] = 21;

	a.top_corner = 18;
	a.bottom_corner = 31;

	Challenger b;
	b.square[0*4 + 3] = 2;
	b.square[1*4 + 0] = 3;
	b.square[2*4 + 2] = 7;
	b.square[3*4 + 1] = 2;

	b.side[0] = 15;
	b.side[1] = 27;
	b.side[2] = 18;
	b.side[3] = 13;

	b.bottom[0] = 28;
	b.bottom[1] = 15;
	b.bottom[2] = 15;
	b.bottom[3] = 15;

	b.top_corner = 17;
	b.bottom_corner = 27;

	Challenger c;
	c.square[0*4 + 0] = 9;
	c.square[1*4 + 1] = 6;
	c.square[2*4 + 2] = 9;
	c.square[3*4 + 3] = 7;

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

	std::cout << "Puzzle a" << std::endl;
	while (a.solve()) {
		print_challenge(&a);
		std::cout << std::endl;
	}
	std::cout << "Puzzle b" << std::endl;
	while (b.solve()) {
		print_challenge(&b);
		std::cout << std::endl;
	}
	std::cout << "Puzzle c" << std::endl;
	int num = 0;
	while (c.solve()) {
		std::cout << ++num << std::endl;
		print_challenge(&c);
		std::cout << std::endl;
	}

	return 0;

}
