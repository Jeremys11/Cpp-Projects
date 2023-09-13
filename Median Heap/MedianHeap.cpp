//MedianHeap.cpp
#ifndef _MEDIAN_HEAP_CPP_
#define _MEDIAN_HEAP_CPP_


#include "MedianHeap.h"
#include <stdexcept>
#include <iostream>

using namespace std;

//////////////////////////////
//                          //
// MedianHeap Implentations //
//                          //
//////////////////////////////

// Constructor
//
template <class T>
MedianHeap<T>::MedianHeap( bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&), int cap ) {
  lessThan = lt;
  greaterThan = gt;
  m_capacity = cap;
  m_size = 0;

  m_maxHeap = new Heap<T>((m_capacity/2)+2, lessThan, greaterThan);
  m_minHeap = new Heap<T>((m_capacity/2)+2, lessThan, greaterThan);
}

// Copy Constructor
//
template <class T>
MedianHeap<T>::MedianHeap(const MedianHeap<T>& otherH) {

  lessThan = otherH.lessThan;
  greaterThan = otherH.greaterThan;
  m_capacity = otherH.m_capacity;
  m_size = otherH.m_size;
  m_max = otherH.m_max;
  m_min = otherH.m_min;

  m_maxHeap = new Heap<T>((m_capacity/2)+2, lessThan, greaterThan);
  m_minHeap = new Heap<T>((m_capacity/2)+2, lessThan, greaterThan);

  m_maxHeap->setHeapSize(otherH.m_maxHeap->getHeapSize());
  m_minHeap->setHeapSize(otherH.m_minHeap->getHeapSize());
  
  for(int i = 1; i < m_maxHeap->getHeapSize()+1; i++){
    m_maxHeap->insertHeap(otherH.m_maxHeap->getElement(i),i);
  }

  for(int i = 1; i < m_minHeap->getHeapSize()+1; i++){
    m_minHeap->insertHeap(otherH.m_minHeap->getElement(i),i);
  }
}

// Destructor
//
template <class T>
MedianHeap<T>::~MedianHeap()  {
  delete m_maxHeap;
  delete m_minHeap;

  m_maxHeap = NULL;
  m_minHeap = NULL;
  lessThan = NULL;
  greaterThan = NULL;
}

// Overloaded Assignment Operator
//
template <class T>
const MedianHeap<T>& MedianHeap<T>::operator=(const MedianHeap<T>& rhs){

  delete m_maxHeap;
  delete m_minHeap;

  m_maxHeap = NULL;
  m_minHeap = NULL;
  lessThan = NULL;
  greaterThan = NULL;

  lessThan = rhs.lessThan;
  greaterThan = rhs.greaterThan;
  m_capacity = rhs.m_capacity;
  m_size = rhs.m_size;
  m_max = rhs.m_max;
  m_min = rhs.m_min;

  m_maxHeap = new Heap<T>((m_capacity/2)+2, lessThan, greaterThan);
  m_minHeap = new Heap<T>((m_capacity/2)+2, lessThan, greaterThan);

  m_maxHeap->setHeapSize(rhs.m_maxHeap->getHeapSize());
  m_minHeap->setHeapSize(rhs.m_minHeap->getHeapSize());

  for(int i = 1; i < m_maxHeap->getHeapSize()+1; i++){
    m_maxHeap->insertHeap(rhs.m_maxHeap->getElement(i),i);
  }

  for(int i = 1; i < m_minHeap->getHeapSize()+1; i++){
    m_minHeap->insertHeap(rhs.m_minHeap->getElement(i),i);
  }

  return *this;
}

// MedianHeap method size
//
template <class T>
int MedianHeap<T>::size() {
  return m_size;
}

// MedianHeap method capacity
//
template <class T>
int MedianHeap<T>::capacity() {
  return m_capacity;
}


