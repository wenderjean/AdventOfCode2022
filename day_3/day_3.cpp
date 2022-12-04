#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> read_file_and_parse_to_vector() {
  string line;
  ifstream myfile ("day_3_input.txt");
  
  vector<string> values;

  if (myfile.is_open()) {
    while( getline (myfile, line) ) {
			values.push_back(line);
    }

    myfile.close();
  }

	return values;
}

vector<char> find_duplications_in_compartments(vector<string> values) {
  vector<char> col;

	for (string items : values) {
		int delimiter = items.length() / 2;

		string compartment_1;
		string compartment_2;

		for (int i = 0; i < delimiter; i++) {
			compartment_1 += items[i];
			compartment_2 += items[i + delimiter];
		}
    
		char duplicated = '\0';
		for (char c : compartment_1) {
			if (c == duplicated) {
        continue;
      }

      for (char d : compartment_2) {
        if (c == d) {
					col.push_back(c);
					duplicated = c;
					break;
				}
			}
		}
	}

  return col;
}

vector<vector<string>> group_in_groups_of_three(vector<string> values) {
  vector<vector<string>> col;
  vector<string> subcol;

  int control = 1;
  for (string item : values) {
    subcol.push_back(item);
    control += 1;

    if (control > 3) {
      control = 1;
      col.push_back(subcol);
      subcol.clear();
    }
  }

  return col;
}

int find_intersection_between_groups(vector<vector<string>> col) {
  vector<int> repeated_items;

  for (vector<string> groups : col) {
    vector<int> col1;
    vector<int> col2;
    vector<int> col3;

    for (char c : groups[0]) {
      int asciin = int(c); 

      if (asciin >= 97 && asciin <= 122) {
        col1.push_back(int(c - 96));
      } else if (asciin >= 65 && asciin <= 90) {
        col1.push_back(int(c - 38));
      }
    }

    for (char c : groups[1]) {
      int asciin = int(c); 

      if (asciin >= 97 && asciin <= 122) {
        col2.push_back(int(c - 96));
      } else if (asciin >= 65 && asciin <= 90) {
        col2.push_back(int(c - 38));
      }
    }

    for (char c : groups[2]) {
      int asciin = int(c); 

      if (asciin >= 97 && asciin <= 122) {
        col3.push_back(int(c - 96));
      } else if (asciin >= 65 && asciin <= 90) {
        col3.push_back(int(c - 38));
      }
    }

    sort(col1.begin(), col1.end());
    sort(col2.begin(), col2.end());
    sort(col3.begin(), col3.end());

    vector<int> intersection_between_first_and_second;
    vector<int> intersection_between_second_and_third;

    set_intersection(col1.begin(), col1.end(),
                     col2.begin(), col2.end(),
                     std::back_inserter(intersection_between_first_and_second));

    set_intersection(intersection_between_first_and_second.begin(), intersection_between_first_and_second.end(),
                     col3.begin(), col3.end(),
                     std::back_inserter(intersection_between_second_and_third));

    vector<int> intersection_between_results;

    set_intersection(intersection_between_first_and_second.begin(), intersection_between_first_and_second.end(),
                     intersection_between_second_and_third.begin(), intersection_between_second_and_third.end(),
                     std::back_inserter(intersection_between_results));

    repeated_items.push_back(intersection_between_results.at(0));
  }

  int total = 0;
  for (int i : repeated_items)
    total += i;

  return total;
}

// @todo construct array of bytes from scratch
int main() {
	vector<string> values = read_file_and_parse_to_vector();

	int sum_of_misplaced_items = 0;
	for (char c : find_duplications_in_compartments(values)) {
		int asciin = int(c); 

		if (asciin >= 97 && asciin <= 122) {
			sum_of_misplaced_items += asciin - 96;
		} else if (asciin >= 65 && asciin <= 90) {
			sum_of_misplaced_items += asciin - 38;
		}
	}

	cout << "Part One -- " << sum_of_misplaced_items << endl;

  int sum_of_badges_present_on_compartments = find_intersection_between_groups(
    group_in_groups_of_three(values)
  );

  cout << "Part Two -- " << sum_of_badges_present_on_compartments << endl;

  return 0;
}
