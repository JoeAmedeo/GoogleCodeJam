#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <math.h>

using namespace std;

struct input_values {
	int stalls;
	int people;
};



class tree {
public:
	int value;
	bool hasChildren;
	tree* left;
	tree* right;

	tree(int v) {
		value = v;
		hasChildren = false;
		left = NULL;
		right = NULL;
	}

	void split() {
		
		left = new tree(floor((value - 1) / 2));
		right = new tree(ceil((value - 1) / 2));
		hasChildren = true;

	}

	int find_max() {
		if (!(hasChildren)) {
			return value;
		}
		else {
			return max(left->find_max(), right->find_max());
		}
	}

	int find_min() {
		if (!(hasChildren)) {
			return value;
		}
		else {
			return min(left->find_max(), right->find_max());
		}
	}


	void insert_people(int x) {

		priority_queue<tree*> q;
		q.push(this);
		while (x > 0) {
			tree* current = q.top();
			q.pop();
			current->split();
			q.push(current->right);
			q.push(current->left);
			x--;
		}
	}

private:
	int min(int x, int y) {
		if (x < y) {
			return x;
		}
		else {
			return y;
		}
	}
	int max(int x, int y) {
		if (x > y) {
			return x;
		}
		else {
			return y;
		}
	}

};



/*
	Originally, I was planning on modeling the problem with an array/list of size N and inserting people in a binary search formations.
	I would do this by looking to see if the middle elementwas empty, if so fill it with a person, if not split the array in half and recursively try and find a middle element that is empty.
	doing this sort of breath first search type insert would model the situation where everyone is as far away as possible.
	

*/

int main() {
	int t;
	cin >> t;
	vector<input_values> input(t);
	//a bunch of code to recieve input, then convert it into the vector of structs created earlier.
	for (int i = 0; i < t; i++) {
		string stalls_string;
		string people_string;
		cin >> stalls_string >> people_string;
		cout << stalls_string << " " << people_string << endl;
		input.at(i).stalls = stoi(stalls_string);
		input.at(i).people = stoi(people_string);
	}

	for (int i = 0; i < t; i++) {
		tree* _tree = new tree(input.at(i).stalls);
		_tree->insert_people(input.at(i).people);
		int max = _tree->find_max();
		int min = _tree->find_min();

		cout << "Case " << i + 1 << ": " << max << " " << min << endl;
		cin >> t;
	}
}
	