// MedianHeap method insert
//
template <class T>
void MedianHeap<T>::insert(const T& item) {

  // full heap throw exception
  if(m_size == m_capacity)
    throw std::out_of_range("Error");

  if(m_size == 0){
    m_min = item;
    m_max = item;
  }
  else{
    if(lessThan(item,m_min))
      m_min = item;
    if(greaterThan(item,m_max))
      m_max = item;
  }

  // Empty heap default to min heap
  if(m_size == 0){
    m_minHeap->insertHeap(item,m_minHeap->getHeapSize()+1);
    m_minHeap->incrementSize();

    m_minHeap->PercalateUp(m_minHeap->getHeapSize() );

    m_max = item;
    m_min = item;
  }

  else{
    // Check in minHeap
    if(greaterThan(item,m_minHeap->getRoot())){
      m_minHeap->insertHeap(item,m_minHeap->getHeapSize()+1);
      m_minHeap->incrementSize();
      
      m_minHeap->PercalateUp(m_minHeap->getHeapSize() );
    }

    // if max heap is empty
    else if(m_maxHeap->getHeapSize() == 0){
      m_maxHeap->insertHeap(item,m_maxHeap->getHeapSize()+1);
      m_maxHeap->incrementSize();

      m_maxHeap->PercalateUpMax( m_maxHeap->getHeapSize() );
    }
    
    // Check in maxHeap
    else if(lessThan(item,m_maxHeap->getRoot())){
      m_maxHeap->insertHeap(item,m_maxHeap->getHeapSize()+1);
      m_maxHeap->incrementSize();
      
      m_maxHeap->PercalateUpMax( m_maxHeap->getHeapSize() );
    }
     
    // Put in minHeap for default
    else{
      m_minHeap->insertHeap(item,m_minHeap->getHeapSize()+1);
      m_minHeap->incrementSize();

      m_minHeap->PercalateUp(m_minHeap->getHeapSize() );
    }
  }
 
  m_size++; // increment size

  MedianHeap::SanityCheck();
}

// MedianHeap method getMedian
//
// Returns median from minHeap if minHeap size >= maxHeap size
// else returns median from maxHeap
//
template <class T>
T MedianHeap<T>::getMedian() {
  if(m_minHeap->getHeapSize() >= m_maxHeap->getHeapSize())
    return m_minHeap->getRoot();
  else
    return m_maxHeap->getRoot();
}

// MedianHeap method getMin
//
template <class T>
T MedianHeap<T>::getMin() {
  return m_min;
}

// MedianHeap method getMax
//
template <class T>
T MedianHeap<T>::getMax() {
  return m_max;
}

// MedianHeap method deleteItem
//
template <class T>
bool MedianHeap<T>::deleteItem(T& givenItem, bool (*equalTo) (const T&, const T&) ) {
  
  bool found = false;
  
  // If deleting max or min - finding new max or min
  
  // finding max
  if(equalTo(givenItem, m_max)){
    m_max = m_minHeap->getRoot();
    for(int i = 1; i < m_minHeap->getHeapSize()+1; i++){
      if(greaterThan(m_minHeap->getElement(i),m_max) && !equalTo(m_minHeap->getElement(i),givenItem)/*not equal*/)
	m_max = m_minHeap->getElement(i);
    }
  }
  // finding min
  if(equalTo(givenItem,m_min)){
    m_min = m_maxHeap->getRoot();
    for(int i = 1; i < m_maxHeap->getHeapSize()+1; i++){
      if(lessThan(m_minHeap->getElement(i),m_max) && !equalTo(m_maxHeap->getElement(i),givenItem)/*not equal*/)
        m_min = m_maxHeap->getElement(i);
    }
  }

  // If empty - throw error
  if(m_size == 0)
    throw std::out_of_range("Error");

  // Check in minHeap
  if(m_minHeap->getHeapSize() > 0){
    for(int i = 1; i < m_minHeap->getHeapSize()+1; i++){
      if(equalTo(givenItem,m_minHeap->getElement(i) )){
	found = true;
	givenItem = m_minHeap->getElement(i);
	m_minHeap->insertHeap(m_minHeap->lastElement(),i);
	m_minHeap->decrementSize();
	
	if ( i == 1 || lessThan(m_minHeap->getParent(i), givenItem) )
	  m_minHeap->PercalateDown(i);  // Move the node down the tree
	else
	  m_minHeap->PercalateUp(i);    // Move the node up the tree
      }
    }
  }

  // Check in Max Heap
  if(m_maxHeap->getHeapSize() > 0){
    for(int i = 1; i < m_maxHeap->getHeapSize()+1; i++){
      if(equalTo(givenItem,m_maxHeap->getElement(i) )){
	found = true;
	givenItem = m_maxHeap->getElement(i);
	m_maxHeap->insertHeap(m_maxHeap->lastElement(),i);
	m_maxHeap->decrementSize();

	if ( i == 1 || greaterThan(m_maxHeap->getParent(i), givenItem) )
	  m_maxHeap->PercalateDownMax(i);  // Move the node down the tree
	else
	  m_maxHeap->PercalateUpMax(i);    // Move the node up the tree
      }
    }
  }

  else
    return false;

  if(found == true)
    m_size--;

  MedianHeap::SanityCheck();

  return found;
}

