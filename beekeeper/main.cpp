#include <iostream>
#include <string>
#include <vector>

using namespace std;

string doOneExample(const vector<string>& words) {
    vector vowels = {'a', 'e', 'i', 'o', 'u', 'y'};
    int most_doubles = -1;
    int number_of_doubles = -1;
    for (int i = 0; i < words.size(); i++) {
        string wordi = words[i];
        int curDoubles = 0;
        for (int c = 0; c < wordi.size() - 1; c++) {
            if (wordi[c] == wordi[c + 1] && (wordi[c] == 'a' || wordi[c] == 'e' || wordi[c] == 'i' || wordi[c] == 'o' || wordi[c] == 'u' || wordi[c] == 'y')) {
                curDoubles++;
                c++;
            }
        }
        if (curDoubles > number_of_doubles) {
            number_of_doubles = curDoubles;
            most_doubles = i;
        }
    }
    return words[most_doubles];
}

int main() {
    int inp = -1;
    cin >> inp;
    vector<vector<string>> wordsMap;
    while (inp != 0) {
        vector<string> words;
        string word;
        getline(cin, word);
        for (int i = 0; i < inp; i++) {
            getline(cin, word);
            words.push_back(word);
        }
        wordsMap.push_back(words);
        cin >> inp;
    }

    for (int i = 0; i < wordsMap.size(); i++) {
        string res = doOneExample(wordsMap[i]);
        cout << res << endl;
    }

}
