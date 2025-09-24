#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct edge {
    int src;
    int dest;
    double w;

    edge(int s, int d, double w);
};

struct vertex {
    int idx;
    pair<int, int> loc;
    std::vector<edge> edges;

    explicit vertex(int idx = -1, pair<int, int> loc = {0, 0});
};

class Graph {



public:
    explicit Graph(int sz, bool is_directed = true);

    void add_edge(int src, int dest, double weight = 1.0);

    [[nodiscard]] pair<vector<std::pair<double, int>>, vector<int>> dijkstra(int n) const;

    std::vector<vertex> graph;
    bool directed;
};

#include <iostream>
#include <queue>

using namespace std;

Graph::Graph(int sz, bool is_directed)
        : graph(sz), directed(is_directed)
{
    for (int i = 0; i < graph.size(); ++i) {
        graph[i].idx = i;
    }
}

void Graph::add_edge(int src, int dest, double weight)
{
    graph[src].edges.emplace_back(src, dest, weight);
    if (!directed) {
        graph[dest].edges.emplace_back(dest, src, weight);
    }
}


pair<vector<pair<double, int>>, vector<int>> Graph::dijkstra(int n) const {
    vector<pair<double, int>> ret(graph.size(), make_pair(-1, -1));
    auto cmp = [&](const vertex* v1, const vertex* v2){return ret[v1->idx].first > ret[v2->idx].first;};
    priority_queue<const vertex*, vector<const vertex*>, decltype(cmp)> q(cmp);
    vector<int> prev(graph.size(), -1);
    vector<bool> known(graph.size(), false);

    ret[n].first = 0;
    ret[n].second = n;
    q.push(&graph[n]);

    while (!q.empty()) {
        const vertex* v = q.top();
        q.pop();
        if (known[v->idx]) continue;
        known[v->idx] = true;

        for (auto e : v->edges) {
            const vertex* dest = &graph[e.dest];
                if (!known[dest->idx]) {
                    double new_dist = ret[v->idx].first + e.w;

                    if (ret[dest->idx].first == -1 || new_dist < ret[dest->idx].first) {
                        ret[dest->idx].first = new_dist;
                        ret[dest->idx].second = v->idx;
                        prev[dest->idx] = v->idx;
                        q.push(dest);

                    }
                }
        }
    }


    return make_pair(ret, prev);
}

edge::edge(int s, int d, double w)
        : src{s}, dest{d}, w{w}
{}

vertex::vertex(int idx, pair<int, int> loc)
        : idx{idx}, loc{std::move(loc)}
{}

int main() {
    int num_safe;
    cin >> num_safe;
    Graph g(num_safe + 2, false);


    for (int i = 0; i < num_safe; ++i) {
        int x, y;
        cin >> x >> y;
        g.graph[i].loc = make_pair(x, y);
    }
    for (int i = 0; i < 2; ++i) {
        int x, y;
        cin >> x >> y;
        g.graph[g.graph.size() - 2 + i].loc = make_pair(x, y);
    }

    for (int i = 0; i < g.graph.size(); ++i) {
        for (int j = i + 1; j < g.graph.size(); ++j) {
            double dist = pow(g.graph[i].loc.first - g.graph[j].loc.first, 2) +
                               pow(g.graph[i].loc.second - g.graph[j].loc.second, 2);
            g.add_edge(i, j, dist);
        }
    }

    auto ret = g.dijkstra(g.graph.size() - 2);

    auto prevs = ret.second;

    int prev = prevs[ret.first.size() - 1];

    vector<int> path;
    while (prev != -1) {
        path.push_back(g.graph[prev].idx);
        prev = prevs[prev];
    }

    vector<int> path2;

    for (int i = 0; i < path.size() - 1; ++i) {
        path2.push_back(path[i]);
    }

    reverse(path2.begin(), path2.end());

    for (int i = 0; i < path2.size(); ++i) {
        cout << path2[i] << endl;
    }

    if (path2.empty()) {
        cout << "-"  << endl;
    }

}

