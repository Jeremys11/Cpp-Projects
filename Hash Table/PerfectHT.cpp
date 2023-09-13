// File: PerfectHT.cpp
//
// UMBC CMSC 341 Fall 2017 Project 5
//
// Implementation of HashFunction, SecondaryHT & PerfectHT classes.
//
// Version: 2017-11-30
//

#include <stdexcept>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std ;

#include "PerfectHT.h"
#include "primes.h"


// =====================================================================
// HashFunction class implementation 
// =====================================================================


// By default do not print info to screen
//
bool HashFunction::m_debug = false ;


// Constructor.
// The constructor picks the smallest prime # greater than
// or equal to n for the table size. 
// Default value of n defined in header.
//  
// Initializes other hash function parameters randomly.
//
HashFunction::HashFunction(int n /* =100*/ ) {

   // note: maxPrime defined in prime.h
   //
   if (n > maxPrime) throw out_of_range("HashTable size too big.\n") ;

   m_tsize = findPrime(n) ;
   m_factor = ( rand() % (m_tsize - 1) ) + 1 ;
   m_shift =  rand() % m_tsize ;
   m_multiplier = 33 ;  // magic number from textbook
   m_reboots = 0 ;

}


// Function that maps string to unsigned int.
// Return value can be much larger than table size.
// Uses m_multiplier data member.
// Return value must be unsgined for overflow to work correctly.
//
unsigned int HashFunction::hashCode(const char *str) const {

   unsigned int val = 0 ; 

   int i = 0 ;
   while (str[i] != '\0') {
      val = val * m_multiplier + str[i] ;
      i++ ;
   }
   return val ; 
}


// Getter for table size
//
int HashFunction::tableSize() const {
   return m_tsize ;
}


// Overloaded () operator that makes this a "functor" class.
// Returns the slot in the hash table for str.
// Uses the MAD method: h(x) = (ax + b) % m where 
// the parameters are:
//   a = m_factor
//   b = m_shift
//   m = m_tsize
//
unsigned int HashFunction::operator() (const char *str) const {
   return ( m_factor * hashCode(str) + m_shift ) % m_tsize ;
}


// Pick new parameters for MAD method and the hashCode function.
// Note: can change table size.
//
void  HashFunction::reboot() {

  m_reboots++;

  int tempFactor = m_factor;
  int tempShift = m_shift;

  // changing multiplier
  if(m_reboots % 3 == 0)
    m_multiplier += 2;
  
  // changing table size
  if(m_reboots % 5 == 0)
    m_tsize = findPrime(m_tsize+1) ;
  
  // changing factor and shift
  while (tempFactor == m_factor)
    m_factor = ( rand() % (m_tsize - 1) ) + 1 ;
  while (tempShift == m_shift)
    m_shift =  rand() % m_tsize ;

  if(HashFunction::m_debug == true){
    cout << "Reboot " << m_reboots << endl 
	 << "m_tsize = " << m_tsize << endl
	 << "m_multiplier = " << m_multiplier << endl
	 << "m_factor = " << m_factor << endl
	 << "m_shift = " << m_shift << endl
	 << endl;
  }
}


// Set random seed for the random number generator.
// Call once at the start of the main program.
// Uses srand() and rand() from cstdlib which is
// shared with other code. For compatibility with
// C++98, it does not have a private random number 
// generator (e.g., mt19337).
//
void HashFunction::setSeed(unsigned int seed) {
   srand(seed) ;
}

// Find the smallest prime number greater than or equal to m.  

int HashFunction::findPrime(int m) {

  if (m > maxPrime) throw out_of_range("HashTable size too big.\n") ;

  // if one or two - return first element so not to get segment fault
  if(m == 1 || m == 2)
    return primes[0];

  int mid;
  int low = 0;
  int high = numPrimes - 1;

  while(low <= high){
    mid = (low + high) / 2;
    if( (primes[mid] >= m) && (primes[mid-1] < m))
      return primes[mid];
    else if((primes[mid] > m) && (primes[mid-1] > m))
      high = mid - 1;
    else
      low = mid + 1;;
  }
}

//
// STUDENT FUNCTION
//
// HashFunction method copyStats
//
// Used in SHT and PHT copy constructor and assignment operator to copy stats for 'hash' member variable
void HashFunction::copyStats(unsigned int size, unsigned int reboots, unsigned int multiplier, unsigned int factor, unsigned int shift){
  m_tsize = size;
  m_reboots = reboots;
  m_multiplier = multiplier;
  m_factor = factor;
  m_shift = shift;
}

// HashFunction method getReboots
//
unsigned int HashFunction::getReboots() const {
  return m_reboots;
}

// HashFunction method getMultiplier
//
unsigned int HashFunction::getMultiplier() const {
  return m_multiplier;
}

// HashFunction method getFactor
//
unsigned int HashFunction::getFactor() const {
  return m_factor;
}

// HashFunction method getShift
//
unsigned int HashFunction::getShift() const {
  return m_shift;
}

