


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
		for (int row = 0; row < 4; ++row) {
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
	// solves the puzzle
	//******
	void solve() {
		set_orig();

		int num_solved = 0; // the number of numbers on the grid
		int cur_square = 0; // the square we're currently on
		//int num_soln_found = 0; // number of solutions found to date
		int first_empty = find_first_empty();

		num_solved = find_num_solved();

		while(1) {
			if (square[cur_square] == 9) {

				if (cur_square == first_empty) {
					// std::cout << "End of searching..." << std::endl;
					break;
				}

				// we have hit a dead end and must got back
				square[cur_square] = 0;
				num_solved--;

				// backup and keep backing up till one that is not original
				do {
					cur_square--;
				} while (is_orig[cur_square]);

				continue;
			}

			// check if we've been to this square before
			if (square[cur_square] == 0) {
				num_solved++;
			}

			// either way, add one
			square[cur_square]++;

			//******
			// check the state
			//******
			// if at least the first row is finished
			if (is_row_filled(0)) {
				if (check_row(0)) {
				} else {
					continue;
				}
			} else {
				do {
					++cur_square;
				} while (cur_square< (4*4) && is_orig[cur_square]);
				continue;
			}

			// if at least the second row is finished
			if (is_row_filled(1)) {
				if (check_row(1)) {
				} else {
					continue;
				}
			} else {
				do {
					++cur_square;
				} while (cur_square< (4*4) && is_orig[cur_square]);
				continue;
			}
			// if at least the third row is finished
			if (is_row_filled(2)) {
				if (check_row(2)) {
				} else {
					continue;
				}
			} else {
				do {
					++cur_square;
				} while (cur_square< (4*4) && is_orig[cur_square]);
				continue;
			}
			// if the full puzzle is finished
			if (cur_square >= (4*4 -1)) {
				if (is_good()) {
					break; // we're done here
				} else {
					continue;
				}
			} else {
				do {
					++cur_square;
				} while (cur_square< (4*4) && is_orig[cur_square]);
			}

/*

			// check if we even have enough squares filled
			if (num_solved == (4*4)) {  // TODO copied wrong???
				do {
					++cur_square;
				} while (is_orig[cur_square] && cur_square<(4*4));

				continue;
			}
			// check if the first row is good, else skip ahead
			if (cur_square == 3 && !check_row(0)) {
				// TODO
				// set the current square to the end of the first row
				//cur_square = 3;
				// and zero out all the non orig numbers for the rest of the puzzle
				//for (int i = 4; i < (4*4); ++i) {
					//if (!is_orig[i]) {
						//square[i] = 0;
					//}
				//}
				continue;
			}
			// finally check if the whole state is good
			if (!is_good()) {
				continue;
			}
			// if we've made is this far then we must be good
			// TODO: continue finding solutions later
			break;

*/
		} // end while
	}

};
