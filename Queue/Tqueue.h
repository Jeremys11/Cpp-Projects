/**********************************************
 ** File:       Tqueue.h
 ** Project:    CMSC 202 Project 5 Spring 2017
 ** Author:     Jeremy Singh
 ** Date:       5/3/17
 ** Lecture:    16
 ** Discussion: 17
 ** E-mail:     jeremys1@umbc.edu
 **
 ** This file contains the method declarations and 
 ** implementations for the Tqueue class
 **
 ** This file contains the following Tqueue methods:
 **
 ** Tqueue default constructor
 ** Tqueue copy constructor
 ** Tqueue destructor
 ** void enqueue(T)
 ** void dequeue(T&)
 ** void queueFront(T&)
 ** int isEmpty()
 ** int isFull()
 ** Tqueue overloaded assignment operator
 ** 
 ***********************************************/

#ifndef TQUEUE_H
#define TQUEUE_H

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T, int N> 
class Tqueue {
public:
  //Name: Tqueue - Default Constructor
  //Precondition: None (Must be templated)
  //Postcondition: Creates a queue using dynamic array
  Tqueue(); //Default Constructor
  //Name: Copy Constructor - Not used but required for project 5
  //Precondition: Existing Tqueue
  //Postcondition: Copies an existing Tqueue
  Tqueue( const Tqueue<T,N>& x ); //Copy Constructor
  //Name: Destructor
  //Precondition: Existing Tqueue
  //Postcondition: Destructs existing Tqueue
  ~Tqueue(); //Destructor
  //Name: enqueue
  //Precondition: Existing Tqueue
  //Postcondition: Adds item to back of queue
  void enqueue(T data); //Adds item to queue (to back)
  //Name: dequeue
  //Precondition: Existing Tqueue
  //Postcondition: Removes item from front of queue
  void dequeue(T &); //Removes item from queue (from front)
  //Name: queueFront
  //Precondition: Existing Tqueue
  //Postcondition: Retrieve front (does not remove it)
  void queueFront(T &);    // Retrieve front (does not remove it)
  //Name: isEmpty
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is empty else 0
  int isEmpty(); //Returns 1 if queue is empty else 0
  //Name: isFull
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is full else 0
  int isFull(); //Returns 1 if queue is full else 0
  //Name: Overloaded assignment operator - Not used but required for project 5
  //Precondition: Existing Tqueue
  //Postcondition: Sets one Tqueue to same as a second Tqueue using =
  Tqueue<T,N>& operator=( Tqueue<T,N> y); //Overloaded assignment operator for queue
private:
  T* m_data; //Data of the queue (Must be dynamically allocated array)
  int m_front; //Front of the queue
  int m_back; //Back of the queue
};

/***********************************
*                                  *
*  Tqueue method implementations   *
*                                  *
***********************************/

// Tqueue default constructor
//
template <class T, int N>
  Tqueue<T,N>::Tqueue ()
{
  m_data = new T[N];
  m_front = 0;
  m_back = 0;
}

// Tqueue copy constructor
//
template <class T, int N>
  Tqueue<T,N>::Tqueue( const Tqueue<T,N>& x)
{
  m_data = new T[N];
  for(int i = 0; i < N; i++)
    m_data[i] = x.m_data[i];

  m_front = x.m_front;
  m_back = x.m_back;
}


// Tqueue destructor
//
template <class T, int N>
  Tqueue<T,N>::~Tqueue()
{
  delete[] m_data;
}

// Tqueue method enqueue(T)
//
// if queue is not full, add element
//
template <class T, int N>
  void Tqueue<T,N>::enqueue(T data)
{
  if(!isFull()){ // if queue is not full
    m_data[m_back] = data;
    m_back = ((m_back+1) % N);    
  }
}

// Tqueue method dequeue(T&)
//
// if queue is not empty remove element
//
template <class T, int N>
  void Tqueue<T,N>::dequeue(T &)
{
  if(!isEmpty()){ // If queue is not empty
    m_front = ((m_front+1) % N);
  }
}

// Tqueue method queueFront(T&)
//
// It's supposed to retrieve m_front, but there is no 
// return value so, I don't know what this function
// is supposed to do
//
template <class T, int N>
  void Tqueue<T,N>::queueFront(T& data)
{/* I honestly have no idea what this function does */}

// Tqueue method isEmpty()
//
// Returns 1 if queue is empty
// Returns 0 if queue is not empty
//
template <class T, int N>
  int Tqueue<T,N>::isEmpty()
{
  if(m_back == m_front)
    return 1;
  else
    return 0;
}

// Tqueue method isFull()
//
// Returns 1 if queue is full
// Returns 0 if queue is not full 
//
template <class T, int N>
  int Tqueue<T,N>::isFull()
{
  if((m_back + 1) % N == m_front )
    return 1;
  else
    return 0;
}

// Tqueue overloaded assignment operator
//
template <class T, int N>
  Tqueue<T,N>& Tqueue<T,N>::operator=( Tqueue<T,N> y)
{
  m_data = new T[N];
  for(int i = 0; i < N; i++)
    m_data[i] = y.m_data[i];
    
  m_front = y.m_front;
  m_back = y.m_back;

  return *this;
}



#endif
