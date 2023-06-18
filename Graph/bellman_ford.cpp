#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

struct edge {
    double weight;
    int from, to;
    edge(int p_from, int p_to, double p_weight) : from(p_from), to(p_to), weight(p_weight) {}
    edge(int p_from, int p_to) : from(p_from), to(p_to), weight(0) {}
};

std::unordered_map<int, std::vector<std::pair<int, double>>> adj_list;

// represents graph using adjacency list 
void preprocessGraph(const std::vector<edge>& edges) {
    for (const auto& e: edges)
        adj_list[e.from].push_back({e.to, e.weight});
}

// searches for all vertices connected to a vertex which is part of a negative cycle
void dfs(std::vector<bool>& vis, int start) {
    if (vis[start]) return;
    vis[start] = true;
    for (auto& [next, weight] : adj_list[start])
        dfs(vis, next);
}

/* Bellman ford algorithm - time complexity O(EV): 
//   - finds shortest distance from start vertex to all other vertices
//   - detects negative cycles if there exists a shorter path greater than |V| - 1 in length
// @params
//   - edges: edge set
//   - n: # of vertices
//   - s: label of start vertex
*/

// implements Bellman Ford, returns all vertices that are part of negative cycles
std::vector<bool> negativeCycleVertices(const std::vector<edge>& edges, int n, int start = 0) {
    // stores distances from start vertex to every other vertex
    std::vector<int> dist(n, INT_MAX);
    dist[start] = 0;
   // iterates through and relaxes all edges, repeats |V| - 1 times
    for (int i = 0; i < n - 1; i++) {
        for (const auto& e : edges) {
            if (e.from == INT_MAX) continue;
            if (dist[e.from] + e.weight < dist[e.to])
                dist[e.to] = dist[e.from] + e.weight;
        }
    }
    // detects negative cycle if any edge weight can be relaxed during |V|th iteration
    std::vector<bool> cycle(n, false);
    for (const auto& e : edges) {
        if (e.from == INT_MAX) continue;
        // if negative cycle detected, dfs on "bad" vertices
        if (dist[e.from] + e.weight < dist[e.to])
            dfs(cycle, e.to);
    }
    return cycle;
}

// implements Bellman Ford, returns true if negative cycle detected
bool detectNegativeCycle(const std::vector<edge>& edges, int n, int start = 0) {
    // stores distances from start vertex to every other vertex
    std::vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    // iterates through and relaxes all edges, repeats |V| - 1 times
    for (int i = 0; i < n - 1; i++) {
        for (const auto& e : edges) {
            if (e.from == INT_MAX) continue;
            if (dist[e.from] + e.weight < dist[e.to])
                dist[e.to] = dist[e.from] + e.weight;
        }
    }
    // detects negative cycle if any edge weight can be relaxed during |V|th iteration
    for (const auto& e : edges) {
        if (e.from == INT_MAX) continue;
        // if negative cycle detected, return true
        if (dist[e.from] + e.weight < dist[e.to])
            return true;
    }
    return false;
}

int main() {
    int n = 3;
    // represents graph by edge set
    std::vector<edge> edges = {{0, 1, 2}, {1, 2, 1}, {2, 2, -3}};
    preprocessGraph(edges);
    // run bellman ford algorithm on graph
    std::vector<bool> neg_cycle_label = negativeCycleVertices(edges, n);
    std::vector<int> neg_cycle_vertices;
    for (int i = 0; i < n; i++) {
        if (neg_cycle_label[i])
            neg_cycle_vertices.push_back(i);
    }
    if (neg_cycle_vertices.empty())
        std::cout << "No negative cycle detected!" << '\n';
    else {
        std::cout << "The following vertices are part of negative cycles: \n";
        for (auto& v : neg_cycle_vertices)
            std::cout << v << ' ';
        std::cout << '\n';
    }
    return 0;
}