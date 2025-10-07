#include <sstream>
#include <iomanip>
#include "product.h"
#include "util.h"
#include "movie.h"
#include <string>

//initalizes private members of Movie class, utilizes Product constructor
Movie::Movie(const std::string category, const std::string name, double price, 
    int qty, std::string genre, std::string rating) :
      Product(category, name, price, qty),
      genre_(genre),
      rating_(rating)
{

}
Movie::~Movie()
{

}

//generate set of keywords based off movie's name and genre
std::set<std::string> Movie:: keywords() const{
  std::set<std::string> keywords;
  keywords.insert(genre_);
  std::set<std::string> name_set = parseStringToWords(this->getName());
  keywords.insert(name_set.begin(), name_set.end());
  return keywords;

}


std::string Movie::displayString() const{
  std::string display_contents = getName() +   "\n Genre: " + 
  genre_ + " Rating: " + rating_ + "\n " + std::to_string(getPrice()) + " "
   + std::to_string(getQty()) + " left.";
  return display_contents;
}


void Movie::dump(std::ostream& os) const{
  os << "movie" << "\n" << getName() << "\n" <<
  getPrice() << "\n" << getQty() << "\n" <<
  genre_ << "\n" << rating_ << std::endl;


}



