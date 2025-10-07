#include <sstream>
#include <iomanip>
#include "product.h"
#include "util.h"
#include "book.h"
#include <string>

//initialize's Book's private members, utilizes Product's constructor
Book::Book(const std::string category, const std::string name, double price, 
    int qty, std::string ISBN, std::string author) :
      Product(category, name, price, qty),
      isbn_(ISBN),
      author_(author)
{

}
Book::~Book()
{

}

//generates set of keywords based on Book's isbn, name, and author
std::set<std::string> Book:: keywords() const{
  std::set<std::string> keywords;
  keywords.insert(isbn_);
  std::set<std::string> title_set = parseStringToWords(this->getName());
  keywords.insert(title_set.begin(), title_set.end());
  std::set<std::string> author_set = parseStringToWords(author_);
  keywords.insert(author_set.begin(), author_set.end());
  return keywords;

}


std::string Book::displayString() const{
  std::string display_contents = getName() +   "\n Author: " + 
  author_ + " ISBN: " + isbn_ + "\n " + std::to_string(getPrice()) + " "
   + std::to_string(getQty()) + " left.";
  return display_contents;
}


void Book::dump(std::ostream& os) const{
  os << "book" << "\n" << getName() << "\n" <<
  getPrice() << "\n" << getQty() << "\n" <<
  isbn_ << "\n" << author_ << std::endl;


}



