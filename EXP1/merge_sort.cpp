#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
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
    mergeSort(arr, 0, n - 1);
    clock_t end_time = clock();

    cout << "\nSorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC * 1000; // Convert to milliseconds
    cout << "\nTime taken to sort: " << time_taken << " milliseconds\n";

    delete[] arr;

    return 0;
}
