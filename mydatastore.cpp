#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"
#include "mydatastore.h"
#include <string>
#include <set>
#include <map>
#include <queue>


MyDataStore::~MyDataStore(){
    // Example: iterator for a set of Product pointers
    std::set<Product*>::iterator it;

    //Deletes every product created
    for (it = products_.begin(); it != products_.end(); ++it){
        delete *it;
    }
    //Deletes every user created
    std::map<std::string, User*>::iterator that;
    for (that = users_.begin(); that != users_.end(); ++that){
        delete that-> second;
    }
}


void MyDataStore::addProduct(Product* p){
    products_.insert(p); //adds the product to products_ set

    std::set<std::string> keys = p-> keywords(); //set of keywords generated for that product
    std::set<std::string>::iterator it;
     for (it = keys.begin(); it != keys.end(); ++it){
        keyword_to_product_[convToLower(*it)].insert(p); //this accesses the correct key-pair and then inserts p to the set of Products associated with that key
    }

}

    
void MyDataStore::addUser(User* u){
    users_.insert({convToLower(u->getName()), u}); //username-User* pair created
    user_to_cart_.insert(std::make_pair(convToLower(u->getName()), std::deque<Product*>()));
    //the above line adds the user's empty cart to the user-cart map
}

std::vector<Product*> MyDataStore::search (std::vector<std::string>& terms, int type){
    

    if (type == 0) /* AND search */ {
        //set intersection function
        std::vector<std::string>::iterator it;
        //if no term presented
        if (terms.size() < 1){
            std::vector<Product*> empty = {};
            return empty;
        }
        //set of products based on first keyword in terms
        std::set<Product*> final_products = keyword_to_product_[convToLower(terms[0])];

        for (it = terms.begin(); it != terms.end(); ++it){
            final_products = setIntersection(final_products, keyword_to_product_[convToLower(*it)]);
        }


        //looked at C++ vector class for this-- turns the set of products into a vector
        std::vector<Product*> v(final_products.begin(), final_products.end());//looked at C++ vector class for this
        return v;


    } else if (type == 1) /* OR search */ {
        std::vector<std::string>::iterator it;
          //if terms vector empty:
          if (terms.size() < 1){
            std::vector<Product*> empty = {};
            return empty;
        }

        //generate set of products containing first keyword in terms
        std::set<Product*> final_products = keyword_to_product_[convToLower(terms[0])];
        for (it = terms.begin(); it != terms.end(); ++it){
            final_products = setUnion(final_products, keyword_to_product_[convToLower(*it)]);
        }
        std::vector<Product*> v(final_products.begin(), final_products.end()); //looked at C++ vector class for this 
        return v;

    }
}



void MyDataStore::dump(std::ostream& ofile){

    std::set<Product*>::iterator it;
    ofile << "<products>" << "\n";
    for (it = products_.begin(); it != products_.end(); ++it){
        (*it)->dump(ofile);
    }
    ofile << "</products>";
    ofile << "\n" << "<users>" << "\n";
    std::map<std::string, User*>::iterator that;
    for (that = users_.begin(); that != users_.end(); ++that){
        that->second->dump(ofile);
    }
    ofile << "</users>";
}


void MyDataStore::addToCart(std::string user, Product* p){
    std::string username = convToLower(user);
    //if inputted username doesn't exist:
    if(user_to_cart_.find(username) == user_to_cart_.end()){
        std::cout<<"Invalid request"<< std::endl;
        return;
    }
    //add product to back of user's cart in user-cart map
    user_to_cart_[convToLower(user)].push_back(p);
}


void MyDataStore::viewCart(std::string u){
    std::deque<Product*>::iterator it;
    int cnt = 1; //begin with first item

    std::string username = convToLower(u);

    //if inputted username doesn't exist:
    if(user_to_cart_.find(username) == user_to_cart_.end()){
        std::cout<<"Invalid username"<< std::endl;
        return;
    }
    
    //set of Product* in inputted user's cart:
    std::deque<Product*> cart = user_to_cart_[username];

    //iterate through cart, call displayString() for each
    for (it = cart.begin(); it != cart.end(); ++it){
        std::cout<<"Item "<<cnt << ": "<<std::endl;
        std::cout << (*it) -> displayString();
        std::cout << std::endl;
        cnt++;
    }

}

void MyDataStore::buyCart(std::string user){

    //if user inputs invalid username:
    if (user_to_cart_.find(convToLower(user)) == user_to_cart_.end()){
        std::cout<< "Invalid Username"<<std::endl;
        return;
    } 

    std::string username = convToLower(user);

    //create an alias for the user's cart found in user_to_cart_
    std::deque<Product*>& cart = user_to_cart_[username];
    std::deque<Product*> not_bought;
    
   User* this_user = users_[username];
   
    while (!cart.empty()){
        if ( (cart.front()-> getPrice() <= this_user-> getBalance() ) &&
            (cart.front()-> getQty() >=1)  ){ /* user can afford this item*/
                
                this_user-> deductAmount(cart.front()-> getPrice());
                cart.front()-> subtractQty(1);
                cart.pop_front();

        } else /* user won't be purchasing this item */{
            not_bought.push_back(cart.front());
            cart.pop_front();
        }
    }

    cart = not_bought; /* user's cart in user_to_cart becomes updated*/
}
                               


    

