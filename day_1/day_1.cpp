#include <iostream>
#include <fstream>
#include <string>
#include <vector>   

using namespace std;

vector<int> read_file_and_cast_values_to_int() {
  string line;
  ifstream myfile ("day_1_input.txt");
  
  vector<int> numbers;

  if (myfile.is_open()) {
    while( getline (myfile, line) ) {
      int num;

      if (line.empty()) {
        num = -1;
      } else {
        num = stoi(line);
      }

      numbers.push_back(num);
    }

		numbers.push_back(-1);

    myfile.close();
  }

	return numbers;
}

vector<int> group_calories_amounts_per_elf() {
	vector<int> calories = read_file_and_cast_values_to_int();

  int amount_of_calories_per_elf;
  int switch_elf = 0;

  vector<int> collection_of_elfs_calories;

  for (int i : calories) {
    if (switch_elf == 1) {
      switch_elf = 0;
    }

    if (i == -1) {
      collection_of_elfs_calories.push_back(amount_of_calories_per_elf);

      amount_of_calories_per_elf = 0;
      switch_elf = 1;
    } else {
      amount_of_calories_per_elf = amount_of_calories_per_elf + i;

      switch_elf = 0;
    }
  }

	return collection_of_elfs_calories;
}

vector<int> sort(vector<int> col) {
  for (int i = 0; i < col.size(); i++) {
		for (int j = i + 1; j < col.size(); j++) {
			if (col.at(i) > col.at(j)) {
				int r = col.at(i);

        col.at(i) = col.at(j);
        col.at(j) = r;
			}
		}
  }

	return col;
}

int main() {
	vector<int> collection_of_elfs_calories = sort(group_calories_amounts_per_elf());
	
	int top_1 = collection_of_elfs_calories.at(collection_of_elfs_calories.size() - 1);
	int top_2 = collection_of_elfs_calories.at(collection_of_elfs_calories.size() - 2);
	int top_3 = collection_of_elfs_calories.at(collection_of_elfs_calories.size() - 3);

  cout << "ELF Carrying the most calories carries exactly: " << top_1 << "\n";
	cout << "Let's find top 3..." << "\n";

  cout << "Top 1: " << top_1 << "\n";
  cout << "Top 2: " << top_2 << "\n";
  cout << "Top 3: " << top_3 << "\n";

	cout << "Total amount: " << top_1 + top_2 + top_3;

  return 0;
}
