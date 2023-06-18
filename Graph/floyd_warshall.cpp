#include <vector>
#include <iostream>
#include <iomanip>

struct edge {
    double weight;
    int from, to;
    edge(int p_from, int p_to, double p_weight) : from(p_from), to(p_to), weight(p_weight) {}
    edge(int p_from, int p_to) : from(p_from), to(p_to), weight(0) {}
};

void preprocessGraph(const std::vector<edge>& edges, int n);
void floydWarshall(int n);
void checkNegCycles(int n);
std::vector<int> constructShortestPath(int i, int j);

std::vector<std::vector<int>> adj_matrix; // adjacency matrix
std::vector<std::vector<int>> fp_matrix; // foward pointer matrix (tracks path for reconstruction)

// represents graph using adjacency matrix 
void preprocessGraph(const std::vector<edge>& edges, int n) {
    adj_matrix.resize(n, std::vector<int>(n, INT_MAX));
    fp_matrix.resize(n, std::vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        adj_matrix[i][i] = 0;
    }
    for (const auto& e: edges) {
        adj_matrix[e.from][e.to] = e.weight;
        fp_matrix[e.from][e.to] = e.to;
    }
}

/* floyd warshall - time complexity O(V^3):
//   - finds minimum cost path between all pairs of vertices using dynamic programming
//   - intuition: algorithm merges all shortest paths passing through vertex 0, then vertex 1, then vertex 2, ...
// @params
//   - n = # of vertices
*/
void floydWarshall(int n) {
    // chooses common vertex in between two paths
    for (int k = 0; k < n; k++) {
        // iterates through all shortest paths between pairs of vertices
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adj_matrix[i][k] == INT_MAX || adj_matrix[k][j] == INT_MAX) continue;
                // updates shortest path from i -> j passing through vertex k
                if (adj_matrix[i][k] + adj_matrix[k][j] < adj_matrix[i][j]) {
                    adj_matrix[i][j] = adj_matrix[i][k] + adj_matrix[k][j];
                    fp_matrix[i][j] = fp_matrix[i][k];
                }
            }
        }
    }
}

// returns vertices traversed along shortest path from vertex i to j
// note: if negative cycles are present, must run checkNegCycles before calling path reconstruction to prevent false paths
std::vector<int> constructShortestPath(int src, int dest) {
    std::vector<int> path = {src};
    int next = fp_matrix[src][dest];
    while (next != -1) {
        path.push_back(next);
        next = fp_matrix[next][dest];
    }
    return path;
}

// detects negative cycles by rerunning floyd warshall i.e. checks if shortest path costs isn't minimal
void checkNegCycles(int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (adj_matrix[i][k] == INT_MAX || adj_matrix[k][j] == INT_MAX) continue;
                // sets path to negative infinity if negative cycle present
                if (adj_matrix[i][k] + adj_matrix[k][j] < adj_matrix[i][j]) {
                    adj_matrix[i][j] = INT_MIN;
                    fp_matrix[i][j] = -1;
                }
            }
        }
    }
}

int main() {
    int n = 5;
    // process graph into adjacency matrix
    std::vector<edge> edges = {{0, 1, 2}, {1, 2, 1}, {1, 3, 4}, {3, 4, 1}, {2, 2, -3}, {0, 4, 9}};
    preprocessGraph(edges, n);
    // run floyd warshall algorithm using adjacency matrix
    floydWarshall(n);
    checkNegCycles(n);
    // prints information regarding shortest paths between all vertex pairs
    std::cout << "Sample shortest path matrix:\n" << std::left;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // prints (+Inf) if no path exists between vertices i & j
            if (adj_matrix[i][j] == INT_MAX)
                std::cout << std::setw(5) << "+Inf" << ' ';
            // prints (-Inf) if path is part of negative cycle
            else if (adj_matrix[i][j] == INT_MIN)
                std::cout << std::setw(5) << "-Inf" << ' ';
            // prints shortest path between vertices i and j
            else
                std::cout << std::setw(5) << adj_matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
    // prints shortest path reconstruction between any two vertices
    std::cout << '\n' << "Sample shortest path reconstruction:" << '\n';
    int src = 0, dest = 4; // arbitrarily chosen
    std::vector<int> path = constructShortestPath(src, dest);
    std::cout << "Vertex " << src << " to " << dest  << ": ";
    std::cout << path[0];
    for (int i = 1; i < path.size(); i++)
        std::cout << " -> " << path[i];
    std::cout << std::endl;
    return 0;
}