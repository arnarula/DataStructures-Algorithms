#include <vector>
#include <iostream>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>

struct edge {
    double weight;
    int from, to;
    edge(int p_from, int p_to, double p_weight) : from(p_from), to(p_to), weight(p_weight) {}
    edge(int p_from, int p_to) : from(p_from), to(p_to), weight(0) {}
};

std::unordered_map<int, std::vector<std::pair<int, double>>> adj_list; // adjacency list
std::vector<int> dist; // tracks distances from source vrertex to every other vertex 

// searches for all vertices connected to a vertex which is part of a negative cycle
void dfs(std::vector<bool>& vis, int curr) {
    if (vis[curr]) return;
    vis[curr] = true;
    dist[curr] = INT_MIN;
    for (auto& [next, weight] : adj_list[curr])
        dfs(vis, next);
}

/* Bellman ford algorithm - time complexity O(EV): 
//   - finds shortest distance from src vertex to all other vertices
//   - detects negative cycles if there exists a shorter path greater than |V| - 1 in length
// @params
//   - edges: edge set
//   - n: # of vertices
//   - src: id of source vertex
*/

// algo 1) implements Bellman Ford, returns all vertices that are part of negative cycles
std::vector<bool> negativeCycleVertices(const std::vector<edge>& edges, int n, int src = 0) {
    // initializes distances from src vertex to every other vertex
    dist.resize(n, INT_MAX);
    dist[src] = 0;
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

// algo 2) implements Bellman Ford, returns true if negative cycle detected
bool detectNegativeCycle(const std::vector<edge>& edges, int n, int src = 0) {
    // stores distances from src vertex to every other vertex
    std::vector<int> dist(n, INT_MAX);
    dist[src] = 0;
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

// sample test case for bellman ford algorithm
int main() {
    int src = 0, n = 8;
    // represents graph using edge set and adjacency list
    std::vector<edge> edges = {{0, 1, 2}, {0, 4, 3}, {0, 5, 6}, {1, 2, 1}, {2, 3, 4}, {3, 1, -7}, {4, 5, 1}, {5, 7, 2}, {6, 7, -2}};
    for (const auto& e: edges)
        adj_list[e.from].push_back({e.to, e.weight});
    // run bellman ford algorithm on graph
    std::vector<bool> neg_cycle_label = negativeCycleVertices(edges, n, src);
    std::vector<int> neg_cycle_vertices;
    for (int i = 0; i < n; i++) {
        if (neg_cycle_label[i])
            neg_cycle_vertices.push_back(i);
    }
    // prints information regarding negative cycles
    if (neg_cycle_vertices.empty())
        std::cout << "No negative cycle detected!" << '\n';
    else {
        std::cout << "The following vertices are part of negative cycles: \n";
        for (auto& v : neg_cycle_vertices)
            std::cout << v << ' ';
        std::cout << '\n';
    }
    // prints distances between source vertex and any other vertex
    std::cout << std::left << std::setw(10) << "Vertex" << std::setw(10) << "Dist. from src" << '\n';
    for (int i = 0; i < n; i++) {
        if (i == src) continue;
        std::string cost = std::to_string(dist[i]);
        if (dist[i] == INT_MAX) cost = "+INF";
        if (dist[i] == INT_MIN) cost = "-INF";
        std::cout << std::setw(10) << i << std::setw(10) << cost << '\n';
    }
    return 0;
}