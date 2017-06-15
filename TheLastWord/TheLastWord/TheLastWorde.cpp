#include <iostream>
#include <vector>
#include <string>

/*
to see the description of this problem, go to:
https://code.google.com/codejam/contest/4304486/dashboard
*/


int main() {
	//get # of inputs
	int t = 0;
	std::cout << "number of test cases: ";
	std::cin >> t;
	//create vector of user input size
	std::vector<std::string> input;
	std::string temp_string;
	//gather input for each number to count
	for (int i = 0; i < t; i++) {
		std::cout << "test case " << i << ": ";
		std::cin >> temp_string;
		input.push_back(temp_string);
	}
	//loop through all inputs
	for (int i = 0; i < t; i++) {
		//create a string that will be our output and a string that is always the first character in said string
		std::string last_string;
		std::string first;
		//loop through every character in the input string
		for (int j = 0; j < input.at(i).length(); j++) {
			//if it is the first character, add it to last_string
			if (j == 0) {
				last_string += input.at(i).at(j);
				first = last_string.at(0);
			}
			else {
				//get the current indexed character in the string
				std::string current;
				current += input.at(i).at(j);
				//if the current character is later alphabetically than the first character in last_string, add the current string to the front of last_string
				if (first.compare(current) <= 0) {
					last_string = current + last_string;
					first = last_string.at(0);
				}
				//otherwise add it to the end of last_string
				else {
					last_string += current;
				}
			}

		}
		//print your output
		std::cout << last_string << std::endl;
	}
	std::cin >> t;
	return 0;
}