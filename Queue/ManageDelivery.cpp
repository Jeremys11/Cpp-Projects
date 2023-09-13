/**********************************************
 ** File:       ManageDelivery.cpp
 ** Project:    CMSC 202 Project 5 Spring 2017
 ** Author:     Jeremy Singh
 ** Date:       5/3/17
 ** Lecture:    16
 ** Discussion: 17
 ** E-mail:     jeremys1@umbc.edu
 **
 ** This file contains the method implementations
 ** for the ManageDelivery class
 **
 **
 ** This file contains the following ManageDelivery methods:
 **
 ** ManageDelivery overloaded constructor(vector<Truck<Item,MAX_CAPACITY>>, vector<Delivery>, vector<Item>)
 ** void StartDelivery()
 ** void DeliverItem(int)
 ** void DisplayItemLeft()
 **
 ***********************************************/

#include "ManageDelivery.h"

// ManageDelivery(vector<Truck>,vector<Delivery>,vector<Item>) overloaded 
// constructor
//
ManageDelivery::ManageDelivery(vector< Truck<Item, MAX_CAPACITY> > truck, vector< Delivery > delivery, vector< Item > item)
{
  m_truck = truck;
  m_delivery = delivery;
  m_item = item;

  int truckSize = (int) m_truck.size();
  int deliverySize = (int) m_delivery.size();
  int itemSize = (int) m_item.size();

  cout << "Trucks Loaded: " << truckSize << endl
       << "Deliveries Loaded: " << deliverySize << endl
       << "Items Loaded: " << itemSize << endl
       << "Start Time: 0" << endl << endl; 

  StartDelivery();

  DisplayItemLeft();
}

// ManageDelivery method StartDelivery()
//
// Loads trucks with items and deliveries until there are not more
// deliveries to be loaded and delivered
//
void ManageDelivery::StartDelivery()
{
  // Sizes for the truck and delivery vectors
  int truckSize = (int) m_truck.size();
  int deliverySize = (int) m_delivery.size();  

  // Adding items and deliveries to Truck
  int truckCounter = 0; // Keeps count of current truck

  int tempDeliveryCounter = 0; // Iterates through tempDelivery
  vector<Delivery> tempDelivery; // Vector to hold deliveries for truck

  int itemsToLoad = 0; // Amount of items to load

  for(int i = 0; i < deliverySize; i++)
    {
      // Adds items to truck and deliveries to truck
      if(itemsToLoad + m_delivery[i].GetNumItem() > m_truck[truckCounter].GetCapacity())
	{
	  // Loading Items
	  cout << "*****Loading Truck (" << truckCounter+1 << ")*****" << endl;
	  for(int j = 0; j < itemsToLoad; j++)
	    {
	      cout << m_item.front().GetName() << " loaded into Truck" << truckCounter+1 << endl;
	      m_truck[truckCounter].AddItem(m_item.front());
	      m_item.erase(m_item.begin());
	    }
	  cout << endl;

	  // Loading Deliveries
	  int tempDeliverySize = (int) tempDelivery.size();

	  while(tempDeliveryCounter != tempDeliverySize)
	    {
	      m_truck[truckCounter].AddDelivery(tempDelivery[tempDeliveryCounter]);
	      tempDeliveryCounter++;
	    }
	  
	  // Reseting deliverCounter, tempDelivery, tempDeliverySize, and truckDeliverySize 
	  tempDelivery.clear();
	  tempDeliverySize = 0;
	  tempDeliveryCounter = 0;
	  itemsToLoad = 0;
	  
	  // Adding m_delivery[i] to vector to be delivered by
	  // the next available truck
	  itemsToLoad += m_delivery[i].GetNumItem();
	  tempDelivery.push_back(m_delivery[i]);
    
	  DeliverItem(truckCounter); // Delivers items in truck
	  truckCounter = ((truckCounter+1) % truckSize); // Iterate current truck
	}

      // Adding deliveries into temporary vector to add to truck
      else
	{
	  tempDelivery.push_back(m_delivery[i]);
	  itemsToLoad += m_delivery[i].GetNumItem();
	}
    }
  
  // Delivers the rest of deliveries if there are any left over
  if(!m_item.empty())
    {
      // Loading items
      cout << "*****Loading Truck (" << truckCounter+1 << ")*****" << endl;
      for(int j = 0; j < itemsToLoad; j++)
	{
	  cout << m_item.front().GetName() << " loaded into Truck" << truckCounter+1 << endl;
	  m_truck[truckCounter].AddItem(m_item.front());
	  m_item.erase(m_item.begin());
	}
      cout << endl;

      // Loading Deliveries
      int tempDeliverySize = (int) tempDelivery.size();

      while(tempDeliveryCounter != tempDeliverySize)
	{
	  m_truck[truckCounter].AddDelivery(tempDelivery[tempDeliveryCounter]);
	  tempDeliveryCounter++;
	}

      DeliverItem(truckCounter); // Starting Deliveries
    }
}

// ManageDelivery method DeliverItem(int)
//
// Takes an (int) that corresponds the the truck number
// in the m_truck vector
//
// Delivers the items and shows how many items were delivered,
// how long the deliveries took, and who the deliveries were for
//
// Empties the truck of items and deliveries afterwards
// 
void ManageDelivery::DeliverItem(int j)
{
  int numberOfDeliveries = (int) m_truck[j].GetDelivery().size();

  int numberOfItems = 0;
  for(int i = 0; i < numberOfDeliveries; i++)
    numberOfItems += m_truck[j].GetDeliveryAt(i).GetNumItem();
    
  // Adding time for truck to be loaded
  int standardLoadingTime = 10;
  m_truck[j].SetTime(m_truck[j].GetTime() + standardLoadingTime); 

  cout << "**Truck Name: Truck " << j+1 << "**" << endl;
  for(int i = 0; i < numberOfDeliveries; i++){

    m_truck[j].SetTime(m_truck[j].GetTime() + m_truck[j].GetDelivery()[i].GetRTMinute()); // Adding time for this delivery to total delivery time
    
    cout << "***********Delivery " << i+1 << "***********" << endl
	 << "DeliveryTime: " << m_truck[j].GetTime() << endl
	 << "Delivery for: " << (m_truck[j].GetDelivery())[i].GetName() << endl 
	 << "Delivered: " << m_truck[j].GetDeliveryAt(i).GetNumItem()
	 << endl;
  }
  cout << endl;

  // Removing Items from truck
  for(int i = 0; i < numberOfItems; i++)
    m_truck[j].DeliverItemFromTruck();

  m_truck[j].CompleteDelivery(); // Removing delivereis from truck
}

// ManageDelivery method DispalyItemLeft()
//
// Prints out all of the items that were loaded
// but not delivered
//
void ManageDelivery::DisplayItemLeft()
{
  int itemSize = (int) m_item.size();

  cout << "*****Items Left After Deliveries*****" << endl;
  if(itemSize > 0){
    for(int i = 0; i < itemSize; i++){
      cout << "Item " << i+1 << ' ' << "- Name: " << m_item[i].GetName()
	   << ' ' << "- Weight: " << m_item[i].GetWeight() << endl;
    }
  }
  else
    cout << "No remaining items" << endl;
}
