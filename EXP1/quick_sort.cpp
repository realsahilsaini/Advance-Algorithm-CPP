#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    srand(time(0));

    int n;
    cout << "Enter the number of random elements: ";
    cin >> n;

    int* arr = new int[n];
    cout << "Generated array: ";
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;  // Generating random numbers between 0 and 99
        cout << arr[i] << " ";
    }

    clock_t start_time = clock();
    quickSort(arr, 0, n - 1);
    clock_t end_time = clock();

    cout << "\nSorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // Convert to milliseconds
    cout << "\nTime taken to sort: " << time_taken << " milliseconds\n";

    delete[] arr;

    return 0;
}
