#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int partition(vector<int>& v, int start, int end) {   // Semi-sorts the subarray around the pivot value such that elements to the
                                                      // left of pivot after partition are smaller and rightward elements are greater
    int piv = v[end];                                 // Defining the pivot to be the last of the subarray, can also be random
    int i = start, pIndex = start;                    // Defining a partition index to keep track of the place to finally swap with pivot
    while (i < end) {                                 // The last element (pivot) is the one being swapped with pIndex after loop ends
        if (v[i] < piv) {                             // Swap() doesnt work for swapping values, iter_swap() does
            iter_swap(v.begin()+i, v.begin()+pIndex); // Swap element at pIndex and i if v[i] is smaller than the pivot
            i++;                                      // Increase i to mark the next element being considered for comparison
            pIndex++;                                 // Increase pIndex to mark the next element being considered for swap
        }
        else {                                        // Otherwise if element at i is not less than the pivot value, i++
            i++;                                      // But pIndex remains same to mark that a "swap-worthy" element is not found
        }                                             // pIndex only changes when v[i] < piv value so pIndex <= i at any time
    }                                                 // Iterate till before the pivot, increase pIndex if v[i] < piv

    iter_swap(v.begin()+end, v.begin()+pIndex);       // After the loop ends, swap the pivot with the value at pIndex to get
    return pIndex;                                    // the pivot to its ideal place in the semi-sorted array
}                                                     // Now elements left of pIndex are smaller than piv and others are greater

void quickSort(vector<int>& v, int start, int end) {
    if (start >= end) {                               // Base case if size == 0 or size == 1
        return;                                       // No need to sort anything in base case
    }
    else {                                            // Otherwise, partition with the end as pivot and then sort left and right sides
        int idx = partition(v, start, end);           // Partition() returns the index of the pivot after partitioning is complete

        quickSort(v, start, idx - 1);                 // Recursive calls to sort the left side of the pivot from start to idx-1
        quickSort(v, idx + 1, end);                   // Recursive calls to sort the right side of the pivot from idx+1 to end
    }
}

int main() {
    vector<int> v = {29, 12, 12, 29, 12, 12, 29, 12};
    vector<int> x = {29, 17, 9, 4, 35, 35, 12, 21};

    quickSort(v, 0, v.size()-1);

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

}
