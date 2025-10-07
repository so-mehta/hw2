#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"
#include <string>
#include <set>
#include <map>
#include <queue>
#include <deque>

class MyDataStore : public DataStore{
public: 
    ~MyDataStore();

    void addProduct(Product* p); /* new product added*/
    void addUser(User* u); /*new user added*/
    std::vector<Product*> search (std::vector<std::string>& terms, int type); /*return vector of Product pointers*/

    void dump(std::ostream& ofile);
    void addToCart(std::string user, Product* p); /* each user has a cart, add product to their cart*/
    void viewCart(std::string u);
    void buyCart(std::string user);




private:
    // std::set<User*> users_;
    std::map<std::string, User*> users_;
    std::set<Product*> products_;
    std::map<std::string, std::set<Product*>> keyword_to_product_;
    std::map<std::string, std::deque<Product*>> user_to_cart_;

};
#endif