// MedianHeap method dump
//
// Used for debugging
//
template <class T>
void MedianHeap<T>::dump() {
  
  cout << "... MedianHeap::dump() ..." << endl;
  cout << "size: " << size()
       << " capacity: " << capacity()
       << endl;

  cout << "Max: ";
  cout << m_max;
  cout << endl;
  cout << "Min: ";
  cout << m_min;
  cout << endl;


  cout << "===== MaxHeap =====" << endl;
  cout << "size: " << m_maxHeap->getHeapSize() 
       << " capacity: " << m_maxHeap->getHeapCapacity()
       << endl;

  for(int i = 1; i < m_maxHeap->getHeapSize()+1; i++){
    cout << "Heap[" << i << "] = (";
    m_maxHeap->printValue(i);
    cout << ")" << endl;
  }

  cout << "===== MinHeap =====" << endl;
  cout << "size: " << m_minHeap->getHeapSize()
       << " capacity: " << m_minHeap->getHeapCapacity()
       << endl;

  for(int i = 1; i < m_minHeap->getHeapSize()+1; i++){
    cout << "Heap[" << i << "] = (";
    m_minHeap->printValue(i);
    cout << ")" << endl;
  }
}

// MedianHeap method maxHeapSize
//
template <class T>
int MedianHeap<T>::maxHeapSize() {
  return m_maxHeap->getHeapSize();
}

// MedianHeap method minHeapSize
//
template <class T>
int MedianHeap<T>::minHeapSize() {
  return m_minHeap->getHeapSize();
}

// MedianHeap method locateInMaxHeap
//
template <class T>
T MedianHeap<T>::locateInMaxHeap(int pos) {
  if(m_maxHeap->getHeapSize() < pos)
    throw std::out_of_range("error");
  else
    return (*m_maxHeap)[pos];
}

// MedianHeap method locateInMinHeap
//
template <class T>
T MedianHeap<T>::locateInMinHeap(int pos) {
  if(m_minHeap->getHeapSize() < pos)
    throw std::out_of_range("error");
  else
    return (*m_minHeap)[pos];
}

template <class T>
void MedianHeap<T>::SanityCheck(){

  if(m_size > 0){
    
    if(AbsoluteValueDifference(m_minHeap->getHeapSize(),m_maxHeap->getHeapSize()) > 1){
      
      // take root from minHeap and put into maxHeap
      if(m_minHeap->getHeapSize() > m_maxHeap->getHeapSize()){
	if(m_maxHeap->getHeapSize() <= m_maxHeap->getHeapCapacity()){
	  m_maxHeap->insertHeap(m_minHeap->getRoot(),m_maxHeap->getHeapSize()+1);
	  m_maxHeap->incrementSize();
	  m_maxHeap->PercalateUpMax(m_maxHeap->getHeapSize());
	  m_minHeap->insertHeap(m_minHeap->lastElement(),1);
	  m_minHeap->decrementSize();
	  m_minHeap->PercalateDown(1);
	}
      }
      // take root from maxHeap and put into minHeap
      else{
	if(m_minHeap->getHeapSize() <= m_minHeap->getHeapCapacity()){
          m_minHeap->insertHeap(m_maxHeap->getRoot(),m_minHeap->getHeapSize()+1);
          m_minHeap->incrementSize();
          m_minHeap->PercalateUp(m_minHeap->getHeapSize());
          m_maxHeap->insertHeap(m_maxHeap->lastElement(),1);
          m_maxHeap->decrementSize();
          m_maxHeap->PercalateDownMax(1);
        }
      }
    }
  }

  return;

}

template <class T>
int MedianHeap<T>::AbsoluteValueDifference(int num1, int num2){

  int temp = num1 - num2;

  if(temp < 0)
    temp *= -1;

  return temp;
  
}

//////////////////////////
//                      //
// Heap Implementations //
//                      //
//////////////////////////

// Heap constructor
//
template <class T>
Heap<T>::Heap(int capacity, bool (*lt) (const T&, const T&), bool (*gt) (const T&, const T&)){
  m_heapCapacity = capacity;
  m_heapArray = new T[m_heapCapacity];

  lessThan = lt;
  greaterThan = gt;
}

// Heap deconstructor
//
template <class T>
Heap<T>::~Heap(){
  delete [] m_heapArray;
  m_heapArray = NULL;
  lessThan = NULL;
  greaterThan = NULL;
}

// Heap method getHeapSize
//
template <class T>
int Heap<T>::getHeapSize(){
  return m_heapSize;
}

