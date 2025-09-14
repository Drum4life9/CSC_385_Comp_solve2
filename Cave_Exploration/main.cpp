#include <iostream>
#include <vector>

using namespace std;

class graph_exception: public std::exception {};

struct edge {
    int src;
    int dest;
    double w;

    edge(int s, int d, double w);
};
struct vertex {
    int idx;
    std::vector<edge> edges;

    explicit vertex(int idx = -1);
};

class Graph {

public:
    explicit Graph(int sz, bool is_directed = true);

    void add_edge(int src, int dest, double weight = 1.0);

    std::vector<vertex> graph;
    bool directed;
};

edge::edge(int s, int d, double w)
        : src{s}, dest{d}, w{w}
{}

vertex::vertex(int idx)
        : idx{idx}
{}


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


vector<int> par;
vector<bool> visited;
vector<bool> curWorkingCycle;
vector<int> cycleNodesContaining0;

void dfs(int v, vector<vertex>& graph) {
    visited[v] = true;

    for (const edge e : graph[v].edges){
        par[e.dest] = v;
        if (!visited[e.dest])
            dfs(e.dest, graph);
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    Graph graphy(N, false);
    for (int i = 0; i < M; ++i) {
        int s, d;
        cin >> s >> d;
        graphy.add_edge(s, d, 1);
    }

    vector<vertex> graph = graphy.graph;
    par = vector(graph.size(), -1);
    visited = vector(graph.size(), false);

    dfs(0, graph);

    return 0;


}