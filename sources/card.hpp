#pragma once
#ifndef CARD_HPP
#define CARD_HPP


#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

namespace ariel{
    class Card{
    private:
    int suit;
    int rank;

    public:
    Card();
    Card(int number, int type) ;
    int get_suit() const { return suit; }
    int get_rank() const { return rank; }



  


};
}
#endif