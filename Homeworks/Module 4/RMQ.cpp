#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int INF = 1000000000;
vector<vector<pair<int, int>>> ST;

void rmq(int l, int r) {
    int k = log2(r - l + 1);
    int f = r - pow(2, k) + 1;
    if(min(ST[k][l].first, ST[k][f].first) != min(max(ST[k][l].first, ST[k][f].first), min(ST[k][l].second, ST[k][f].second))) {
        cout << min(max(ST[k][l].first, ST[k][f].first),
                    min(ST[k][l].second, ST[k][f].second)) << endl;
    } else {
        if(ST[k][l].first == ST[k][f].first) {
            if(min(ST[k][l].second, ST[k][f].second) != ST[k][l].first) {
                cout << min(ST[k][l].second, ST[k][f].second) << endl;
            } else {
                cout << max(ST[k][l].second, ST[k][f].second) << endl;
            }
        } else {
            cout << min(max(ST[k][l].first, ST[k][f].first),
                        max(ST[k][l].second, ST[k][f].second)) << endl;
        }
    }
}

void makeSparseTable(int n) {
    for(int k = 1; k <= n - log2(n); k++) {
        for(int i = 0; i < ST[k - 1].size() - pow(2, k - 1); i++) {
            ST[k].push_back(make_pair(min(ST[k - 1][i].first, ST[k - 1][i + pow(2, k - 1)].first), min(max(ST[k - 1][i].first, ST[k - 1][i + pow(2, k - 1)].first), min(ST[k - 1][i].second, ST[k - 1][i + pow(2, k - 1)].second))));
        }
    }
}

int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    ST.resize(n);
    for(int i = 0; i < n; i++) {
        int a = 0;
        cin >> a;
        ST[0].push_back(make_pair(a, INF));
    }
    makeSparseTable(n);
    for(int i = 0; i < m; i++) {
        int l = 0, r = 0;
        cin >> l >> r;
        rmq(l - 1, r - 1);
    }
}

