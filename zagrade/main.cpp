#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string inp;
    getline(cin, inp);
    vector<string> words;
    vector<int> lefts;

    int right_index = 0;
    vector<std::pair<int, int>> parenthesis_pairs;
    for (int i = 0; i < inp.size(); i++) {
        if (inp[i] == '(') {
            lefts.push_back(i);
        }
        else if (inp[i] == ')') {
            parenthesis_pairs.push_back(std::make_pair(lefts[(lefts.size() - ++right_index)], i));
        }
    }

    cout << parenthesis_pairs.size() << endl;
}