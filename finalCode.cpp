#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// Generate Random Numbers
vector<int> generateRandomNumbers(int N) {
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

// Merge Sort Helper
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort Helper
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Binary Search
int binarySearch(vector<int>& arr, int key) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// Exponential Search
int exponentialSearch(vector<int>& arr, int key) {
    if (arr[0] == key) return 0;
    int i = 1;
    while (i < arr.size() && arr[i] <= key)
        i *= 2;

    int left = i / 2;
    int right = min(i, (int)arr.size() - 1);
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// MAIN FUNCTION
int main() {
    srand(time(0));
    int N, key;
    cout << "Enter number of elements (N): ";
    cin >> N;

    vector<int> data = generateRandomNumbers(N);
     cout << "Here are the generated numbers:\n";
    for (int i = 0; i < N; ++i) {
        cout << data[i] << " ";
    }
    cout << "\n\n";

    vector<int> dataForMerge = data;
    vector<int> dataForSearch = data;

    // Quick Sort Timing
    auto start1 = high_resolution_clock::now();
    quickSort(data, 0, N - 1);
    auto stop1 = high_resolution_clock::now();
    cout << "Quick Sort Time: " << duration_cast<milliseconds>(stop1 - start1).count() << " ms\n";

    // Merge Sort Timing
    auto start2 = high_resolution_clock::now();
    mergeSort(dataForMerge, 0, N - 1);
    auto stop2 = high_resolution_clock::now();
    cout << "Merge Sort Time: " << duration_cast<milliseconds>(stop2 - start2).count() << " ms\n";

    sort(dataForSearch.begin(), dataForSearch.end()); // sort for search

    cout << "Enter the number to search: ";
    cin >> key;

    // Binary Search Timing
    auto start3 = high_resolution_clock::now();
    int index1 = binarySearch(dataForSearch, key);
    auto stop3 = high_resolution_clock::now();

    // Exponential Search Timing
    auto start4 = high_resolution_clock::now();
    int index2 = exponentialSearch(dataForSearch, key);
    auto stop4 = high_resolution_clock::now();

    cout << "\n--- SEARCH RESULTS ---\n";
    if (index1 != -1)
        cout << "Binary Search: Found at index " << index1 << " (Time: " << duration_cast<microseconds>(stop3 - start3).count() << " microseconds)\n";
    else
        cout << "Binary Search: Not Found (Time: " << duration_cast<microseconds>(stop3 - start3).count() << " microseconds)\n";

    if (index2 != -1)
        cout << "Exponential Search: Found at index " << index2 << " (Time: " << duration_cast<microseconds>(stop4 - start4).count() << " microseconds)\n";
    else
        cout << "Exponential Search: Not Found (Time: " << duration_cast<microseconds>(stop4 - start4).count() << " microseconds)\n";

    return 0;
}
