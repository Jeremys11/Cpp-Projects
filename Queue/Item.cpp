/**********************************************
 ** File:       Item.cpp                              
 ** Project:    CMSC 202 Project 5 Spring 2017         
 ** Author:     Jeremy Singh                            
 ** Date:       5/3/17                                 
 ** Lecture:    16                                      
 ** Discussion: 17                                      
 ** E-mail:     jeremys1@umbc.edu                       
 **                                                     
 ** This file contains the method implementations       
 ** for the Item class                                
 **                                                     
 **                                                     
 ** This file contains the following Item methods:    
 **                                                     
 ** Item default constructor                          
 ** Item overloaded constructor(string,float)           
 ** string GetName                                   
 ** float GetWeight
 **
 ***********************************************/

#include "Item.h"

// Item default constructor
//
Item::Item()
{
  m_name = "NOTHING";
  m_weight = 0;
}

// Item(string,float) overloaded constructor
//
// sets m_name to iName and m_weight to iWeight
//
Item::Item(string iName, float iWeight)
{
  m_name = iName;
  m_weight = iWeight;
}

// Item method GetName()
//
// returns m_name
//
string Item::GetName() const
{
  return m_name;
}

// Item method GetWeight()
//
// returns m_weight
//
float Item::GetWeight() const 
{
  return m_weight;
}
