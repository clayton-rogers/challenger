


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
	bool is_good() {

		// check all the rows
		// we check the last row first, since it's most likely to be wrong
		for (byte row = 0; row < 4; ++row) {
			byte sum = 0;
			for (byte col = 0; col < 4; ++col) {
				sum += square[row*4 + col];
			}
			if (sum != side[row]) {
				return false;
			}
		}

		// check all the cols
		for (byte col = 0; col < 4; ++col) {
			byte sum = 0;
			for (byte row = 0; row < 4; ++row) {
				sum += square[row*4 + col];
			}
			if (sum != bottom[col]) {
				return false;
			}
		}

		// check the two corners
		{
			byte sum = 0;
			for (byte row_col = 0; row_col < 4; ++row_col) {
				sum += square[row_col*4 + row_col];
			}
			if (sum != bottom_corner) {
				return false;
			}
		}
		{
			byte sum = 0;
			for (byte val = 0; val < 4; ++val) {
				sum += square[val*4 + (3-val)];
			}
			if (sum != top_corner) {
				return false;
			}
		}

		return true; // if nothing has failed yet
	}

	//******
	// increments the first two non original values
	//******
	bool increment_row(byte row) {
		byte* first = nullptr;
		byte* second = nullptr;
		for (byte i = 0; i < 4; ++i) {
			if (!is_orig[row*4 + i]) {
				if (first == nullptr) {
					first = &square[row*4 + i];
				} else {
					second = &square[row*4 + i];
					break;
				}
			}
		}
		if (*first == 9 && *second == 9) {
			*first = 1;
			*second = 1;
			return false;
		}
		if (*second == 9) {
			*second = 1;
			++(*first);
		} else {
			++(*second);
		}

		return true;
	}

	//******
	// solves the puzzle
	//******
	bool solve() {
		// whether this puzzle already has a solution and
		// we should be finding the next one
		bool has_solution = false;

		for (byte i = 0; i < (4*4); ++i) {
			if (is_orig[i]) {
				has_solution = true;
				break;
			}
		}

		if (has_solution) {
			// if there's already a solution, we need to increment once,
			// then find the next one
			increment_row(2);
		} else {
			// sets all the filled squares to be original
			for (byte i = 0; i < (4*4); ++i) {
				if (square[i] != 0) {
					is_orig[i] = true;
				}
			}

			// sets all non original squares to 1
			for (byte i = 0; i < (4*4); ++i) {
				if (!is_orig[i]) {
					square[i] = 1;
				}
			}
		}

		byte cur_row = 0;

		while (1) {
			byte last_col = 99;

			// get the last column to be solved
			if (is_orig[cur_row*4 + 3]) {
				last_col = 2;
			} else {
				last_col = 3;
			}
			
			// solve the last col if possible
			square[cur_row*4 + last_col] = 0;
			byte sum = 0;
			for (byte col = 0; col < 4; ++col) {
				sum += square[cur_row*4 + col];
			}
			if (sum+1 > side[cur_row] ||
					sum+9 < side[cur_row]) {
				// this is unsolvable so increment
				while (!increment_row(cur_row)) {
					if (cur_row == 0) {
						return false;
					}
					--cur_row;
				}
			} else {
				square[cur_row*4 + last_col] = side[cur_row] - sum;
				// if the current row is 2, only the final row remains,
				// which is immediately solvable
				if (cur_row == 2) {
					bool is_bad = false;
					for (byte col = 0; col < 4; ++col) {
						if (is_orig[3*4 + col]) {
							byte sum = 0;
							for (byte row = 0; row < 4; ++row) {
								sum += square[row*4 + col];
							}
							if (sum != bottom[col]) {
								is_bad = true;
							}
						} else {
							byte sum = 0;
							square[3*4 + col] = 0;
							for (byte row = 0; row < 4; ++row) {
								sum += square[row*4 + col];
							}
							if (sum+1 > bottom[col] ||
									sum+9 < bottom[col]) {
								is_bad = true;
								break;
							} else {
								square[3*4 + col] = bottom[col] - sum;
							}
						}
					}

					if (!is_bad && is_good()) {
						return true;
					} else { // else keep incrementing
						while (!increment_row(cur_row)) {
							if (cur_row == 0) {
								return false;
							}
							--cur_row;
						}
					}
				} else {
					++cur_row;
				}
			}
		}
	}
};
