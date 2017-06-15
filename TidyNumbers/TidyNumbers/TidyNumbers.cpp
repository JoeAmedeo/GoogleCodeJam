#include <iostream>
#include <vector>
#include <string>

/*
	see the problem description at:
	https://code.google.com/codejam/contest/3264486/dashboard#s=p1&a=0
*/

/*
	My way of solving this problem involves a greedy algorithm.
	I converted the input into an array, each index representing a digit in the number.
	What we can do from here is look at the array of numbers from left to right
	We have 3 cases for comparing each digit.
	case 1: N < N+1
	here we just move the index forward, since it still fits the criteria of being tidy
	case 2: N > N+1
	in this case, the number is no longer tidy.
	in most cases, you will get the next greatest tidy number by subtracting the value of N by 1 then changing all values from N+1 to the last index to 9.
	This will only fail in the equals case, which will be explained shortly.
	case 3: N == N+1
	this case requires some keeping track of. 
	a number is still tidy if neighboring digits are equal.
	The issue comes about when you have a series of equal digits followed by a lesser valued digit.
	This makes it so the normal case 2 fails.
	for example, take 2224442.
	we would go left to right, and at the last two indexes, you would see that 4 > 2 and would do the usual subtract by 1, change all to the right to 9.
	this will return 2224439, which is obviously wrong.
	my solution to this issue is to keep two indexes, the one for the current comparison, and one that keeps track of the start of values that are equal.
	this can be shown again with the number 2224442.
	we would start at index 0, and we see that index 0 through 2 have the same value, so for the first through third comparison, we would maintain the index 0 incase case two comes about.
	when comparing indeces 2 and 3, we see 2 < 4 and we can change this change index to 3.
	the same process occurs between indeces 3 and 5, except when comparing 5 and 6, you see 4 > 2.
	here we kept track of the earliest 4, and will subtract that 4 by 1 and change all to the right of it to 9.
	this will give us 2223999, which is the greatest tidy number less than 2224442.

*/

int main() {
	//a bunch of stuff to get input
	int t;
	std::cout << "Number of test cases: ";
	std::cin >> t;

	std::vector<int> input;

	for (int i = 0; i < t; i++) {
		int temp;
		std::cout << "Case " << i + 1 << " : ";
		std::cin >> temp;
		input.push_back(temp);
	}

	//itterate over all inputs
	for (int i = 0; i < t; i++) {
		//get current input value into int variable
		int current_num = input.at(i);
		//convert to string for length determining purposes
		std::string string_num = std::to_string(current_num);
		//convert current_num into an array, with each index representing a digits in the number
		std::vector<int> split_input(string_num.length());
		for (int j = (string_num.length()-1); j >= 0; j--) {
			split_input.at(j) = current_num % 10;
			current_num /= 10;
		}
		//set the change index and start traversing the digits
		int change_index = 0;
		for (int j = 0; j < (string_num.length() - 1); j++) {
			//case 1: N < N+1, change the change index and continue forward
			if (split_input.at(j) < split_input.at(j + 1)) {
				change_index = j + 1;
			}
			//case 2: N > N+1, subtract value at change index by one, change everything after it to 9
			else if (split_input.at(j) > split_input.at(j + 1)) {
				split_input.at(change_index) -= 1;
				change_index++;
				for (change_index; change_index < string_num.length(); change_index++) {
					split_input.at(change_index) = 9;
				}
				break;
			}
			//case 3: N == N+1, dont change the change index, move forward.
			else {

			}
		
		}
		//convert array back into int
		current_num = 0;
		for (int j = 0; j < string_num.length(); j++) {
			current_num += split_input.at(j);
			current_num *= 10;
		}
		current_num /= 10;
		//print out the result
		std::cout << current_num << std::endl;
	}

	std::cin >> t;
	return 0;
}