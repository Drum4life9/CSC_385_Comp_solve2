#include <iostream>
#include <vector>
#include <map>

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


vector<const vertex* > vertex_stack;
map<int, bool> is_a_safe_vertex;
map<int, bool> has_fully_explored;
map<int, bool> current_path;


void dfs(const vector<vertex>& graph, const vertex& v, int parent_id) {
    //mark current vertex as exploring
    current_path[v.idx] = true;

    for (edge e : v.edges) {
        if (e.dest == parent_id) {
            continue;
        }

        const vertex& new_vert = graph[e.dest];
        if (!current_path[new_vert.idx]) {
            vertex_stack.push_back(&new_vert);
            dfs(graph, new_vert, v.idx);
        }

        // If the vertex we're checking is already safe, then everything currently in the "stack" is safe
        if (is_a_safe_vertex[new_vert.idx]) {
            for (const vertex* now_safe_vertex : vertex_stack) {
                is_a_safe_vertex[now_safe_vertex->idx] = true;
            }
        }
    }
    has_fully_explored[v.idx] = true;
    current_path[v.idx] = false;
    vertex_stack.pop_back();

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

    vertex_stack.push_back(&graph[0]);
    for (int i = 0; i < N; i++) {
        current_path[i] = false;
        is_a_safe_vertex[i] = false;
    }
    is_a_safe_vertex[0] = true;
    has_fully_explored[0] = false;

    dfs(graph, graph[0], 0);

    int count = 0;

    for (const auto& pair : is_a_safe_vertex) {
        if (pair.second) {
            count++;
        }
    }

    cout << count << endl;

    return 0;


}
/*
9 11
0 1
0 2
1 3
2 3
2 8
3 4
4 5
4 6
5 7
6 7
4 1

*/