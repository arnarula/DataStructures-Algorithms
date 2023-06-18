#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

struct edge {
    double weight;
    int from, to;
    edge(int p_from, int p_to, double p_weight) : from(p_from), to(p_to), weight(p_weight) {}
    edge(int p_from, int p_to) : from(p_from), to(p_to), weight(0) {}
};

std::vector<double> dist; // tracks distances from source vertex
std::vector<int> bp; // tracks back pointer for vertices (for path reconstruction)
std::unordered_map<int, std::vector<std::pair<int, double>>> adj_list; // graph adjacency list

// initializes distances and back pointer vectors
void initializeGraph(int src, int n) {
    dist.resize(n, INT_MAX);
    bp.resize(n, -1);
    dist[src] = 0;
}

/* dijkstra's algorithm - time complexity O((E + V) * log V)
//   - calculates shortest path cost distance from source vertex to every other vertex
//   - assumes all edge weights are non-negative and no self-loops
// @params
//   - src: id of source vertex
//   - n: # of vertices
*/
void dijkstras(int src, int n) {
    initializeGraph(src, n);
    // min heap to quickly find next unvisited vertex with lowest path cost from source
    typedef std::pair<int, double> pid;
    std::priority_queue<pid, std::vector<pid>, std::greater<pid>> min_heap;
    // set tracks visited vertices 
    std::unordered_set<int> vis; 
    min_heap.push({0, src});
    while (!min_heap.empty()) {
        auto curr = min_heap.top().second; min_heap.pop();
        if (vis.count(curr)) continue;
        vis.insert(curr);
        for (auto& [next, weight] : adj_list[curr]) {
            if (vis.count(next)) continue;
            if (dist[curr] + weight < dist[next]) {
                dist[next] = dist[curr] + weight;
                bp[next] = curr;
                min_heap.push({dist[next], next});
            }
        }
    }
}

// resconstructs shortest cost path from source vertex to any other vertex
std::vector<int> constructShortestPath(int src, int dest) {
    std::vector<int> path = {dest};
    int prev = bp[dest];
    while (prev != -1) {
        path.push_back(prev);
        prev = bp[prev];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// sample test case for djekstra's algorithm
int main() {
    int src = 1, n = 5;
    // graph represented by edge set and adjacency list
    std::vector<edge> edges = {{0, 1, 2}, {1, 2, 1}, {1, 3, 4}, {3, 4, 1}, {2, 3, 5}, {0, 4, 5}};
    for (const auto& e: edges)
        adj_list[e.from].push_back({e.to, e.weight});
    // run djekstras on source vertex
    dijkstras(src, n);
    // prints distances between source vertex and any other vertex
    std::cout << std::left << std::setw(10) << "Vertex" << std::setw(10) << "Dist. from src" << '\n';
    for (int i = 0; i < n; i++) {
        if (i == src) continue;
        if (dist[i] == INT_MAX) 
            std::cout << std::setw(10) << i << std::setw(10) << "+INF" << '\n';
        else
            std::cout << std::setw(10) << i << std::setw(10) << dist[i] << '\n';
    }
    // reconstructs shortest path between source and destination vertex
    int dest = 4;
    std::cout << '\n' << "Sample shortest path reconstruction:" << '\n';
    std::cout << "Vertex " << src << " to " << dest  << ": ";
    std::vector<int> path = constructShortestPath(src, dest);
    std::cout << path[0];
    for (int i = 1; i < path.size(); i++)
        std::cout << " -> " << path[i];
    std::cout << std::endl;
    return 0;
}