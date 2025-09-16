#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, K;

    cin >> N >> K;

    vector<pair<int, int>> m;

    for (int k = 0; k < K; k++) {
        char op;
        cin >> op;
        if (op == 'F') {
            int index;
            cin >> index;
            //todo do flip here

            if (m.empty()) {
                m.emplace_back(index, index);
                continue;
            }

            bool hasFoundPair = false;
            int starting_index = 0;
            int ending_index = m.size();

            pair<int, int>* checking_pair = nullptr;
            while (true) {
                if (starting_index == ending_index) {
                    break;
                }
                int checking_index = (ending_index - starting_index) / 2;
                checking_pair = &m[checking_index];
                if (checking_pair->first <= index && checking_pair->second >= index) {
                    break;
                }
                if (checking_pair->first > index) {
                    ending_index = checking_index + 1;
                }
                else if (checking_pair->second < index) {
                    starting_index = checking_index + 1;
                }
                checking_pair = nullptr;
            }

            if (checking_pair == nullptr) {
                m.emplace_back(index, index);
                continue;
            }

            //if it's a single item pair, delete it
            if (checking_pair->first == checking_pair->second) {
                auto it = ranges::find(m, *checking_pair);
                if (it != m.end()) { m.erase(it); }
            }
            // checking_pair->second = index - 1;


        }
        else {
            int start_index, end_index;
            cin >> start_index >> end_index;

            vector<pair<int, int>*> covered_pairs;
            for (auto& i : m) {
                pair<int, int>* p = &i;
                //pair fully contained in range
                if (p->first >= start_index && p->second <= end_index) {
                    covered_pairs.push_back(p);
                }
                //pair contains left index of search range
                else if (p->first <= start_index && p->second >= start_index) {
                    covered_pairs.push_back(p);
                }
                //pair contains right index of search range
                else if (p->first <= end_index && p->second >= end_index) {
                    covered_pairs.push_back(p);
                }

            }

            if (covered_pairs.empty()) {
                cout << 0 << endl;
            }
            else {
                int start_diff = 0, end_diff = 0;
                if (covered_pairs[0]->first < start_index) {
                    start_diff = covered_pairs[0]->first - start_index;
                }
                if (covered_pairs[covered_pairs.size() - 1]->second > end_index) {
                    end_diff = end_index - covered_pairs[covered_pairs.size() - 1]->second;
                }

                int running_amount = 0;

                for (pair<int, int>* i : covered_pairs) {
                    running_amount += (i->second - i->first) + 1;
                }
                running_amount -= end_diff;
                running_amount -= start_diff;

                cout << running_amount << endl;
            }
        }
    }
}