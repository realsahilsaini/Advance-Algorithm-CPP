#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int weight;
    int profit;
};

struct Solution {
    int itemIndex;
    double portion;
};

bool compare(Item a, Item b) {
    double r1 = (double)a.profit / a.weight;
    double r2 = (double)b.profit / b.weight;
    return r1 > r2;
}

pair<double, vector<Solution>> fractionalKnapsack(int n, vector<Item>& items, int capacity) {
    sort(items.begin(), items.end(), compare);

    int curWeight = 0;
    double finalProfit = 0.0;
    vector<Solution> solution;

    for (int i = 0; i < n; i++) {
        if (curWeight + items[i].weight <= capacity) {
            curWeight += items[i].weight;
            finalProfit += items[i].profit;
            solution.push_back({i, 1.0});
        } else {
            int remain = capacity - curWeight;
            finalProfit += items[i].profit * ((double)remain / items[i].weight);
            solution.push_back({i, (double)remain / items[i].weight});
            break;
        }
    }

    return make_pair(finalProfit, solution);
}

int main() {
    int n;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter weight and profit for item " << i+1 << ": ";
        cin >> items[i].weight >> items[i].profit;
    }

    int capacity;
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    pair<double, vector<Solution>> result = fractionalKnapsack(n, items, capacity);

    cout << "Total profit: " << result.first << "\n";
    cout << "Selected items (index and portion): ";
    for (const Solution& s : result.second) {
        cout << "(" << s.itemIndex+1 << ", " << s.portion << ") ";
    }
    cout << "\n";

    return 0;
}