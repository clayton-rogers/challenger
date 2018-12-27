


struct Challenger {
	int square[4*4] = { 0 };
	bool is_orig[4*4] = { false };
	int side[4] = { 0 };
	int bottom[4] = { 0 };
	int top_corner = 0;
	int bottom_corner = 0;

	//******
	// checks if the current state is good
	//******
	bool is_good() {

		// check all the rows
		// we check the last row first, since it's most likely to be wrong
		for (int row = 3; row >= 0; --row) {
			int sum = 0;
			for (int col = 0; col < 4; ++col) {
				sum += square[row*4 + col];
			}
			if (sum != side[row]) {
				return false;
			}
		}

		// check all the cols
		for (int col = 0; col < 4; ++col) {
			int sum = 0;
			for (int row = 0; row < 4; ++row) {
				sum += square[row*4 + col];
			}
			if (sum != bottom[col]) {
				return false;
			}
		}

		// check the two corners
		{
			int sum = 0;
			for (int row_col = 0; row_col < 4; ++row_col) {
				sum += square[row_col*4 + row_col];
			}
			if (sum != bottom_corner) {
				return false;
			}
		}
		{
			int sum = 0;
			for (int val = 0; val < 4; ++val) {
				sum += square[val*4 + (3-val)];
			}
			if (sum != top_corner) {
				return false;
			}
		}

		return true; // if nothing has failed yet
	}

	//******
	// checks if just the first row is good
	//******
	bool check_row(int row) {
		int sum = 0;
		for (int col = 0; col < 4; ++col) {
			sum += square[row*4 + col];
		}
		return sum == side[row];
	}
	
	//******
	// finds the first empty square
	//******
	int find_first_empty() {
		for (int i = 0; i < (4*4); ++i) {
			if (square[i] == 0) {
				return i;
			}
		}

		return (4*4 -1);
	}

	//******
	// finds the number of squares solved
	//******
	int find_num_solved() {
		int num = 0;
		for (int i = 0; i < (4*4); ++i) {
			if (square[i] != 0) {
				++num;
			}
		}

		return num;
	}

	//******
	// sets all the orig flags at the beginning
	//******
	void set_orig() {
		for (int i = 0; i < (4*4); ++i) {
			if (square[i] != 0) {
				is_orig[i] = true;
			}
		}
	}
	
	//******
	// whether a row is filled
	//******
	bool is_row_filled(int row) {
		for (int col = 0; col < 4; ++col) {
			if (square[row*4 + col] == 0) {
				return false;
			}
		}
		return true;
	}

	//******
	// returns the position of the original for a given row
	//******
	int get_orig_pos(int row) {
		for (int col = 0; col < 4; ++col) {
			if (is_orig[row*4 + col]) {
				return col;
			}
		}
		return 255;
	}

	//******
	// prefills the empty squares
	//******
	void pre_fill_grid() {
		for (int i = 0; i < (4*4); ++i) {
			if (!is_orig[i]) {
				square[i] = 1;
			}
		}
	}

	//******
	// increments the first two non original values
	//******
	bool increment_row(int row) {
		int* first = nullptr;
		int* second = nullptr;
		for (int i = 0; i < 4; ++i) {
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
			*first = 0;
			*second = 0;
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
	void solve() {
		set_orig();
		pre_fill_grid();

		int cur_row = 0;

		while (1) {
			int last_col = 99;

			// get the last column to be solved
			if (is_orig[cur_row*4 + 3]) {
				last_col = 2;
			} else {
				last_col = 3;
			}
			
			// solve the last col if possible
			square[cur_row*4 + last_col] = 0;
			int sum = 0;
			for (int col = 0; col < 4; ++col) {
				sum += square[cur_row*4 + col];
			}
			if (sum+1 > side[cur_row] ||
					sum+9 < side[cur_row]) {
				// this is unsolvable so increment
				while (!increment_row(cur_row)) {
					--cur_row;
				}
			} else {
				square[cur_row*4 + last_col] = side[cur_row] - sum;
				// if the current row is 2, only the final row remains,
				// which is immediately solvable
				if (cur_row == 2) {
					bool is_bad = false;
					for (int col = 0; col < 4; ++col) {
						if (is_orig[3*4 + col]) {
							int sum = 0;
							for (int row = 0; row < 4; ++row) {
								sum += square[row*4 + col];
							}
							if (sum != bottom[col]) {
								is_bad = true;
							}
						} else {
							int sum = 0;
							square[3*4 + col] = 0;
							for (int row = 0; row < 4; ++row) {
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
						return;
					} else { // else keep incrementing
						while (!increment_row(cur_row)) {
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
