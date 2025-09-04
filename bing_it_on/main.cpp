#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int num = 0;
    cin >> num;
    vector<string> words(num);

    string blank = "";
    getline(cin, blank);

    string word;
    for (int i = 0; i < num; i++) {
        getline(cin, word);
        words[i] = word;
    }

    cout << 0 << endl;

    for (int i = 1; i < num; i++) {
        int count = 0;
        string curWord = words[i];
        for (int j = 0; j < i; j++) {
            string sub = words[j].substr(0, curWord.length());
            if (sub == curWord) {
                count++;
            }
        }

        cout << count << endl;
    }
}