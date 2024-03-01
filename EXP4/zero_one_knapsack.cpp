#include <iostream>
#include <vector>

using namespace std;

// Structure to represent an item
struct Item {
    int weight;
    int profit;
};

// Function to solve 0/1 Knapsack problem
void knapsack(int N, int W, vector<Item>& items) {
    // Create a 2D array to store the maximum profit for different capacities
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    // Fill the dp table using bottom-up dynamic programming approach
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= W; ++j) {
            // If the current item's weight is less than or equal to the current capacity
            if (items[i - 1].weight <= j) {
                // Decide whether to include the current item or not
                dp[i][j] = max(dp[i - 1][j], items[i - 1].profit + dp[i - 1][j - items[i - 1].weight]);
            } else {
                // If the current item's weight exceeds the current capacity, exclude it
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Trace back to find the items selected
    int totalProfit = dp[N][W];
    int remainingWeight = W;
    vector<Item> selectedItems;

    for (int i = N; i > 0 && totalProfit > 0; --i) {
        if (dp[i][remainingWeight] != dp[i - 1][remainingWeight]) {
            // Item i was selected, add it to the selected items list
            selectedItems.push_back(items[i - 1]);
            totalProfit -= items[i - 1].profit;
            remainingWeight -= items[i - 1].weight;
        }
    }

    // Output the selected items and total profit
    cout << "Items selected:\n";
    for (const auto& item : selectedItems) {
        cout << "Weight: " << item.weight << ", Profit: " << item.profit << '\n';
    }
    cout << "Total Profit: " << dp[N][W] << '\n';
}

int main() {
    int N, W; // Number of items and knapsack capacity
    cout << "Enter number of items: ";
    cin >> N;
    cout << "Enter knapsack capacity: ";
    cin >> W;

    vector<Item> items(N); // Vector to store items

    // Input weight and profit for each item
    cout << "Enter weight and profit for each item:\n";
    for (int i = 0; i < N; ++i) {
        cin >> items[i].weight >> items[i].profit;
    }

    // Solve 0/1 Knapsack problem
    knapsack(N, W, items);

    return 0;
}
