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

            int starting_index = 0;
            int ending_index = m.size() - 1;
            int checking_index = (ending_index - starting_index) / 2;

            pair<int, int>* checking_pair = nullptr;
            while (true) {
                if (m[checking_index].first <= index && m[checking_index].second >= index) {
                    checking_pair = &m[checking_index];
                    break;
                }
                if (starting_index == ending_index) {
                    break;
                }
                checking_pair = &m[checking_index];
                if (checking_pair->first > index) {
                    ending_index = checking_index;
                }
                else if (checking_pair->second < index) {
                    starting_index = checking_index + 1;
                }
                checking_pair = nullptr;
                checking_index = ((ending_index - starting_index) + starting_index) / 2 + 1;

            }

            if (checking_pair == nullptr) {
                //if checking_pair is less than index
                //whenever possible, it's easier to tack the new index onto the end of an existing pair
                if (m[checking_index].second == index - 1) {
                    m[checking_index].second = index;
                    if (checking_index != m.size() - 1 && m[checking_index + 1].first == index + 1) {
                        //combine pairs
                        m[checking_index].second = m[checking_index + 1].second;
                        m.erase(m.begin() + checking_index + 1);
                    }
                }
                else if (m[checking_index].first == index + 1) {
                    m[checking_index].first = index;
                    if (checking_index != 0 && m[checking_index - 1].second == index - 1) {
                        m[checking_index].first = m[checking_index - 1].first;
                        m.erase(m.begin() + checking_index - 1);
                    }
                }
                else {
                    if (index < m[checking_index].first) {
                        m.insert(m.begin() + checking_index, make_pair(index, index));
                    }
                    else {
                        m.insert(m.begin() + checking_index + 1, make_pair(index, index));
                    }
                }


                continue;
            }

            //if it's a single item pair, delete it
            if (checking_pair->first == checking_pair->second) {
                auto it = ranges::find(m, *checking_pair);
                if (it != m.end()) { m.erase(it); }
            }
            else if (checking_pair->first == index) {
                checking_pair->first = index + 1;
            }
            else if (checking_pair->second == index) {
                checking_pair->second = index - 1;
            }
            else {
                //we're in the middle, so we should split
                int temp_end = checking_pair->second;
                checking_pair->second = index - 1;
                m.insert(m.begin() + checking_index + 1, make_pair(index + 1, temp_end));
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
                    end_diff = covered_pairs[covered_pairs.size() - 1]->second - end_index;
                }

                int running_amount = 0;

                for (const pair<int, int>* i : covered_pairs) {
                    running_amount += (i->second - i->first) + 1;
                }
                running_amount -= end_diff;
                running_amount -= start_diff;

                cout << running_amount << endl;
            }
        }
    }
}
/*
8 5
F 3
F 5
F 4
F 4
F 4

*/