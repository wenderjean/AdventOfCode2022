#include <iostream>
#include <fstream>
#include <string>
#include <vector> 

using namespace std;

vector<vector<char>> read_file_and_parse_to_vector() {
  string line;
  ifstream myfile ("day_2_input.txt");
  
  vector<vector<char>> rounds;

  if (myfile.is_open()) {
    while( getline (myfile, line) ) {
			vector<char> round;

			for (char c : line) {
				if (c == ' ') continue;

				round.push_back(c);
			}

			rounds.push_back(round);
    }

    myfile.close();
  }

	return rounds;
}

// Left side:
//   A - Rock
//   B - Paper
//   C - Scissors
//
// Right side:
//   X - Rock
//   Y - Paper
//   Z - Scissors
//
//   Rock     - 1P
//   Paper    - 2P
//   Scissors - 3P
//
//   Lost - 0P
//   Draw - 3P
//   Win  - 6P
//
//   Rock defeats Scissors
//   Scissors defeats Paper
//   Paper defeats Rock
int main() {
	int score = 0;

	for (vector<char> round : read_file_and_parse_to_vector()) {
		char opponent = round.at(0);
		char me = round.at(1);

		if (me == 'X') {
			if (opponent == 'A') me = 'Z';
			if (opponent == 'B') me = 'X';
			if (opponent == 'C') me = 'Y';
		} else if (me == 'Y') {
			if (opponent == 'A') me = 'X';
			if (opponent == 'B') me = 'Y';
			if (opponent == 'C') me = 'Z';
		} else if (me == 'Z') {
			if (opponent == 'A') me = 'Y';
			if (opponent == 'B') me = 'Z';
			if (opponent == 'C') me = 'X';
		}

		if (opponent == 'A' && me == 'X') {
			score += 3;
			score += 1;
		} else if (opponent == 'A' && me == 'Y') {
			score += 2;
			score += 6;
		} else if (opponent == 'A' && me == 'Z') {
			score += 3;
			score += 0;
		} else if (opponent == 'B' && me == 'X') {
			score += 1;
		} else if (opponent == 'B' && me == 'Y') {
			score += 2;
			score += 3;
		} else if (opponent == 'B' && me == 'Z') {
			score += 3;
			score += 6;
		} else if (opponent == 'C' && me == 'X') {
			score += 1;
			score += 6;
		} else if (opponent == 'C' && me == 'Y') {
			score += 2;
		} else if (opponent == 'C' && me == 'Z') {
			score += 3;
			score += 3;
		}
	}

	cout << score << endl;

  return 0;
}
