#include <iostream>
#include <vector>

using namespace std;

int main() {
    int inp = 0;
    cin >> inp;

    vector<pair<int, int>> options;

    for (int b = 1; b <= 2000000; b++) {
        for (int a = 1; a <= b; a++) {
            if (a * b > inp) {
                break;
            }
            if (a * b == inp) {
                int j = (a+b)/2;
                int i = (b-a)/2;
                if (j * j - i * i == inp) {
                    options.emplace_back(i, j);
                    cout << i << " " << j << endl;
                    return 0;
                }
            }
        }
    }

    // if (options.size() > 0) {
    //     int index_least = -1;
    //     int least_i = 1000000000;
    //     for (int i = 0; i < options.size(); i++) {
    //         if (options[i].first < least_i) {
    //             index_least = i;
    //             least_i = options[i].first;
    //         }
    //     }
    //
    //     cout << options[index_least].first << " " << options[index_least].second << endl;
    //     return 0;
    // }

    cout << "impossible" << endl;

}