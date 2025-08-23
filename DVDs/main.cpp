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

int doDVDMoveFunction(vector<int> v) {
	int numMoves = 0;
	while (true) {
		int curNumber = v[v.size() - 1];
		for (int i = v.size() - 1; i >= 0; i--) {
			if (v[i] == curNumber + 1) {
				numMoves++;
				curNumber = v[i];
				if (curNumber == v.size()) {
					return numMoves;
				}
			}
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
		cout << doDVDMoveFunction(nums) << endl;
	}
};

