#include <iostream>
#include <cmath>

using namespace std;

int main() {
    unsigned int inp = 0;
    cin >> inp;

    for (int j = 0; j <= 100000; j++) {
        int mi = 0;
        if (j*j > 200000) {
            mi = max(int(sqrt(j*j - 200000)) - 1, 0);
             // if (j * j - ((j-1) * (j-1)) > inp) break;
        }
        for (int i = mi; i <= j + 10; i++) {
            unsigned int res = (j * j) - (i * i);

            if (res < inp) break;

            if (res == inp) {
                cout << i << ' ' << j << endl;
                return 0;
            }
        }
    }
    cout << "impossible" << endl;

}