// Heapmethod getHeapCapacity
//
template <class T>
int Heap<T>::getHeapCapacity(){
  return m_heapCapacity;
}

// Heap method getLeft
//
template <class T>
int Heap<T>::getLeft(const int& pos){
  if(hasLeft(pos))
    return (int)(pos*2);
  else
    return 0;
}

// Heap method getRight
//
template <class T>
int Heap<T>::getRight(const int& pos){
  if(hasRight(pos))
    return (int)((pos*2) + 1);
  else
    return 0;
}

// Heap method getParent
//
template <class T>
T Heap<T>::getParent(const int& pos){
  if(pos != 1)
    return m_heapArray[(int)(pos/2)];
  else
    return m_heapArray[1];
}

// Heap method getRoot
//
template <class T>
T Heap<T>::getRoot(){
  return m_heapArray[1];
}

// Heap method hasLeft
//
template <class T>
bool Heap<T>::hasLeft(const int& pos){
  if(pos*2 <= getHeapSize())
    return true;
  else
    return false;
}

// Heap method hasRight
// 
template <class T>
bool Heap<T>::hasRight(const int& pos){
  if(((pos*2) + 1) <= getHeapSize())
    return true;
  else
    return false;
}

// Heap method isRoot
//
template <class T>
bool Heap<T>::isRoot(const int& pos){
  if(pos == root)
    return true;
  else
    return false;
}

// Overloaded [] operator
//
template <class T>
T& Heap<T>::operator[] (const int& pos) {
  return m_heapArray[pos];
}

// Heap method PercalateUp
//
template <class T>
void Heap<T>::PercalateUp(int pos){
  int parent;
  T temp;

  while(pos != 1){
    parent = (int)(pos/2);

    if(lessThan(m_heapArray[pos], m_heapArray[parent])){
      temp = m_heapArray[parent];
      m_heapArray[parent] = m_heapArray[pos];
      m_heapArray[pos] = temp;

      pos = parent;
    }
    else
      break;
  }
}

// Heap method PercalateDown
//
template <class T>
void Heap<T>::PercalateDown(int pos){

  int child;
  T temp = m_heapArray[pos];

  for(; pos*2 <= getHeapSize(); pos = child){
    child = (int)(pos*2);

    if(child != getHeapSize() && lessThan(m_heapArray[child +1] , m_heapArray[child]))
      child++;

    if(lessThan(m_heapArray[child] , temp))
      m_heapArray[pos] = m_heapArray[child];
    else
      break;
  }

  m_heapArray[pos] = temp;
}

// Heap method PercalateUpMax
//
template <class T>
void Heap<T>::PercalateUpMax(int pos){

  int parent;
  T temp;

  while(pos != 1){
    parent = (int)(pos/2);

    if(greaterThan(m_heapArray[pos], m_heapArray[parent])){
      temp = m_heapArray[parent];
      m_heapArray[parent] = m_heapArray[pos];
      m_heapArray[pos] = temp;

      pos = parent;
    }
    else
      break;
  }
}

// Heap Method PercalateDownMax
//
template <class T>
void Heap<T>::PercalateDownMax(int pos){

  int child;
  T temp = m_heapArray[pos];

  for(; pos*2 <= getHeapSize(); pos = child){
    child = (int)(pos*2);

    if(child != getHeapSize() && greaterThan(m_heapArray[child +1] , m_heapArray[child]))
      child++;

    if(greaterThan(m_heapArray[child] , temp))
      m_heapArray[pos] = m_heapArray[child];
    else
      break;
  }

  m_heapArray[pos] = temp;
}

// Heap method insert
//
template <class T>
void Heap<T>::insertHeap(const T& item , int pos){
  m_heapArray[pos] = item;
}

// Heap method incrementSize
//
template <class T>
void Heap<T>::incrementSize(){
  m_heapSize++;
}

// Heap method decrementSize
//
template <class T>
void Heap<T>::decrementSize(){
  m_heapSize--;
}

// Heap method printValue
//
template <class T>
void Heap<T>::printValue(int pos){
  cout << m_heapArray[pos];
}

// Heap method lastElement
//
template <class T>
T Heap<T>::lastElement(){
  return m_heapArray[m_heapSize];
}

// Heap method getElement
//
template <class T>
T Heap<T>::getElement(int pos){
  return m_heapArray[pos];
}

// Heap method setHeapSize
//
template <class T>
void Heap<T>::setHeapSize(int size){
  m_heapSize = size;
}

#endif
