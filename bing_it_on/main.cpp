#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;
struct edge {
    int src;
    int dest;
    bool reverse;

    edge(int s, int d, bool r);
};

struct vertex {
    int idx;
    string val;
    int count;
    std::vector<edge> edges;

    explicit vertex(int idx = -1, string val = "", int count = 0);
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

edge::edge(const int s, const int d, const bool r)
        : src{s}, dest{d}, reverse{r}
{}

vertex::vertex(const int idx, string val, const int count)
        : idx{idx}, val(std::move(val)), count(count)
{}

int main() {
    int num = 0;
    cin >> num;
    vector<vertex*> tree_heads;

    Graph graphy(num);

    vector<vertex> graph = graphy.graph;

    string blank = "";
    getline(cin, blank);

    string word;
    for (int n = 0; n < num; n++) {
        getline(cin, word);
        bool added_to_head_node = false;
        bool added_inside_tree = false;
        vertex& curnode = graph[n];
        curnode.val = word;
        curnode.count = 1;
        vector<int> added_to;
        for (int i = 0; i < tree_heads.size(); ++i) {
            if (added_inside_tree) {
                break;
            }
            if (n == tree_heads[i]->idx) {continue;}
            int lenWord = word.size();
            //assuming there are trees in here
            //if current searching word is a substring of a word on a root node
            if (tree_heads[i]->val.substr(0, lenWord) == word) {
                //add it as a link
                curnode.edges.emplace_back(n, tree_heads[i]->idx, false);
                //we've added a node, yay!
                added_to_head_node = true;
                added_to.emplace_back(i);
                curnode.count += tree_heads[i]->count;
            }

            int lenTreeWord = tree_heads[i]->val.length();
            if (word.substr(0, lenTreeWord) == tree_heads[i]->val) {
                bool is_same_node = false;
                added_inside_tree = true;
                //ok, now we're inside a tree. This needs to be put in the middle of it somewhere
                // lets check each of the sub nodes "recursively" to figure out where to put it.
                vertex* parentNode = tree_heads[i];
                vertex* added_to_node = nullptr;
                while (added_to_node == nullptr) {
                    for (int subNodeI = 0; subNodeI < parentNode->edges.size(); ++subNodeI) {
                        vertex& checkingNode = graph[parentNode->edges[subNodeI].dest];
                        int lenCheckingWord = checkingNode.val.length();
                        if (checkingNode.val == word) {
                            added_to_node = &checkingNode;
                            curnode = checkingNode;
                            is_same_node = true;
                            break;
                        }
                        if (checkingNode.val == word.substr(0, lenCheckingWord)) {
                            parentNode = &checkingNode;
                            break;
                        }
                    }
                    if (!is_same_node) {
                        added_to_node = parentNode;
                    }
                }


                if (!is_same_node) {
                    for (int edgeIndex = added_to_node->edges.size() - 1; edgeIndex >= 0; --edgeIndex) {
                        curnode.edges.emplace_back(n, added_to_node->edges[edgeIndex].dest, false);
                        graph[added_to_node->edges[edgeIndex].dest].edges.emplace_back(added_to_node->edges[edgeIndex].dest, n, true);
                        parentNode->edges.erase(parentNode->edges.begin() + edgeIndex);
                    }

                    added_to_node->edges.emplace_back(added_to_node->idx, n, false);
                    curnode.edges.emplace_back(n, added_to_node->idx, true);
                }


                bool hasParentNode = true;

                parentNode = &curnode;
                while (hasParentNode) {
                    hasParentNode = false;
                    parentNode->count++;
                    for (int parentEdgeIndex = 0; parentEdgeIndex < parentNode->edges.size(); ++parentEdgeIndex) {
                        if (parentNode->edges[parentEdgeIndex].reverse) {
                            parentNode = &graph[parentNode->edges[parentEdgeIndex].dest];
                            hasParentNode = true;
                            break;
                        }
                    }
                }
            }
        }
        if (added_to_head_node) {
            for (int i = added_to.size() - 1; i >= 0; i--) {
                tree_heads.erase(tree_heads.begin() + added_to[i]);
            }
            tree_heads.emplace_back(&curnode);

        }
        else if (!added_inside_tree) {
            tree_heads.emplace_back(&curnode);
            cout << 0 << endl;
            continue;
        }
        cout << curnode.count - 1 << endl;


    }

}