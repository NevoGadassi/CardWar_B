#include <string>
using namespace std;

#include "card.hpp"
using namespace ariel;

Card::Card(){}
Card::Card(int number,int type)   {
        this->suit=type;
        this->rank=number;
     }

