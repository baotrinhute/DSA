#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
using namespace std;
using namespace std::chrono;

struct Bid {
    string bidderId;
    double amount;       // bid price
    long long timestamp; // Unix ms
    int auctionId;
};

// ---------- Utilities ----------
void printBids(const vector<Bid>& v, size_t limit = 10) {
    for (size_t i = 0; i < min(v.size(), limit); ++i)
        cout << "[" << v[i].bidderId << "] $" << v[i].amount
             << " @ " << v[i].timestamp << "\n";
    if (v.size() > limit) cout << "... (" << v.size() << " total)\n";
}

bool loadBids(const string& path, vector<Bid>& out) {
    ifstream f(path);
    if (!f) return false;
    Bid b;
    while (f >> b.bidderId >> b.amount >> b.timestamp >> b.auctionId)
        out.push_back(b);
    return true;
}

// ---------- TODO: Implement these ----------
void insertionSort(vector<Bid>& v){         // Task A
    int n = v.size();
    for(int i = 1; i<n;i++){
        Bid key = v[i];
        int j = i -1;
        while(j >=0 && (v[j].amount > key.amount
        || (v[j].amount == key.amount && v[j].timestamp > key.timestamp))){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = key;
    }
}
void selectionSort(vector<Bid>& v){          // Task B
    int n = v.size();
    for(int i =0;i<n-1;i++){
        int maxIndex = i;
        for(int j = i+1;j<n;j++){
            if(v[j].amount > v[maxIndex].amount) maxIndex = j;
        }
        if(maxIndex != i) swap(v[i], v[maxIndex]);
    }
}
void interchangeSort(vector<Bid>& v){        // Task C
    int n = v.size();
    int swaps = 0;
    for(int i =0; i < n-1;i++){
        for(int j = i + 1; j < n;j++){
            if(v[j].amount < v[i].amount){
                swap(v[i],v[j]);
                swaps++;
            }
        }
    }
    cout << "Total swaps: " << swaps << "\n";
}
bool bubbleSortEarlyStop(vector<Bid>& v){    // Task D — returns true if stable (no swaps on a full pass)
    int n = v.size();
    bool isStable = true;
    for(int i = 0; i < n - 1; i++){
        bool swapped = false;
        for(int j = 0; j < n - 1 - i; j++){
            if(v[j].amount > v[j+1].amount){
                swap(v[j],v[j+1]);
                swapped = true;
                if(i == 0) isStable = false;
            }
        }
        if(!swapped) break;
    }
    return isStable;
}
void quickSort(vector<Bid>& v, int lo, int hi){ // Task E
    if (lo>=hi) return;
    int mid = lo + (hi-lo) / 2;
    if (v[mid].amount < v[lo].amount || (v[mid].amount == v[lo].amount && v[mid].timestamp < v[lo].timestamp))
    swap(v[lo], v[mid]);
    if (v[hi].amount < v[lo].amount || (v[hi].amount == v[lo].amount && v[hi].timestamp < v[lo].timestamp))
    swap(v[lo], v[hi]);
    if (v[hi].amount < v[mid].amount || (v[hi].amount == v[mid].amount && v[hi].timestamp < v[mid].timestamp))
    swap(v[mid], v[hi]);

    swap(v[mid],v[hi]);
    Bid pivot = v[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
    if (v[j].amount < pivot.amount || (v[j].amount == pivot.amount && v[j].timestamp < pivot.timestamp)) {
        i++;
        swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[hi]);
    int pi = i + 1;
    quickSort(v, lo, pi - 1);
    quickSort(v, pi + 1, hi);
}

void quickSortWrapper(vector<Bid>& v) {
    if (!v.empty()) {
        quickSort(v, 0, (int)v.size() - 1);
    }
}

// ---------- Driver ----------
int main(int argc, char* argv[]) {
    // See per-task instructions.
    vector<Bid> smalldata;
    if (!loadBids("test_data/small.txt", smalldata)) {
        cout << "Khong mo duoc file test_data/small.txt\n";
        return 1;
    }

    // Test Task A:
    cout << "Test Task A\n";
    vector<Bid> dataA = smalldata;
    insertionSort(dataA);
    printBids(dataA);
    cout << endl;

    // Test Task B:
    cout << "Test Task B (Top 3)\n";
    vector<Bid> dataB = smalldata;
    selectionSort(dataB);
    printBids(dataB, 3);
    cout << endl;

    // Test Task C:
    cout << "Test Task C\n";
    vector<Bid> dataC = smalldata;
    interchangeSort(dataC);
    printBids(dataC);
    cout << endl;

    //Test Task D:
    cout << "Test Task D\n";
    bool test1 = bubbleSortEarlyStop(dataC);
    cout << "Test 1 (Already sorted): " << (test1 ? "STABLE" : "UNSTABLE") << "\n";

    vector<Bid> dataD = dataB;
    bool test2 = bubbleSortEarlyStop(dataD);
    cout << "Test 2 (Reversed input): " << (test2 ? "STABLE" : "UNSTABLE") << "\n";
    cout << endl;

    // Test Task E (100,000 records):
    cout << "\nTest Task E (100,000 records)\n";
    vector<Bid> largeData;
    mt19937 rng(42);
    uniform_real_distribution<double> priceDist(10.0, 10000.0);
    
    ofstream out("test_data/large.txt");
    for (int i = 0; i < 100000; i++) {
        Bid b{"user_" + to_string(i % 5000), priceDist(rng), 1000000LL + i};
        largeData.push_back(b);
        out << b.bidderId << " " << b.amount << " " << b.timestamp << "\n";
    }
    out.close();
    cout << "Loaded records: " << largeData.size() << "\n";

    auto start = chrono::high_resolution_clock::now();
    quickSortWrapper(largeData);
    auto end = chrono::high_resolution_clock::now();

    double elapsedMs = chrono::duration<double, milli>(end - start).count();
    cout << "QuickSort runtime: " << elapsedMs << " ms\n";

    bool ok = true;
    for (size_t i = 1; i < largeData.size(); i++) {
        if (largeData[i - 1].amount > largeData[i].amount ||
           (largeData[i - 1].amount == largeData[i].amount && largeData[i - 1].timestamp > largeData[i].timestamp)) {
            ok = false;
            break;
        }
    }
    cout << "Sorted correctly: " << (ok ? "YES" : "NO") << "\n";
    printBids(largeData, 5);
    return 0;
}