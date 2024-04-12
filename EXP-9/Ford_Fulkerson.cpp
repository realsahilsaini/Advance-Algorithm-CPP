#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

// Finds the maximum flow from source to sink in the given graph
int fordFulkerson(vector<vector<int>>& capacity, int source, int sink, vector<vector<int>>& residualGraph) {
    int numVertices = capacity.size();
    residualGraph = capacity; // Initialize residual graph as original capacity graph
    vector<int> parent(numVertices); // Array to store the path
    int maxFlow = 0;

    // Augment the flow while there is a path from source to sink
    while (true) {
        vector<bool> visited(numVertices, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;
        bool foundAugmentingPath = false;

        // Standard BFS loop
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < numVertices; v++) {
                if (!visited[v] && residualGraph[u][v] > 0) { // Found a connection with capacity left
                    if (v == sink) {
                        parent[v] = u;
                        foundAugmentingPath = true;
                        break;
                    }
                    q.push(v);
                    visited[v] = true;
                    parent[v] = u;
                }
            }

            if (foundAugmentingPath)
                break;
        }

        // No augmenting path anymore
        if (!foundAugmentingPath)
            break;

        // Find the maximum flow through the path found.
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Update residual capacities of the edges and reverse edges
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

// Function to find the minimum cut and display it
void findMinCut(vector<vector<int>>& originalGraph, vector<vector<int>>& residualGraph, int source) {
    int numVertices = originalGraph.size();
    vector<bool> visited(numVertices, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;

    // Use BFS to mark all reachable vertices from source in the residual graph
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < numVertices; v++) {
            if (residualGraph[u][v] > 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    // Display minimum cut
    cout << "Minimum Cut:" << endl;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (visited[i] && !visited[j] && originalGraph[i][j]) {
                cout << i << " - " << j << endl;
            }
        }
    }
}

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<vector<int>> capacity(numVertices, vector<int>(numVertices, 0));
    cout << "Enter the edges and their capacities:" << endl;
    for (int i = 0; i < numEdges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        capacity[u][v] = w;
    }

    int source, sink;
    cout << "Enter the source: ";
    cin >> source;
    cout << "Enter the sink: ";
    cin >> sink;

    vector<vector<int>> residualGraph;
    int maxFlow = fordFulkerson(capacity, source, sink, residualGraph);

    cout << "Maximum flow is: " << maxFlow << endl;
    findMinCut(capacity, residualGraph, source);

    return 0;
}
