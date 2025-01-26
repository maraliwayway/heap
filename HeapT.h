#pragma once //include guard
#include <iostream>

// Heap class
template<class T>
class HeapT
{

public:
    // Constructor 
    // Array capacity equal to its integer parameter
    HeapT(int capacity);

    // Copy constructor
    // Creates deepy copy of its constant Heap reference parameter
    HeapT(const HeapT& other);

    // Destructor
    ~HeapT();

    // Assignment operator
    HeapT& operator=(const HeapT& other);

    // Insert
    void insert(T node);

    // Remove
    // Returns the root
    T remove();

    // Peek
    T peek() const;

    // Merge
    HeapT<T> merge(const HeapT<T>& other) const;

    // Size
    int size() const;

private:

    // Pointer to underlying array that holds heap
    T* heapArray;

    // Capacity (max number of nodes in heap)
    int capacity;

    // Current size
    int currentSize;

    // Helper functions
    void bubbleUp(int index);
    void bubbleDown(int index);
    void swap(int index1, int index2); 
    void copyFrom(const HeapT<T>& other);

};

// Heap method implementations

// Constructor method
template<class T>
HeapT<T>::HeapT(int capacity) {
    this->capacity = capacity;
    this->currentSize = 0;
    heapArray = new T[capacity];
}

// Copy constructor method
template<class T>
HeapT<T>::HeapT(const HeapT<T>& other) {
    copyFrom(other);
}

// Destructor method
template<class T>
HeapT<T>::~HeapT() {
    delete[] heapArray;
}

// Assignment operator method
template<class T>
HeapT<T>& HeapT<T>::operator=(const HeapT<T>& other) {
    if (this != &other) { // Check for self-assignment
        delete[] heapArray; // Clean up
        copyFrom(other);
    }
    return *this;
}

// Insert method
template<class T>
void HeapT<T>::insert(T node) {
    if (currentSize == capacity) { // Check if heap is full
        throw std::runtime_error("ERROR: Heap is full");
    }

    heapArray[currentSize] = node;
    bubbleUp(currentSize);
    currentSize++;
}

// Remove method
template<class T>
T HeapT<T>::remove() {
    if (currentSize == 0) { // Check if heap is empty
        throw std::runtime_error("ERROR: Heap is empty");
    }

    T removedRoot = heapArray[0];
    heapArray[0] = heapArray[currentSize - 1];
    currentSize--;

    bubbleDown(0);

    return removedRoot;
}

// Peek method
template<class T>
T HeapT<T>::peek() const {
    if (currentSize == 0) { // Check if heap is empty
        throw std::runtime_error("ERROR: Heap is empty");
    }

    return heapArray[0];
}

// Merge method
template<class T>
HeapT<T> HeapT<T>::merge(const HeapT<T>& other) const {
    HeapT mergedHeap(this->capacity + other.capacity);

    for (int i = 0; i < this->currentSize; i++) {
        mergedHeap.insert(this->heapArray[i]);
    }
    for (int i = 0; i < other.currentSize; i++) {
        mergedHeap.insert(other.heapArray[i]);
    }

    return mergedHeap;
}

// Size method
template<class T>
int HeapT<T>::size() const {
    return currentSize;
}

// Bubble up helper method
template<class T>
void HeapT<T>::bubbleUp(int index) {
    int parentIndex = (index - 1) / 2;

    if (index > 0 && heapArray[parentIndex] > heapArray[index]) {
        swap(index, parentIndex);
        bubbleUp(parentIndex);
    }
}

// Bubble down helper method
template<class T>
void HeapT<T>::bubbleDown(int index) {
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;
    int smallest = index;

    if (leftChildIndex < currentSize && heapArray[smallest] > heapArray[leftChildIndex]) {
        smallest = leftChildIndex;
    }

    if (rightChildIndex < currentSize && heapArray[smallest] > heapArray[rightChildIndex]) {
        smallest = rightChildIndex;
    }

    if (smallest != index) {
        swap(index, smallest);
        bubbleDown(smallest);
    }
}

// Swap helper method
template<class T>
void HeapT<T>::swap(int index1, int index2) {
    T temp = heapArray[index1];
    heapArray[index1] = heapArray[index2];
    heapArray[index2] = temp;
}

// Copy helper method
template<class T>
void HeapT<T>::copyFrom(const HeapT<T>& other) {
    // Copy capacity and size
    capacity = other.capacity;
    currentSize = other.currentSize;

    // Allocate new array and copy elements from other heap
    heapArray = new T[capacity];
    for (int i = 0; i < currentSize; i++) {
        heapArray[i] = other.heapArray[i];
    }
}