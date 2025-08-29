#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main() {
    int t1_height, t2_height = 0;
    vector<int> boxes(6);

    for (int i = 0; i < 6; i++) {
        cin >> boxes[i];
    }
    cin >> t1_height;
    cin >> t2_height;

    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 5; j++) {
            for (int k = 2; k < 6; k++) {
                int sum = boxes[i] + boxes[j] + boxes[k];
                if (sum == t1_height || sum == t2_height) {
                    int sum2 = 0;
                    vector others = {-1, -1, -1};
                    vector boxesUsing = {boxes[i], boxes[j], boxes[k]};
                    int innerIndex = 0;
                    for (int inner = 0; inner < 6; inner++) {
                        if (inner != i && inner != j && inner != k) {
                            sum2 += boxes[inner];
                            others[innerIndex] = boxes[inner];
                            innerIndex++;
                        }
                    }
                    std::sort(others.begin(), others.end(), std::greater<int>());
                    std::sort(boxesUsing.begin(), boxesUsing.end(), std::greater<int>());
                    if ((sum == t1_height && sum2 == t2_height) || (sum == t2_height && sum2 == t1_height)) {
                        if (sum == t1_height) {
                            cout << boxesUsing[0] << " " << boxesUsing[1] << " " << boxesUsing[2] << " " << others[0] << " " << others[1] << " " << others[2] << endl;
                            return 0;
                        }
                        cout << others[0] << " " << others[1] << " " << others[2] << " " << boxesUsing[0] << " " << boxesUsing[1] << " " << boxesUsing[2] << " " << endl;

                        return 0;
                    }
                }
            }
        }
    }
}
//12 8 2 4 10 3 14 25
