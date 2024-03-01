#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii; // Pair of (weight, node)

void dijkstra(int n, int start, vector<vector<pii>>& graph) {
    vector<int> dist(n, INT_MAX); // Initialize distances to infinity
    vector<int> parent(n, -1); // Initialize parent array to -1
    priority_queue<pii, vector<pii>, greater<pii>> pq; // Min-heap to store (distance, node) pairs

    dist[start] = 0; // Distance from start node to itself is 0
    pq.push({0, start}); // Push start node to the priority queue

    while (!pq.empty()) {
        int u = pq.top().second; // Extract node with minimum distance
        pq.pop();

        // Output current shortest path for each node
        cout << "Iteration " << u << ": ";
        vector<int> path;
        for (int j = u; j != -1; j = parent[j])
            path.push_back(j);
        for (int j = path.size() - 1; j >= 0; --j)
            cout << path[j] << (j == 0 ? "" : " -> ");
        cout << " (Distance: " << dist[u] << ")" << endl;

        // Iterate through all neighbors of node u
        for (auto& neighbor : graph[u]) {
            int v = neighbor.second; // Neighbor node
            int weight = neighbor.first; // Weight of edge (u, v)

            // Relaxation step: If shorter path found, update distance and parent
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v}); // Push updated distance to priority queue
            }
        }
    }
}

int main() {
    int n, m; // Number of nodes and edges
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<pii>> graph(n); // Adjacency list representation of graph

    // Input edges and weights
    cout << "Enter edges and weights (source destination weight):\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({w, v}); // Add edge (u, v) with weight w
    }

    int start; // Starting node for Dijkstra's Algorithm
    cout << "Enter starting node: ";
    cin >> start;

    // Run Dijkstra's Algorithm
    dijkstra(n, start, graph);

    return 0;
}



































































































// #include <iostream>
// #include <vector>
// #include <queue>
// #include <climits>

// using namespace std;

// // Structure to represent an edge
// struct Edge {
//     int destination;
//     int weight;
// };

// // Function to perform Dijkstra's Algorithm
// void dijkstra(vector<vector<Edge>>& graph, int source) {
//     int numNodes = graph.size();
//     vector<int> dist(numNodes, INT_MAX); // Initialize distances to infinity
//     dist[source] = 0; // Distance from source to itself is 0

//     // Priority queue to store nodes with their current distances
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
//     pq.push({0, source}); // Push source node with distance 0

//     while (!pq.empty()) {
//         int u = pq.top().second;
//         int currDist = pq.top().first;
//         pq.pop();

//         // If current distance is greater than stored distance, skip
//         if (currDist > dist[u]) continue;

//         // Iterate through all neighbors of u
//         for (Edge& edge : graph[u]) {
//             int v = edge.destination;
//             int weight = edge.weight;

//             // If new distance is shorter, update distance and push to queue
//             if (dist[u] + weight < dist[v]) {
//                 dist[v] = dist[u] + weight;
//                 pq.push({dist[v], v});
//             }
//         }
//     }

//     // Print the shortest distances from source to all nodes
//     cout << "Shortest distances from source " << source << ":\n";
//     for (int i = 0; i < numNodes; ++i) {
//         cout << "Node " << i << ": " << dist[i] << "\n";
//     }
// }

// int main() {
//     int numNodes, numEdges;
//     cout << "Enter the number of nodes: ";
//     cin >> numNodes;
//     cout << "Enter the number of edges: ";
//     cin >> numEdges;

//     // Initialize graph with empty adjacency lists
//     vector<vector<Edge>> graph(numNodes);

//     // Input edges and their weights
//     cout << "Enter the edges and their weights:\n";
//     for (int i = 0; i < numEdges; ++i) {
//         int u, v, weight;
//         cin >> u >> v >> weight;
//         // Add edge from u to v with weight
//         graph[u].push_back({v, weight});
//         // If graph is undirected, add edge from v to u as well
//         // graph[v].push_back({u, weight});
//     }

//     int source;
//     cout << "Enter the source node: ";
//     cin >> source;

//     // Perform Dijkstra's Algorithm
//     dijkstra(graph, source);

//     return 0;
// }
