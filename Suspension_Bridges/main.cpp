#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

int main() {
    int d, s;
    cin >> d >> s;

    // a + s = a * cosh(d/2*a)
    // l(a,d) = 2a * sinh(d/2*a)

    double lower_bound = 0;
    double upper_bound = 100000000;

    while (true) {
        double a = ((upper_bound - lower_bound) / 2) + lower_bound;
        double x = d / (2 * a);
        double rside = a * ((exp(x) + exp(-1 * x)) / 2 ) - a;
        // increasing a decreases cosh

        //check diff in rside and lside
        //todo adjust this number
        if (abs(rside - s) < .00001) {
            double len = 2 * a * sinh(d / (2 * a));
            cout << std::fixed << setprecision(9) << len << endl;

            return 0;
        }

        if (s - rside < 0) {
            lower_bound = a;
        }
        else {
            upper_bound = a;
        }
    }

}