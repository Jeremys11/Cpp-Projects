/**********************************************                       
 ** File:       ReadyDelivery.cpp
 ** Project:    CMSC 202 Project 5 Spring 2017                        
 ** Author:     Jeremy Singh                                          
 ** Date:       5/3/17                                                
 ** Lecture:    16                                                    
 ** Discussion: 17                                                    
 ** E-mail:     jeremys1@umbc.edu                                     
 **                                                                   
 ** This file contains the method implementations                     
 ** for the ReadyDelivery class
 **                                                                   
 **                                                                   
 ** This file contains the following ReadyDelivery methods:
 **                                                                   
 ** ReadyDelivery default constructor
 ** ReadyDelivery overloaded constructor(string,string,string)
 ** void LoadTruck                                                   
 ** void LoadDelivery
 ** void LoadItem                                  
 ** vector<Truck<Item,MAX_CAPACITY>>& GetTruck
 ** vector<Delivery> GetDelivery
 ** vector<Item> GetItem
 **
 ***********************************************/

#include "ReadyDelivery.h"

// ReadyDelivery Default Constructor
//
ReadyDelivery::ReadyDelivery()
{
  m_truckFile = "proj5_truck_t1.txt";
  m_deliveryFile = "proj5_delivery_t1.txt";
  m_itemFile = "proj5_item_t1.txt";

  LoadTruck();
  LoadItem();
  LoadDelivery();
}


// ReadyDelvery(string,string,string) overloaded constructor
//
ReadyDelivery::ReadyDelivery(string truckFile, string deliveryFile, string itemFile)
{
  m_truckFile = truckFile;
  m_deliveryFile = deliveryFile;
  m_itemFile = itemFile;

  LoadTruck();
  LoadItem();
  LoadDelivery();
}

// ReadyDelivery method LoadTruck
//
// Loads informantion from truck file to create Trucks
// to load into m_truck vector
//
void ReadyDelivery::LoadTruck()
{
  ifstream file(m_truckFile.c_str());

  string truckName;
  int truckNumber;

  while(file >> truckName >> truckNumber)
    {
      Truck<Item,MAX_CAPACITY> temp(truckName,truckNumber);
      m_truck.push_back(temp);
    }

  file.close();
}

// ReadyDelivery method LoadDelivery
//
// Loads information from delivery file to create Deliveries
// to load into m_delivery vector
//
void ReadyDelivery::LoadDelivery()
{
  ifstream file(m_deliveryFile.c_str());

  string customerName;
  int numDeliveryItem;
  int roundTripMinute;

  while(file >> customerName >> numDeliveryItem >> roundTripMinute)
    {
      Delivery temp(customerName,numDeliveryItem,roundTripMinute);
      m_delivery.push_back(temp);
    }

  file.close();
}

// ReadyDelivery method LoadItem
//
// Loads information from item file to create Items
// to load into m_item vector
//
void ReadyDelivery::LoadItem()
{ 
  ifstream file(m_itemFile.c_str());

  string itemName;
  float itemWeight;

  while(file >> itemName >> itemWeight)
    {
      Item temp(itemName,itemWeight);
      m_item.push_back(temp);
    }
}

// ReadyDelivery method GetTruck
//
// returns m_truck
//
vector<Truck<Item, MAX_CAPACITY> >& ReadyDelivery::GetTruck()
{
  return m_truck;
}

// ReadyDelivery method GetDelivery
//
// returns m_delivery
//
vector<Delivery> ReadyDelivery::GetDelivery()
{
  return m_delivery;
}

// ReadyDelivery method GetDelivery
//
// returns m_item
//
vector<Item> ReadyDelivery::GetItem()
{
  return m_item;
}
