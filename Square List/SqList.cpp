/*****************************************
 ** File:       SqList.cpp
 ** Project:    CMSC 341 Project 2, Fall 2017
 ** Author:     Jeremy Singh
 ** Date:       10/11/17
 ** Lecture:    06
 ** E-mail:     jeremys1@umbc.edu
 **
 ** This file contains the method implementations
 ** for the SqList class
 **
 **
 ** This file contains the following SqList methods:
 **
 ** SqList default constructor
 ** SqList copy constructor
 ** SqList assignment operator
 ** SqList destructor
 ** void consolidate
 ** void addFirst 
 ** void addLast
 ** Int341 removeFirst
 ** Int341 removeLast
 ** void add
 ** Int341 remove
 ** SqList  [] operator
 ** int indexOf
 ** void dump
 **
 *******************************************/


#include "SqList.h"

// Default Constructor
// 
SqList::SqList(){
  m_numItems = 0;
  list<Int341> temp;
  L.push_front(temp);
}

// Copy Constructor
//
SqList::SqList(const SqList& other)
{
  m_numItems = other.m_numItems;

  list< list<Int341> >::iterator it;
  list<Int341>::iterator itr;

  list< list<Int341> > tempLst = other.L;
  
  for(it = tempLst.begin(); it != tempLst.end(); ++it){
    list<Int341> temp;
    L.push_back(temp);
    for(itr = it->begin(); itr != it->end(); ++itr){
      L.back().push_back(*itr);
    }
  }  
  
}

// Assignment Operator
//
const SqList& SqList::operator=(const SqList& rhs)
{
  L.clear();
  m_numItems = 0;
  m_numItems = rhs.m_numItems;

  list< list<Int341> >::iterator it;
  list<Int341>::iterator itr;

  list< list<Int341> > tempLst = rhs.L;
  
  for(it = tempLst.begin(); it != tempLst.end(); ++it){
    list<Int341> temp;
    L.push_back(temp);
    for(itr = it->begin(); itr != it->end(); ++itr){
      L.back().push_back(*itr);
    }
  }

  return *this;
}

// Destructor
//
SqList::~SqList()
{/* NO CODE */}

// SqList method consolidate
//
// Merges short lists together and 
// Splits long lists
// Removal of empty lists after removal
// of items handled in the various remove
// functions
//
void SqList::consolidate()
{
  list< list<Int341> >::iterator it;
  list<Int341>::iterator itr;
  list<Int341> temp;

  double big = 2*sqrt(m_numItems);
  double small = sqrt(m_numItems) / 2;
  int half;

  bool prevIsShort = false ;
  bool currIsShort = false;

  
  // Merge short lists
  it = L.begin();
  while(it != L.end())
    {
      if(it->size() < small){
	currIsShort = true;
      }
      else
	currIsShort = false;
      if(currIsShort && prevIsShort){
	itr = it->begin();
	it->splice(itr,temp);
	it--;
	it = L.erase(it);
	temp.clear();
	currIsShort = false;
	prevIsShort = false;
      }
      else{
	if(currIsShort){
	  temp = *it;
	  currIsShort = false;
	  prevIsShort = true;
	}
	else{
	  currIsShort = false;
	  prevIsShort = false;
	}
	it++;
      }
    }


  // Split long list
  it = L.begin();
  while(it != L.end()){
    if(it->size() > big){
      list<Int341> temp;
      half = it->size() / 2;
      itr = it->begin();
      advance(itr,half);
      temp.splice(temp.begin(), *it, it->begin(), itr);
      L.insert(it++,temp);
    }
    ++it;
  }  
}

// SqList method addFirst
//
// Adds item to first list in list of lists
// in the first position
//
void SqList::addFirst(const Int341& x){
  L.front().push_front(x);
  m_numItems++;
  consolidate();
}

// SqList method addLast
//
// Adds item to last list in list of lists
// in the last position
//
void SqList::addLast(const Int341& x){
  L.back().push_back(x);
  m_numItems++;
  consolidate();
}

// SqList method removeFirst
//
// Removes item from first list in list of lists
// in the first position
//
Int341 SqList::removeFirst(){

  Int341 erasedValue;

  if(m_numItems > 0){
    erasedValue = L.front().front();
    L.front().pop_front();
    m_numItems--;
    if(L.front().size() == 0){
      L.pop_front();
    }
    else
      consolidate();
  }
  else
    throw std::out_of_range("error");

  return(erasedValue);
}

