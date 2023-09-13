//MedianHeap.h
#ifndef _MEDIANHEAP_H_
#define _MEDIANHEAP_H_

template <class T>
class Heap
{
 public:
  // default constructor
  Heap(int capacity, bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&));

  // destructor
  ~Heap();
 
  // PercalateUp and PercalateDown
  // For Min Heap
  void PercalateUp(int pos);
  void PercalateDown(int pos);

  // PercalateUpMax and PercalateDownMax
  //  For Max Heap
  void PercalateUpMax(int pos);
  void PercalateDownMax(int pos);

  // insert
  void insertHeap(const T& item, int pos);
 
  // getters
  int getHeapSize();
  int getHeapCapacity();
  int getLeft(const int& pos);
  int getRight(const int& pos);
  T   getParent(const int& pos);
  T   getRoot();
  void printValue(int pos);
  T   lastElement();
  T   getElement(int pos);

  // setters
  void incrementSize();
  void decrementSize();
  void setHeapSize(int size);

  // logic
  bool hasLeft(const int& pos);
  bool hasRight(const int& pos);
  bool isRoot(const int& pos);

  // overloaded [] operator
  T& operator[] (const int& pos) ;

 private:
  int m_heapSize;
  int m_heapCapacity;
  T* m_heapArray;
  int root;
  
  // Function pointers
  bool (*lessThan)(const T&, const T&);
  bool (*greaterThan)(const T&, const T&);
};

template <class T>
class MedianHeap
{
 public:
  // Constructor
  MedianHeap( bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap=100 ) ;
  
  // Copy Constructor
  MedianHeap(const MedianHeap<T>& otherH) ;

  // Destructor
  ~MedianHeap()  ;

  // Assignment Operator
  const MedianHeap<T>& operator=(const MedianHeap<T>& rhs)  ;

  // Getters
  int size() ;
  int capacity() ;
  T getMedian() ;
  T getMin() ;
  T getMax() ;

  // Functions for Grading
  int maxHeapSize() ;
  int minHeapSize() ;
  T locateInMaxHeap(int pos) ;
  T locateInMinHeap(int pos) ;

  // insert
  void insert(const T& item) ;
  
  // deleteItem
  bool deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&) ) ;

  // dump
  void dump() ;  

  // checks the sizes of both heaps after insertion
  // or deletion and fixes them
  void SanityCheck();

  // AbsoluteValueDifference
  int AbsoluteValueDifference(int num1, int num2);

 private:
  int m_capacity;
  int m_size;

  // max - min
  T m_max;
  T m_min;
  
  // Min and Max heaps
  Heap<T>* m_minHeap;
  Heap<T>* m_maxHeap;

  // Function pointers
  bool (*lessThan)(const T&, const T&);
  bool (*greaterThan)(const T&, const T&);
};



#include "MedianHeap.cpp"

#endif
