#include <string>
using namespace std;

#include "player.hpp"
using namespace ariel;

Player::Player(){}
Player::Player(string name)
{this->playername=name;
this->stackcount=0;
}
int Player::cardesTaken(){return Player::takencount;}
int Player::stacksize(){return Player::stackcount;}

   
