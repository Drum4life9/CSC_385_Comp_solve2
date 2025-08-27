#include <iostream>
#include <vector>
#include <string>

using namespace std;

int doDVDMoveFunction(int n, vector<int> v) {
    int last_num_in_order = 0;
	for (int i : v) {
		if (i == last_num_in_order + 1) {
			last_num_in_order = i;
		}
	}

	return n - last_num_in_order;
}

int main() {
	int numCases = 0;
	cin >> numCases;
	for (int i = 0; i < numCases; i++) {
		int numMoves = 0;
		cin >> numMoves;
		vector<int> nums(numMoves);

		for (int j = 0; j < numMoves; j++) {
			cin >> nums[j];
		}
		cout << doDVDMoveFunction(numMoves, nums) << endl;
	}
};

// 2
// 4
// 1 3 2 4
// 5
// 5 1 2 4 3
// 2
// 4
// 4 3 2 1
// 5
// 5 1 2 4 3
