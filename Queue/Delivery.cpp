/**********************************************           
 ** File:       Delivery.cpp
 ** Project:    CMSC 202 Project 5 Spring 2017            
 ** Author:     Jeremy Singh                              
 ** Date:       5/3/17                                    
 ** Lecture:    16                                        
 ** Discussion: 17                                        
 ** E-mail:     jeremys1@umbc.edu                         
 **                                                       
 ** This file contains the method implementations         
 ** for the Delivery class         
 **                                                       
 **                                                       
 ** This file contains the following Delivery methods:   
 **                                                       
 ** Delivery default constructor
 ** Delivery overloaded constructor(string,int,int)
 ** string GetName                                        
 ** int GetNumItem         
 ** int GetRTMinute                                      
 **
 ***********************************************/


#include "Delivery.h"

// Delivery default Constructor
//
Delivery::Delivery()
{
  m_name  = "Nothing";
  m_numItem = 0;
  m_rtMinute = 0;
}

// Delivery(string,int,int) overloaded constructor
//
Delivery::Delivery(string name, int numItem, int rtMinute)
{
  m_name = name;
  m_numItem = numItem;
  m_rtMinute = rtMinute;
}

// Delivery method GetName
//
// returns m_name
//
string Delivery::GetName() const 
{
  return m_name;
}

// Delivery method m_numItem
//
// returns m_numItem
//
int Delivery::GetNumItem() const 
{
  return m_numItem;
}

// Delivery method GetRTMinute
//
// returns m_rtMinute
//
int Delivery::GetRTMinute() const 
{
  return m_rtMinute;
}
