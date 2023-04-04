#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
#include "card.hpp"

namespace ariel{
    class Player{
    private:
    vector<Card> hand_;
    string playername;
    int stackcount;
    int takencount=0;
    int wincount=0;
    int isgame=0;
    public:
    Player();
    Player(string name);
    string getname(){return this->playername;}
    void setstack(int stack){stackcount=stack;}
    int getstack() const {return this->stackcount;}
    void settaken(int taken){takencount=taken;}
    int gettaken()const{return this->takencount;}
    void addwin(){wincount=wincount+1;}
    int getwin()const{return this->wincount;}
    void conectgame(){isgame=1;}
    int getisgame()const{return this->isgame;}

    void add_card(const Card& card)
     { hand_.push_back(card); }    

    int  stacksize();
    int  cardesTaken();
    vector<Card> gethand(){
        return this->hand_;
    }
    void erasefirtshand(){
    this->hand_.erase(this->hand_.begin());
    }
    void printhand(){
    std::cout << this->playername << std::endl;
    for (const auto& card : this->hand_) {
        std::cout << "rank: ";
        std::cout << card.get_rank() ;
        std::cout << " suit: ";
        std::cout << card.get_suit() << std::endl;

    }
    }
    
    };
}
#endif  