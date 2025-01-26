#include <vector>
#include "HeapT.h"
using std::vector;

template <typename T>
vector<T> largestm(vector<T> nVector, int m) {

    // If m is 0 or less, then return an empty vector
    if (m <= 0) {
        return vector<T>(); 
    }

    // Get the size of the vector
    int n = nVector.size();

    // Ensure that resultSize is the smaller of m or n
    int resultSize = (n < m) ? n : m;  

    // Create vector that stores the result
    vector<T> result(resultSize);

    // Create min heap that keeps track of the top m largest nodes
    HeapT<T> minHeap(m);  

    // Process the input vector to fill the heap
    for (int i = 0; i < n; i++) {
        if (minHeap.size() < m) {
            minHeap.insert(nVector[i]);  // Insert until the heap has m nodes
        } else if (nVector[i] > minHeap.peek()) {
            // Replace the smallest node (root) if the new value is larger
            minHeap.remove();
            minHeap.insert(nVector[i]);
        }
    }

    // Build the result vector by removing elements from the heap in descending order
    for (int i = 0; i < resultSize; i++) {
        result[resultSize - 1 - i] = minHeap.remove();  // Insert in descending order
    }

    return result;
}
