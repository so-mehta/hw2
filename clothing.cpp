#include <sstream>
#include <iomanip>
#include "product.h"
#include "util.h"
#include "clothing.h"
#include <string>

//Initiliaze's Clothing's private members, utilizes Product constructor
Clothing::Clothing(const std::string category, const std::string name, double price, 
    int qty, std::string size, std::string brand) :
      Product(category, name, price, qty),
      size_(size),
      brand_(brand)
{

}
Clothing::~Clothing()
{

}
//Generates set of keywords using brand and name
std::set<std::string> Clothing:: keywords() const{
  std::set<std::string> keywords = 
  parseStringToWords(this -> brand_);
  std::set<std::string> name_set = 
  parseStringToWords(getName() );
  keywords.insert(name_set.begin(), name_set.end());
  return keywords;

}


std::string Clothing::displayString() const{
  
  std::string display_contents = getName() +   "\nSize: "
  + size_ + " Brand: " + brand_ + "\n" + std::to_string(getPrice()) + " " + std::to_string(getQty()) + 
  " left.";
  return display_contents;
}


void Clothing::dump(std::ostream& os) const{
  os << "clothing" << "\n" << getName() << "\n" <<
  getPrice() << "\n" << getQty() << "\n" <<
  size_ << "\n" << brand_ << std::endl;


}



