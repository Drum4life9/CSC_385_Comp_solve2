#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;
struct edge {
    int src;
    int dest;

    edge(int s, int d);
};

struct vertex {
    int idx;
    char val;
    int count;
    std::vector<edge> edges;

    explicit vertex(int idx = -1, char val = ' ', int count = 0);
};
class Graph {


public:
    explicit Graph(int sz);

    std::vector<vertex> graph;
};

Graph::Graph(int sz)
        : graph(sz) {
    for (int i = 0; i < graph.size(); ++i) {
        graph[i].idx = i;
    }
}

edge::edge(const int s, const int d)
        : src{s}, dest{d}
{}

vertex::vertex(const int idx, char val, const int count)
        : idx{idx}, val(std::move(val)), count(count)
{}

int main() {
    int num = 0;
    cin >> num;

    vector<vertex> graph;
    graph.reserve(3200000);
    graph.emplace_back(0, ' ', 0);

    string blank = "";
    getline(cin, blank);

    string word;
    for (int n = 0; n < num; n++) {
        getline(cin, word);

        vertex* curVertex;

        for (int i = 0; i < graph.size(); ++i) {
            if (graph[i].idx == 0) {
                curVertex = &graph[i];
                curVertex->count++;
            }
        }

        int i = 0;
        while (i < word.size()) {
            //get char
            char c = word[i];
            //loop through edges in curvertex
            bool added_to_a_vertex = false;
            for (edge& e : curVertex->edges) {
                //if we can move on to a new vertex in the graph
                if (graph[e.dest].val == c) {
                    //update current vertex to add a new character
                    i++;
                    curVertex = &graph[e.dest];
                    curVertex->count++;
                    added_to_a_vertex = true;
                    break;
                }
            }
            if (!added_to_a_vertex) {
                graph.push_back(vertex(graph.size(), c, 1));
                curVertex->edges.emplace_back(curVertex->idx, graph.size() - 1);
                curVertex = &graph[graph.size() - 1];
                i++;
            }


            if (i == word.size()) {
                cout << curVertex->count - 1 << endl;
            }
        }
    }
}