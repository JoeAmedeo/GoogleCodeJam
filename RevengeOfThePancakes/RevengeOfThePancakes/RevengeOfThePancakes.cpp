#include <iostream>
#include <vector>
#include <string>

/*
  to see this problem, head to:
  https://code.google.com/codejam/contest/6254486/dashboard#s=p1
*/

/*
  This problem can be solved inductively.
  We can use a base case of a single pancake.
  In this case, either the pancake is + or -
  If it is +, leave it, if it is -, flip it.
  Now for the inductive case.
  In this case, we can assume that all pancakes on top of this one are right side up
  Since you will be solving top to bottom.
  Now we can look at the Nth pancake in two cases, + and -
  if +, then leave it alone like the base case
  if -, then a little bit of extra work compared to the base case.
  first, you flip pancakes 1 ... N-1.
  Now pancakes 1 ... N will be -.
  finally, flip pancakes 1...N and they will all be +.
  repeat for the entire batch of pancakes then you win!

  for this problem, we can luckily skip some flips to make it run faster
  in any case where you want to flip a -, you can check how many -'s are after the current one and flip them all at the same time!

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
	
	for (int i = 0; i < input.size(); i++) {
		int flip_count = 0;
		std::string current = input.at(i);
		for (int j = 0; j < current.length(); j++) {
			if (j == 0) {
				if (current.at(0) == '-') {
					flip_count++;
				}
			}
			else {
				if (current.at(j) == '-') {
					flip_count += 2;

					while (j < (current.length() - 1) && current.at(j + 1) == '-') {
						j++;
					}
				}
			}

		}
		std::cout << flip_count << std::endl;
	}

	std::cin >> t;
	return 0;
}