/**********************************************
 ** File:       Truck.h
 ** Project:    CMSC 202 Project 5 Spring 2017
 ** Author:     Jeremy Singh
 ** Date:       5/3/17
 ** Lecture:    16
 ** Discussion: 17
 ** E-mail:     jeremys1@umbc.edu
 **
 ** This file contains the method declarations and
 ** implementations for the Truck class
 **
 **
 ** This file contains the following Tqueue methods:
 **
 ** Truck overloaded constructor(string,int)
 ** Truck destructor
 ** Tqueue<T,N> GetItem()
 ** void AddItem(T&)
 ** void DeliverItemFromTruck()
 ** void AddDelivery(Delivery&)
 ** void CompleteDelivery()
 ** Delivery& GetDeliveryAt(int)
 ** vector<Delivery> GetDelivery()
 ** int GetTime()
 ** void SetTime(int)
 ** double GetCapacity()
 ** string GetName()
 **
 ***********************************************/

#ifndef TRUCK_H
#define TRUCK_H

#include "Item.h"
#include "Tqueue.h"
#include "Delivery.h"

#include <vector>

using namespace std;

template <class T, int N>
class Truck {
 public:
  //Name: Truck(string, int) Overloaded constructor.
  //Precondition: Requires truck file has been loaded
  //Postcondition: Builds a new templated truck
  Truck(string inName, int capacity);

  //Name: Destructor
  //Precondition: Requires truck file has been loaded
  //Postcondition: Destroys everything in truck
  ~Truck();

  //Name: GetItem (optional)
  //Precondition: Requires that the truck's item queue has been populated
  //Postcondition: Templated accessor for this truck's cargo
  Tqueue<T,N> GetItem() const;

  /*
  //Name: GetItemAt (optional)
  //Precondition: Requires that the truck's item queue has been populated
  //Postcondition: Templated accessor for this truck's cargo at a specific location
  const T& GetItemAt(int index) const;
  */

  //Name: AddItem (optional)
  //Precondition: Requires that the trucks have been loaded
  //Postcondition: Adds item into this truck
  void AddItem(T& inputObject);

  //Name: DeliverItemFromTruck (optional)
  //Precondition: Requires that the trucks have been loaded
  //Postcondition: Delivers item from this truck to customer
  void DeliverItemFromTruck();  

  //Name: AddDelivery (optional)
  //Precondition: Requires that all deliveries have been input and trucks
  //Postcondition: Used to add deliveries for specific trucks
  void AddDelivery(Delivery&);

  //Name: CompleteDelivery (optional)
  //Precondition: Requires that deliveries have been assigned to this truck
  //Postcondition: Removes current deliveries from this truck
  void CompleteDelivery();

  //Name: GetDeliveryAt (optional)
  //Precondition: Requires that this truck has at least 1 delivery assigned to it
  //Postcondition: Used to return a specific delivery
  Delivery& GetDeliveryAt(int index);

  //Name: GetDelivery (optional)
  //Precondition: Requires deliveries have been asssigned to this truck
  //Postcondition: Used to return the entire vector of deliveries
  vector<Delivery> GetDelivery() const;
 
  //Name: GetTime (optional)
  //Precondition: None
  //Postcondition: Used to return current time for a specific truck
  int GetTime(); 

  //Name: SetTime (optional)
  //Precondition: None
  //Postcondition: Used to set time for a specific truck
  void SetTime(int time);

  //Name: GetCapacity (optional)
  //Precondition: Requires that the trucks have been loaded
  //Postcondition: Used to access the capacity of a truck
  double GetCapacity() const;

  //Name: GetName (optional)
  //Precondition: Requires that the trucks have been loaded
  //Postcondition: Used to access the name of a truck
  string GetName() const;

private:
  string m_name;
  int m_capacity;
  int m_time;
  vector<Delivery> m_curDelivery;
  Tqueue<T,N> m_item;
};
/*******************************************
*                                          *          
*    Truck class mehod implementations     *
*                                          *
*******************************************/

// Truck(string,int) overloaded constructor
//
template<class T, int N>
  Truck<T,N>::Truck(string inName, int capacity)
{
  m_name = inName;
  m_capacity = capacity;
  m_time = 0;
}

// Truck destructor
//
template<class T, int N>
  Truck<T,N>::~Truck()
{
  // No more itmes in truck or deliveries
  // since those were removed in ManageDeliveries

  // No dynamic memory allocation
}

// Truck method GetItem()
//
// returns m_item
//
template<class T, int N>
  Tqueue<T,N> Truck<T,N>::GetItem() const 
{
  return m_item;
}

/*
// Truck method GetItemAt(int)
//
template<class T, int N>
  const T& Truck<T,N>::GetItemAt(int index) const {}
*/

// Truck method AddItem(T& inputObject)
//
// calls Tqueue method enqueue
//
template<class T, int N>
  void Truck<T,N>::AddItem(T& inputObject) 
{
  m_item.enqueue(inputObject);
}


// Truck method DeliverItemFromTruck()
//
// Calls Tqueue method dequeue
//
template<class T, int N>
  void Truck<T,N>::DeliverItemFromTruck()
{
  Item temp;
  m_item.dequeue(temp);
}


// Truck method AddDelivery(Delivery&)
//
// Adds someDelivery to m_curDelivery
//
template<class T, int N>
  void Truck<T,N>::AddDelivery(Delivery& someDelivery)
{
  m_curDelivery.push_back(someDelivery);
}

// Truck method CompleteDelivery()
//
// Emptues m_curDelivery
//
template<class T, int N>
  void Truck<T,N>::CompleteDelivery()
{
  m_curDelivery.clear();
}

// Truck method GetDeliveryAt(int)
//
// returns delivery in m_curDelivery[index]
//
template<class T, int N>
  Delivery& Truck<T,N>::GetDeliveryAt(int index)
{
  return m_curDelivery[index];
}

// Truck method GetDelivery()
//
// returns m_curDelivery
//
template<class T, int N>
  vector<Delivery> Truck<T,N>::GetDelivery() const 
{
  return m_curDelivery;
}

// Truck method GetTime()
//
// returns m_time
//
template<class T, int N>
  int Truck<T,N>::GetTime()
{
  return m_time;
}

// Truck method SetTime(int)
//
// sets m_time to time
//
template<class T, int N>
  void Truck<T,N>::SetTime(int time)
{
  m_time = time;
}

// Truck method GetCapacity()
//
// returns m_capacity
//
template<class T, int N>
  double Truck<T,N>::GetCapacity() const 
{
  return m_capacity;
}

// Truck method GetName()
//
// returns m_name
//
template<class T, int N>
  string Truck<T,N>::GetName() const 
{
  return m_name;
}

#endif