// SqList method removeLast
//
// Removes item from last list in list of lists
// in the last position
//
Int341 SqList::removeLast(){

  Int341 erasedValue;

  if(m_numItems > 0){
    erasedValue = L.back().back();
    L.back().pop_back();
    m_numItems--;
    if(L.back().size() == 0){  
      L.pop_back();
    }
    else
      consolidate();
  }
  else
    throw std::out_of_range("error");

  return(erasedValue);
}

// SqList method add
//
// Adds data to position before the item already
// in the given position
//
void SqList::add(int pos, const Int341& data)
{
  if(pos < m_numItems && pos >= 0){
    list< list<Int341> >::iterator it;
    list<Int341>::iterator itr;
    unsigned int curItem = 0;
    unsigned int position = pos;
    
    for(it = L.begin(); it != L.end(); ++it){
      if(curItem + it->size() > position){
        for(itr = it->begin(); itr != it->end(); ++itr){
          if(curItem == position){
            it->insert(itr,data);
	  }
	  curItem++;
	}
      }
      else
	curItem += it->size();
    }
  }
    else
      throw std::out_of_range("error");

  m_numItems++;

  consolidate();
}

// SqList method remove
//
// Removes item from given postion and deletes
// list if that was the last element
//
Int341 SqList::remove(int pos)
{
  Int341 erasedValue;

  if(pos < m_numItems && pos >= 0){
    list< list<Int341> >::iterator it;
    list<Int341>::iterator itr;
    unsigned int curItem = 0;
    unsigned int position = pos;

    for(it = L.begin(); it != L.end(); ++it){
      if(curItem + it->size() > position){
        for(itr = it->begin(); itr != it->end(); ++itr){
          if(curItem == position){
            erasedValue = *itr;
	    it->erase(itr);
	    m_numItems--;
	    if(it->size() == 0 && L.size() > 1)
	      L.erase(it);
	    else
	      consolidate();
	    return(erasedValue);
	  }
          curItem++;
        }
      }
      else
        curItem += it->size();
    }
  }
  else
    throw std::out_of_range("error");


  consolidate();

  return(erasedValue);
}

// SqList operator []
// 
// Returns Int341 object in the overall
// position instead of the position from
// any particular list
//
Int341& SqList::operator[](int pos)
{
  list< list<Int341> >::iterator it;
  list<Int341>::iterator itr;
  unsigned int curItem = 0;
  unsigned int position = pos;

  if(pos < m_numItems && pos >= 0){
    for(it = L.begin(); it != L.end(); ++it){
      if(curItem + it->size() > position){
	for(itr = it->begin(); itr != it->end(); ++itr){
	  if(curItem == position)
	    return(*itr);
	  curItem++;
	}
      }
      else
	curItem += it->size();  
    }
  }
  else
    throw std::out_of_range("error");

  return *itr;
}

// SqList method indexOf
//
// Finds the first instance of the number given
// and returns its position. If not, there, returns
// -1
//
int SqList::indexOf(const Int341& data)
{
  list< list<Int341> >::iterator it;
  list<Int341>::iterator itr;
  int curItem = 0;
  int numNotFound = -1;

  for(it = L.begin(); it != L.end(); ++it){
    for(itr = it->begin(); itr != it->end(); ++itr){
      if(itr->m_data == data.m_data)
	return(curItem);
      curItem++;
    }
  }
  return(numNotFound);
}

// SqList method numItems
//
// Returns total number of Int341 in the list 
// of lists
//
int SqList::numItems(){
  return m_numItems;
}

// SqList method dump
//
// Prints out content of list of lists
// Used for debugging
//
void SqList::dump()
{
  list< list<Int341> >::iterator it;
  list<Int341>::iterator itr;
  int curList = 0;

  for(it = L.begin(); it != L.end(); ++it){
    cout << curList << ' ' << '(' << it->size() << ')' << ' ' << ':' << ' ';
    curList++;
    for(itr = it->begin(); itr != it->end(); ++itr){
      cout << itr->m_data << ' ';
    }
    cout << endl;
  }
}

