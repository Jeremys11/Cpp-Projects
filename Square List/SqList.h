#ifndef _SQLIST_H_
#define _SQLIST_H_

/*****************************************
 ** File:       CBofCB.cpp
 ** Project:    CMSC 341 Project 1, Fall 2017
 ** Author:     Jeremy Singh
 ** Date:       9/26/17
 ** Lecture:    06
 ** E-mail:     jeremys1@umbc.edu
 **
 ** This file contains the method implementations
 ** for the CBofCB class
 **
 **
 ** This file contains the following CBofCB methods:
 **
 ** CBofCB default constructor
 ** CBofCB copy constructor
 ** CBofCB destructor
 ** void enqueue(int)
 ** int dequeue()
 ** bool isFull()
 ** bool isEmpty()
 ** int capacity()
 ** int size()
 ** CBofCB overloaded assignment operator
 ** void dump()
 **
 *******************************************/

#include <list>
#include <math.h>
#include <stdexcept>
#include <iostream>
#include "Int341.h"

using namespace std;

class SqList
{
 public:
  // Default Constructor
  SqList();

  // Copy Constructor
  SqList(const SqList& other);

  // Destructor
  ~SqList();

  // Assignment operator
  const SqList& operator=(const SqList& rhs);

  void consolidate();

  void addFirst(const Int341& x);

  void addLast(const Int341& x);

  Int341 removeFirst();

  Int341 removeLast();

  void add(int pos, const Int341& data);

  Int341 remove(int pos);

  Int341& operator[](int pos);

  int indexOf(const Int341& data);

  int numItems();

  void dump();

  void inspector();
  

 private:

  int m_numItems;
  
  int m_numTopLists;

  list< list<Int341> > L ;

};

#endif
