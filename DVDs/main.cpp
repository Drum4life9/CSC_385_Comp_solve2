#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool checkVectorSorted(const vector<int>& nums) {
	if (nums.size() == 1) {
		return true;
	}

	for (int i = 0; i < nums.size() - 1; i++) {
		if (nums[i] + 1 != nums[i + 1]) {
			return false;
		}
	}
	return true;
}

int doDVDMoveFunction(int n, vector<int> v) {
	int numMoves = 0;
	int startIndexFromEnd = 0;
	while (true) {
		int lastNumMoves = 0;
		int curNumber = v[v.size() - 1 - startIndexFromEnd];
		for (int i = v.size() - 1; i >= 0; i--) {
			if (v[i] == curNumber + 1) {
				numMoves++;
				lastNumMoves++;
				curNumber = v[i];
				auto it = v.begin() + i;
				v.erase(it);
				startIndexFromEnd = 0;
				if (curNumber == n) {
					return numMoves;
				}
			}
		}
		if (lastNumMoves == 0) {
			startIndexFromEnd++;
		}
		if (startIndexFromEnd == v.size()) {
			return numMoves;
		}
	}
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
