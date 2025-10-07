#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{ 
    std::set<std::string> newSet;
    //makes every word in rawWords lowercase
    std::string param = convToLower(rawWords);

    std::stringstream ss(param);
    std::string word;

    
    while (ss >> word){
      bool noPunct = true; 
      for (int i = 0; i <word.size(); i++){
        if ((word[i] < 'a') || (word[i] > 'z')) { //punctuation reached
            noPunct = false;

            if (word.size() == 2){ //case 1: just one letter like "J."
              i = word.size();
            } else if (i == 1){ //case 2: punctuation after first letter, like "I'll"
              newSet.insert(word.substr(0,1) + word.substr(2,1));
              i=word.size();
            } else { //case 3: insert word as is before punctuation
              newSet.insert(word.substr(0,i));
              i = word.size();

            }

        } 
      }
      if (noPunct){ /* if no punctuation found in word, add word to set as is*/
        newSet.insert(word);
      }

    }


  return newSet;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
