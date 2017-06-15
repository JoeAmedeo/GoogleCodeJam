#include <iostream>
#include <string>
#include <vector>


bool allTrue(std::vector<bool> array) {
	int x = 0;
	for (int i = 0; i < array.size(); i++) {
		if (array[i]) {
			x++;
		}
		//std::cout << i << " is " << array[i] << std::endl;
	}
	if (x == array.size()) {
		return true;
	}
	else {
		return false;
	}
}

/*
to see the problem this program is associated with, go to
https://code.google.com/codejam/contest/6254486/dashboard
*/
int main() {
	//get user input for number of cases that will be tested
	int t = 0;
	std::cout << "number of test cases: ";
	std::cin >> t;
	//create vector of user input size
	std::vector<int> input;
	int temp_int;
	//gather input for each number to count
	for (int i = 0; i < t; i++) {
		std::cout << "test case " << i << ": ";
		std::cin >> temp_int;
		input.insert(input.begin()+i, temp_int);
	}
	//iterate over all inputs
	for (int i = 0; i < input.size(); i++) {
		//following the counting method of 1*N, 2*N, 3*N, and so on, x will be our 1,2,3 so on
		int x = 1;
		bool loop = true;
		//create an array of booleans, with their index representing the numbers that have occured in the sequence.
		std::vector<bool> numbers{ false, false, false, false, false, false, false, false, false, false };
		while (loop) {
			
			//set temp as the input value times the x value
			int temp = input[i] * x;
			//convert temp to a string
			std::string s = std::to_string(temp);
			//itterate over every character in the string, and set given values to true.
			//std::cout << "traversing string: " << s << std::endl;
			for (char& c : s) {
				//std::cout << c << std::endl;
				switch (c) {
				case '0': numbers[0] = true;
					break;
				case '1': numbers[1] = true;
					break;
				case '2': numbers[2] = true;
					break;
				case '3': numbers[3] = true;
					break;
				case '4': numbers[4] = true;
					break;
				case '5': numbers[5] = true;
					break;
				case '6': numbers[6] = true;
					break;
				case '7': numbers[7] = true;
					break;
				case '8': numbers[8] = true;
					break;
				case '9': numbers[9] = true;
					break;
				default: break;
				}
			}
			if (allTrue(numbers)) {
				//if every value has been seen, print the current number and break the while loop
				std::cout << "Case " << i << ": " << temp << std::endl;
				loop = false;
			}
			else if (temp == 0) {
				//if the case causes insomnia, print output then break while loop
				std::cout << "Case " << i << ": INSOMNIA" << std::endl;
				loop = false;
			}
			else {
				//itterate x if not insomnia or not all true
				x++;
			}
		}
	}
	std::cin >> t;
	return 0;
}