#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Utility function to print the distance matrix
void printMatrix(const vector<vector<int>>& dist, int V) {
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == numeric_limits<int>::max())
                cout << "INF ";
            else
                cout << dist[i][j] << "   ";
        }
        cout << endl;
    }
    cout << endl;
}

void floydWarshall(vector<vector<int>>& graph, int V) {
    vector<vector<int>> dist = graph;

    // Print initial matrix
    cout << "Initial matrix:" << endl;
    printMatrix(dist, V);

    for (int k = 0; k < V; ++k) {
        // Consider each vertex as an intermediate vertex.
        // 'k' is the current vertex being considered as an intermediate vertex.

        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                // If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
                if (dist[i][k] != numeric_limits<int>::max() && dist[k][j] != numeric_limits<int>::max() &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        // Print the distance matrix after the k-th iteration
        cout << "After considering vertex " << k + 1 << " as intermediate:" << endl;
        printMatrix(dist, V);
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V, numeric_limits<int>::max()));

    for (int i = 0; i < V; ++i)
        graph[i][i] = 0;

    cout << "Enter the number of edges: ";
    cin >> E;
    cout << "Enter edges in the format 'u v w' where 'u' and 'v' are vertices and 'w' is the weight:" << endl;

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
    }

    floydWarshall(graph, V);

    return 0;
}