//
// END
//


// =====================================================================
// SecondaryHT class implementation 
// =====================================================================


// By default do not print debugging info 
bool SecondaryHT::m_debug = false ;


// Create a secondary hash table using the char * strings
// stored in "words". Makes copy of each item in words.
//
SecondaryHT::SecondaryHT(vector<const char *> words) : hash(words.size()*words.size()){
  
  // initializing member variables
  m_attempts = 1;
  m_size = 0;

  // dynamic temporary array
  int wordSize = words.size();
  int* tempArray = new int[hash.tableSize()];
  for(int j = 0; j < hash.tableSize(); j++)
    tempArray[j] = 0;
  
  // loop to check if we can create perfect hash table
  int i = 0;
  while(i != wordSize){
    if(tempArray[hash(words[i])] == 0){
      tempArray[hash(words[i])] = 1;
      i++;
    }
    else{
      i = 0;
      //m_attempts++;

      // deleting and resizing temporary array
      delete[] tempArray;
      tempArray = NULL;
      
      hash.reboot();
      if(m_attempts < maxAttempts){
	m_attempts++;
	tempArray = new int[hash.tableSize()];
	for(int j = 0; j < hash.tableSize(); j++)
	  tempArray[j] = 0;
      }
      else
	throw very_unlucky("error");
    }
  }
  
  // deleting temporary array

  delete[] tempArray;
  tempArray = NULL;

  // creating array for perfect table
  T2 = new char*[hash.tableSize()];
  for(int j = 0; j < hash.tableSize(); j++)
    T2[j] = NULL;

  // filling array
  i = 0;
  while(i != wordSize){
    T2[hash(words[i])] = strdup(words[i]);
    m_size++;
    i++;
  }
}


// Copy constructor. Remember to strdup.
//
SecondaryHT::SecondaryHT(const SecondaryHT& other) {

  m_size = other.m_size;
  m_attempts = other.m_attempts;

  hash.copyStats(other.hash.tableSize(), other.hash.getReboots(), other.hash.getMultiplier(), other.hash.getFactor(), other.hash.getShift());

  T2 = new char*[hash.tableSize()];
  for(int j = 0; j < hash.tableSize(); j++)
    T2[j] = NULL;

  int i = 0;
  while(i != hash.tableSize()){
    if(other.T2[i] != NULL)
      T2[i] = strdup(other.T2[i]);
    i++;
  }
}


// Destructor. Use free() to free strings.
//
SecondaryHT::~SecondaryHT() {

  for(int i = 0; i < hash.tableSize(); i++){
    free(T2[i]);
    T2[i] = NULL;
  }
  delete[] T2;
  T2 = NULL;
}


// Assignment operator. Remember to use strdup() and free()
//
const SecondaryHT& SecondaryHT::operator=(const SecondaryHT& rhs)  {

  m_size = rhs.m_size;
  m_attempts = rhs.m_attempts;;

  // deleting
  for(int i = 0; i < hash.tableSize(); i++){
    if(T2[i] != NULL)
      free(T2[i]);
    T2[i] = NULL;
  }
  delete[] T2;
  T2 = NULL;

  // assigning
  hash.copyStats(rhs.hash.tableSize(), rhs.hash.getReboots(), rhs.hash.getMultiplier(), rhs.hash.getFactor(), rhs.hash.getShift());

  T2 = new char*[rhs.hash.tableSize()];
  for(int i = 0; i < rhs.hash.tableSize(); i++)
    T2[i] = NULL;

  int i = 0;
  while(i != rhs.hash.tableSize()){
    if(rhs.T2[i] != NULL)
      T2[i] = strdup(rhs.T2[i]);
    i++;
  }
  
  return *this;
}


// returns whether given word is in this hash table.
//
bool SecondaryHT::isMember (const char *word) const {

   int slot = hash(word) ;

   assert ( 0 <= slot && slot < hash.tableSize() ) ;

   if (T2[slot] == NULL) return false ;

   if ( strcmp(word, T2[slot]) != 0 ) return false ;

   return true ; 
}


// getter. Actually, the hash function has the size.
//
int SecondaryHT::tableSize() const {
   return hash.tableSize() ;
}


// Pretty print for debugging
//
void SecondaryHT::dump() const {
   cout << "=== Secondary Hash Table Dump: ===\n" ;
   cout << "Table size = " << hash.tableSize() << endl ;
   cout << "# of items = " << m_size << endl ;
   cout << "# of attempts = " << m_attempts << endl ;
 
   for (int i=0 ; i < hash.tableSize() ; i++) {
      cout << "T2[" << i << "] = " ;
      if (T2[i] != NULL) cout << T2[i] ;
      cout << endl ;
   }

   cout << "==================================\n" ;
}



// =====================================================================
// PerfectHT class implementation 
// =====================================================================


// by default, do not print debugging info
//
bool PerfectHT::m_debug = false ;


