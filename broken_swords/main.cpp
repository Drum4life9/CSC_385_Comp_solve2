#include <iostream>
#include <vector>

using namespace std;

int main() {
    int num_swords;
    cin >> num_swords;
    vector<string> swords(num_swords);
    for (int i = 0; i < num_swords; i++) {
        cin >> swords[i];
    }

    vector slats = {0, 0, 0, 0};
    for (int i = 0; i < num_swords; i++) {
        if (swords[i][0] == '0') slats[0]++;
        if (swords[i][1] == '0') slats[1]++;
        if (swords[i][2] == '0') slats[2]++;
        if (swords[i][3] == '0') slats[3]++;
    }
    int tops_bots = slats[0] + slats[1];
    int ls_rs = slats[2] + slats[3];

    int tot_tops = tops_bots / 2;
    int tot_lrs = ls_rs / 2;

    int num_makable = min(tot_tops, tot_lrs);
    int leftover_tops = tops_bots - (num_makable * 2);
    int leftover_lrs = ls_rs - (num_makable * 2);
    cout << num_makable << " " << leftover_tops << " " << leftover_lrs << endl;
}