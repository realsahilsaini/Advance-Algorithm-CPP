#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent an edge
struct Edge {
    int destination;
    int weight;
};

// Function to perform Dijkstra's Algorithm
void dijkstra(vector<vector<Edge>>& graph, int source) {
    int numNodes = graph.size();
    vector<int> dist(numNodes, INT_MAX); // Initialize distances to infinity
    dist[source] = 0; // Distance from source to itself is 0

    // Priority queue to store nodes with their current distances
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source}); // Push source node with distance 0

    while (!pq.empty()) {
        int u = pq.top().second;
        int currDist = pq.top().first;
        pq.pop();

        // If current distance is greater than stored distance, skip
        if (currDist > dist[u]) continue;

        // Iterate through all neighbors of u
        for (Edge& edge : graph[u]) {
            int v = edge.destination;
            int weight = edge.weight;

            // If new distance is shorter, update distance and push to queue
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print the shortest distances from source to all nodes
    cout << "Shortest distances from source " << source << ":\n";
    for (int i = 0; i < numNodes; ++i) {
        cout << "Node " << i << ": " << dist[i] << "\n";
    }
}

int main() {
    int numNodes, numEdges;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    // Initialize graph with empty adjacency lists
    vector<vector<Edge>> graph(numNodes);

    // Input edges and their weights
    cout << "Enter the edges and their weights:\n";
    for (int i = 0; i < numEdges; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        // Add edge from u to v with weight
        graph[u].push_back({v, weight});
        // If graph is undirected, add edge from v to u as well
        // graph[v].push_back({u, weight});
    }

    int source;
    cout << "Enter the source node: ";
    cin >> source;

    // Perform Dijkstra's Algorithm
    dijkstra(graph, source);

    return 0;
}
