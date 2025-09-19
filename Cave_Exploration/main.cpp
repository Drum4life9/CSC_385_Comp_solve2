#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Edge {
    int to, idx;
};

vector<vector<Edge>> adj;
vector<int> tin, low;
set<int> bridges;
int timer = 0;

void dfs_bridges(int v, int p, vector<bool>& visited) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (auto& e : adj[v]) {
        int to = e.to;
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs_bridges(to, v, visited);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                bridges.insert(e.idx);
            }
        }
    }
}

void dfs_component(int v, vector<bool>& visited, const vector<pair<int,int>>& edges) {
    visited[v] = true;
    for (auto& e : adj[v]) {
        if (bridges.count(e.idx)) continue;
        if (!visited[e.to]) dfs_component(e.to, visited, edges);
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    adj.resize(N);
    vector<pair<int,int>> edges;
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        edges.push_back({u, v});
    }

    tin.assign(N, -1);
    low.assign(N, -1);
    vector<bool> visited(N, false);
    dfs_bridges(0, -1, visited);

    visited.assign(N, false);
    dfs_component(0, visited, edges);

    int count = 0;
    for (int i = 0; i < N; ++i) {
        if (visited[i]) count++;
    }
    cout << count << endl;
}
