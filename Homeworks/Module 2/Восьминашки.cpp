#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class CClass {
public:
    CClass(vector<int> a) {
        start = a;
    }

    void addToChanges(int nullPos, int a, char c, vector<vector<int>> &nearCurrent, vector<char> &changes, vector<int> current) {
        vector<int> g = current;
        swap(g[nullPos], g[nullPos + a]);
        nearCurrent.push_back(g);
        changes.push_back(c);
    }

    void findStates(vector<int> &current, vector<vector<int>> &nearCurrent, vector<char> &changes) {
        int nullPos = 0;
        for(int i = 0; i < 9; i++) {
            if(current[i] == 0) {
                nullPos = i;
            }
        }
        if(nullPos == 0) {
            addToChanges(nullPos, 1, 'R', nearCurrent, changes, current);
            addToChanges(nullPos, 3, 'D', nearCurrent, changes, current);
        }
        if(nullPos == 1) {
            addToChanges(nullPos, 1, 'R', nearCurrent, changes, current);
            addToChanges(nullPos, 3, 'D', nearCurrent, changes, current);
            addToChanges(nullPos, -1, 'L', nearCurrent, changes, current);
        }
        if(nullPos == 2) {
            addToChanges(nullPos, 3, 'D', nearCurrent, changes, current);
            addToChanges(nullPos, -1, 'L', nearCurrent, changes, current);
        }
        if(nullPos == 3) {
            addToChanges(nullPos, 1, 'R', nearCurrent, changes, current);
            addToChanges(nullPos, 3, 'D', nearCurrent, changes, current);
            addToChanges(nullPos, -3, 'U', nearCurrent, changes, current);
        }if(nullPos == 4) {
            addToChanges(nullPos, 1, 'R', nearCurrent, changes, current);
            addToChanges(nullPos, 3, 'D', nearCurrent, changes, current);
            addToChanges(nullPos, -1, 'L', nearCurrent, changes, current);
            addToChanges(nullPos, -3, 'U', nearCurrent, changes, current);
        }if(nullPos == 5) {
            addToChanges(nullPos, -3, 'U', nearCurrent, changes, current);
            addToChanges(nullPos, 3, 'D', nearCurrent, changes, current);
            addToChanges(nullPos, -1, 'L', nearCurrent, changes, current);
        }if(nullPos == 6) {
            addToChanges(nullPos, 1, 'R', nearCurrent, changes, current);
            addToChanges(nullPos, -3, 'U', nearCurrent, changes, current);
        }if(nullPos == 7) {
            addToChanges(nullPos, 1, 'R', nearCurrent, changes, current);
            addToChanges(nullPos, -3, 'U', nearCurrent, changes, current);
            addToChanges(nullPos, -1, 'L', nearCurrent, changes, current);
        }if(nullPos == 8) {
            addToChanges(nullPos, -3, 'U', nearCurrent, changes, current);
            addToChanges(nullPos, -1, 'L', nearCurrent, changes, current);
        }
    }

    vector<int> getStart() {
        return start;
    }

    map<vector<int>, string> getWay() {
        return way;
    }

private:
    vector<int> start;
    map<vector<int>, string> way;
};


// вынесен БФС за границы класса
void BFS(map<vector<int>, string> way, int start) {
    vector<int> const idol = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    map<vector<int>, bool> used;
    map<vector<int>, int> dist;
    dist[start] = 0;
    way[start] = "";
    queue<vector<int>> q;
    q.push(start);
    used[start] = true;
    while(!q.empty()) {
        vector<int> state = q.front();
        q.pop();
        vector<vector<int>> nearCurrent;
        vector<char> changes;
        if(state == idol) {
            cout << dist[state] << endl;
            cout << way[state] << endl;
            exit(0);
        }
        findStates(state, nearCurrent, changes);
        for(int i = 0; i < nearCurrent.size(); i++) {
            if(used[nearCurrent[i]] != true) {
                used[nearCurrent[i]] = true;
                dist[nearCurrent[i]] = dist[state] + 1;
                way[nearCurrent[i]] = way[state] + changes[i];
                q.push(nearCurrent[i]);
            }
        }
    }
    cout << -1 << endl;
}

int main() {
    vector<int> g;
    for(int i = 0; i < 9; i++) {
        int a;
        cin >> a;
        g.push_back(a);
    }
    CClass result(g);
    BFS(result.getWay(), result.getStart());
}
