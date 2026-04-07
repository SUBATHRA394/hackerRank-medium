#include<bits/stdc++.h>

using namespace std;
#include <vector>
#include <algorithm>

// Structure to store individual workshop details
struct Workshop {
    int start_time;
    int duration;
    int end_time;
};

// Structure to hold the collection of all available workshops
struct Available_Workshops {
    int n;
    Workshop* workshops;
};

// Comparator function to sort workshops based on their end_time
bool compareWorkshops(const Workshop& a, const Workshop& b) {
    return a.end_time < b.end_time;
}

// Function to allocate memory and initialize workshop data
Available_Workshops* initialize(int start_time[], int duration[], int n) {
    Available_Workshops* ptr = new Available_Workshops;
    ptr->n = n;
    ptr->workshops = new Workshop[n];
    
    for (int i = 0; i < n; i++) {
        ptr->workshops[i].start_time = start_time[i];
        ptr->workshops[i].duration = duration[i];
        ptr->workshops[i].end_time = start_time[i] + duration[i];
    }
    
    return ptr;
}

// Function to calculate the maximum number of workshops a student can attend
int CalculateMaxWorkshops(Available_Workshops* ptr) {
    // Transfer data to a vector for easy sorting
    vector<Workshop> v;
    for (int i = 0; i < ptr->n; i++) {
        v.push_back(ptr->workshops[i]);
    }
    
    // Greedy Strategy: Sort workshops by the earliest end time
    sort(v.begin(), v.end(), compareWorkshops);
    
    int count = 0;
    int last_end_time = 0;
    
    for (int i = 0; i < ptr->n; i++) {
        // Only attend if the current workshop starts after or at the previous one's end time
        if (v[i].start_time >= last_end_time) {
            count++;
            last_end_time = v[i].end_time;
        }
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
