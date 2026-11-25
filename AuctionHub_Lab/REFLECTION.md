1. Algorithms

A - Live Auction

Since typically live auction related data is already almost sorted, Insertion Sort can achieve a best case efficiency of O(n). Compared to other algorithms such as Quick Sort and Merge Sort which both have a time complexity of O(n log n), Insertion Sort has low overheads and only needs O(1) extra space. Hence, Insertion Sort is well suited to efficiently re-sort near-sorted live data.

B - Identification of Top 3 Bids

As we only need to determine the three highest bids, Selection Sort is suitable. Within each iteration of the algorithm the biggest element is both located and positioned. Consequently, at most K=3 (i.e. O(K)) swaps will occur and only O(1) extra space is needed. So, for relatively small datasets, there is minimal data movement (swapping) required.

C - Verification of Price

Although Interchange Sort has a time complexity of O(n²), it can be successfully applied where the volume of data to be sorted is limited (such as when n ≤ 50 as may be encountered within a QA verification scenario). When working with small data sets, the efficiency difference between an O(n²) and an O(n log n) algorithm is negligible. Moreover, Interchange Sort is uncomplicated to implement. It does not involve recursion and only needs O(1) extra space. Consequently, it is readily both testable and modifiable.

D - Price Constancy Verification

An Early Stop rule can be introduced to a Bubble Sort to mean that if no swaps are executed on one run of the algorithm then the algorithm will terminate. As a result, the best case efficiency of the algorithm is enhanced to become O(n). This avoids unnecessary comparisons of price data where constancy has already been established. Furthermore, the algorithm can be realised using just O(1) extra space.

E - Past Auction Data

Historical auction data (amounting to 100,000 data points) has been sorted using Quick Sort. This algorithm possesses an average efficiency of O(n log n). It also only utilises O(log n) stack space as it is recursive in nature. In addition, it has good cache locality. Utilisation of the median-of-three pivot selection strategy (i.e. calculation of the median of the first, middle and last data points) ensures that even if data is already either sorted or reverse-sorted, it avoids degenerate O(n²) worst-case partitions on already-sorted or reverse-sorted inputs.

2. Runtime (100,000 data points)

Data: 100,000 bids (test_data/large.txt)

Algorithm: Quick Sort with median-of-three pivot selection

Runtime: 192.831ms

Was data correctly sorted? YES

3. Bugs

Initially my Task B (Selection Sort) code mistakenly contained a swap(v[i], v[maxIndex]) statement inside the innermost j loop. Consequently, my code was undertaking multiple swaps on each iteration, akin to the Interchange Sort. However, in fact, only one value exchange should occur on each iteration.

I rectified this issue by moving the if (maxIndex != i) swap(v[i], v[maxIndex]); statement so that it is now situated after (i.e. outside of) the final brace of the inner j loop. This guarantees that once the true maximum of the sub-array of unsorted data has been ascertained, there is just one data point swap.

4. AI Engagement

Prompt 1 (Yellow Zone – Comprehension): Asked for an in-depth explanation of how the median-of-three pivot selection process organises the lo, mid and hi values ready for Lomuto partitioning.

Prompt 2 (Green Zone – Generation): Needed advice on how to use C++’s mt19937 and chrono classes to generate 100,000 fake bid data points and to measure runtime in milliseconds.

Prompt 3 (Green Zone – Problem Solving): Shared error messages and code containing loops in an effort to assist in locating mis-matched brackets within my Selection Sort code. I also supplied code illustrating struct member comparison in order to help identify problems with the comparative function of my Quick Sort code.

5. Worst Case Time Complexity of Median-of-Three Quick Sort

Despite the use of the median-of-three pivot selection strategy, Quick Sort can still suffer from a worst case time complexity of O(n²). Although median-of-three prevents worst case efficiency for already sorted, or reverse-sorted, data, it remains feasible to construct a dataset for which the median of the first, middle and last data points continually corresponds to either the second lowest or second highest data point. This will lead to asymmetrical partitions of size n-2 and 1.