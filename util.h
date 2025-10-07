#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{

 typename std::set<T> intersect;

 typename std::set<T>::iterator it;
 for (it = s1.begin(); it != s1.end(); ++it){
  //checks if each item in s1 is found in s2
  if (s2.find(*it) != s2.end()){
    intersect.insert(*it);
  }
 }

 return intersect;

}


template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> unionSet;
  //inserts s1 and s2 into unionSet
  unionSet.insert(s1.begin(), s1.end());
  unionSet.insert(s2.begin(), s2.end());
  return unionSet;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
