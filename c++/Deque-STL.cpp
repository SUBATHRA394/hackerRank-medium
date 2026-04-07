#include <iostream>
#include <deque> 
#include <vector>

using namespace std;

void printKMax(int arr[], int n, int k) {
    deque<int> dq;

    for (int i = 0; i < n; i++) {
        // 1. Remove elements that are out of the current window (left side)
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }

        // 2. Remove elements from the back that are smaller than the current element
        // because they can never be the maximum again.
        while (!dq.empty() && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
        }

        // 3. Add the current element's index to the back
        dq.push_back(i);

        // 4. Print the front element (the maximum) once the first window is full
        if (i >= k - 1) {
            cout << arr[dq.front()] << (i == n - 1 ? "" : " ");
        }
    }
    cout << "\n"; // Use "\n" instead of endl for faster performance
}

int main() {
    // Optimization for large input/output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t > 0) {
        int n, k;
        cin >> n >> k;
        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        printKMax(arr, n, k);
        t--;
    }
    return 0;
}