// Create a Perfect Hashing table using the first n strings 
// from the words array.
//
PerfectHT::PerfectHT (const char *words[], int n) : hash(n) {

  PHT1 = new char*[hash.tableSize()];
  PHT2 = new SecondaryHT*[hash.tableSize()];
  vector<const char *> *hold = new vector<const char *>[hash.tableSize()] ;
  for(int i = 0; i < hash.tableSize(); i++){
    PHT1[i] = NULL;
    PHT2[i] = NULL;
  }

  // putting everything in hold
  for(int i = 0; i < n; i++)
    hold[hash(words[i])].push_back(words[i]);

  // if hold[i] only has one element - put in PHT1
  for(int i = 0; i < hash.tableSize(); i++){
    if(hold[i].size() == 1){
      PHT1[i] = strdup(hold[i].back());
      hold[i].pop_back();
    }
  }

  // allocating memory and assigning for indecies
  for(int i = 0; i < hash.tableSize(); i++){
    if(PHT2[i] == NULL && hold[i].size() > 0)
      PHT2[i] = new SecondaryHT(hold[i]);
  }

  delete [] hold;     
}


// Copy constructor. Use strdup or SecondaryHT copy constructor.
//
PerfectHT::PerfectHT(const PerfectHT& other) {

  PHT1 = new char*[other.hash.tableSize()];
  PHT2 = new SecondaryHT*[other.hash.tableSize()];
  for(int i = 0; i < other.hash.tableSize(); i++){
    PHT1[i] = NULL;
    PHT2[i] = NULL;
  }

  hash.copyStats(other.hash.tableSize(), other.hash.getReboots(), other.hash.getMultiplier(), other.hash.getFactor(), other.hash.getShift());

  for(int i = 0; i < other.hash.tableSize(); i++){
    if(other.PHT1[i] != NULL)
      PHT1[i] = strdup(other.PHT1[i]);
  }

  for(int i = 0; i < other.hash.tableSize(); i++){
    if(other.PHT2[i] != NULL)
      (PHT2[i]) = new SecondaryHT (*(other.PHT2[i]));
  }
}


// Destructor. Remember to use free() for strdup-ed strings.
//
PerfectHT::~PerfectHT() {
  
  for(int i = 0; i < hash.tableSize(); i++){
    if(PHT1[i] != NULL)
      free(PHT1[i]);
    PHT1[i] = NULL;
    if(PHT2[i] != NULL)
      delete PHT2[i];
    PHT2[i] = NULL;
    
  }
  delete[] PHT1;
  delete[] PHT2;
  PHT1 = NULL;
  PHT2 = NULL;
}


// Assignment operator. Use strdup() and free() for strings.
//
const PerfectHT& PerfectHT::operator=(const PerfectHT& rhs) {

  for(int i = 0; i < hash.tableSize(); i++){
    if(PHT1[i] != NULL)
      free(PHT1[i]);
    PHT1[i] = NULL;
    
    if(PHT2[i] != NULL)
      delete PHT2[i];
    PHT2[i] = NULL;
  }
  delete[] PHT1;
  delete[] PHT2;
  PHT1 = NULL;
  PHT2 = NULL;
  

  PHT1 = new char*[rhs.hash.tableSize()];
  PHT2 = new SecondaryHT*[rhs.hash.tableSize()];
  for(int i = 0; i < rhs.hash.tableSize(); i++){
    PHT1[i] = NULL;
    PHT2[i] = NULL;
  }

  hash.copyStats(rhs.hash.tableSize(), rhs.hash.getReboots(), rhs.hash.getMultiplier(), rhs.hash.getFactor(), rhs.hash.getShift());

  for(int i = 0; i < hash.tableSize(); i++){
    if(rhs.PHT1[i] != NULL)
      PHT1[i] = strdup(rhs.PHT1[i]);
  }

  for(int i = 0; i < hash.tableSize(); i++){
    if(rhs.PHT2[i] != NULL)
      (PHT2[i]) = new SecondaryHT (*(rhs.PHT2[i]));
  }

  return *this;
}


// Returns whether word is stored in this hash table.
//
bool PerfectHT::isMember(const char * str) const {
   int slot = hash(str) ; 

   if (PHT1[slot] == NULL && PHT2[slot] == NULL) return false ;

   if (PHT1[slot] != NULL) return strcmp(str,PHT1[slot]) == 0 ;

   return PHT2[slot]->isMember(str) ;
}


// Pretty print for debugging.
//
void PerfectHT::dump() const {
   int m = hash.tableSize() ;   

   cout << "------------- PerfectHT::dump()  -------------\n" ;
   cout << "table size = " << hash.tableSize() << endl ;
   cout << endl ;
   for (int j=0 ; j < m ; j++) {
      cout << "[" << j << "]:  " ;
      if (PHT1[j] != NULL) cout << PHT1[j] ;
      if (PHT2[j] != NULL) {
         cout << endl ;
         PHT2[j]->dump() ;
      }
      cout << endl ;
   }

   cout << "----------------------------------------------\n" ;
}
