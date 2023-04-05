#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
using namespace std;

#include "game.hpp"
using namespace ariel;

#include "player.hpp"
#include "card.hpp"
using namespace ariel;


    Game::Game(Player& player1,Player& player2):firstplayer(player1) , secondplayer(player2){

       if(this->firstplayer.getisgame()==1 ||this->secondplayer.getisgame()==1){
        throw("someone alreday played");
       }
       else{
        this->firstplayer.conectgame();
        this->secondplayer.conectgame();
         std::vector<Card> deck;
        for (int suit = 1; suit < 5; ++suit) {
            for (int rank = 1; rank < 14; ++rank) {
             deck.emplace_back(rank, suit);
             }
            }

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));

        for (std::vector<Card>::size_type i = 0; i < 26; ++i)  {
            this->firstplayer.add_card(deck.at(i));
            int count1=this->firstplayer.getstack();
            this->firstplayer.setstack(count1+1);
            this->secondplayer.add_card(deck.at(i+26));
            int count2=this->secondplayer.getstack();
            this->secondplayer.setstack(count2+1);
        }
       }

  
    }
    void Game::addwin(int whowin,Card card1,Card card2, string details,int cardtake){
        string suitNames[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string rankNames[] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
        if(whowin == 1){
            this->firstplayer.settaken(this->firstplayer.gettaken()+cardtake);
            string thisturn= details+this->firstplayer.getname()+" played "+ rankNames[card1.get_rank()-1]+" of "+suitNames[card1.get_suit()-1]+ " "+this->secondplayer.getname()+" played "+ rankNames[card2.get_rank()-1]+" of "+suitNames[card2.get_suit()-1]+" ."+this->firstplayer.getname()+"win.";
            this->addturn(thisturn);
            this->firstplayer.addwin();
        }
        else{
            this->secondplayer.settaken(this->secondplayer.gettaken()+cardtake);
            string thisturn= details+this->firstplayer.getname()+" played "+ rankNames[card1.get_rank()-1]+" of "+suitNames[card1.get_suit()-1]+ " " +this->secondplayer.getname()+" played "+ rankNames[card2.get_rank()-1]+" of "+suitNames[card2.get_suit()-1]+" ." +this->secondplayer.getname()+"win.";
            this->addturn(thisturn);
            this->secondplayer.addwin();


        }

    }
    void Game::drawreq( string details,int cardtake){
        this->plusdraw();
        string suitNames[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string rankNames[] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
        string turn;
        if(this->firstplayer.getstack()>1){

            this->firstplayer.erasefirtshand();
            this->secondplayer.erasefirtshand();
            Card firstcard=this->firstplayer.gethand().at(0);
            Card secondcard=this->secondplayer.gethand().at(0);
            this->firstplayer.erasefirtshand();
            this->secondplayer.erasefirtshand();
            this->firstplayer.setstack(this->firstplayer.getstack()-2);
            this->secondplayer.setstack(this->secondplayer.getstack()-2);

             if(firstcard.get_rank()==secondcard.get_rank())
                {  
                    turn=details+this->firstplayer.getname()+" played "+ rankNames[firstcard.get_rank()-1]+" of "+suitNames[firstcard.get_suit()-1]+ this->secondplayer.getname()+" played "+ rankNames[secondcard.get_rank()-1]+" of "+suitNames[secondcard.get_suit()-1]+" DRAW.";
                     drawreq(turn,cardtake+4);
                }
             else  if((firstcard.get_rank() > secondcard.get_rank()) || (firstcard.get_rank()==1))
                {
                         if(firstcard.get_rank()==1 && secondcard.get_rank()==2){
                                 this->addwin(2,firstcard,secondcard,details,cardtake+4);
                            }       
               
                        else if(secondcard.get_rank()==1 && firstcard.get_rank()!=2){
                            this->addwin(2,firstcard,secondcard,details,cardtake+4);
                            }
                         else{
                            this->addwin(1,firstcard,secondcard,details,cardtake+4);
                            }

                 }
            else if(firstcard.get_rank()<secondcard.get_rank() ||secondcard.get_rank()==1)
            {
                if(firstcard.get_rank()==2 && secondcard.get_rank()==1)
                {
                    this->addwin(1,firstcard,secondcard,details,cardtake+4);
                }
                else{
                    this->addwin(2,firstcard,secondcard,details,cardtake+4);
                }
            }
        
        }
        else{
            this->firstplayer.settaken(this->firstplayer.gettaken()+this->firstplayer.getstack()+(cardtake)/2);
            this->secondplayer.settaken(this->secondplayer.gettaken()+this->secondplayer.getstack()+(cardtake)/2);
            turn=details+" stack is over card divide to the player";
            this->addturn(turn);
        }


    }
    void Game::  playTurn (){
        this->pluscount();
        string draw;
        string suitNames[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string rankNames[] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };

        if(this->firstplayer.getname()==this->secondplayer.getname()){
            throw("the same player");
        }
        else if (this->firstplayer.stacksize()>0 &&this->secondplayer.stacksize()>0)
        {
            Card firstcard=this->firstplayer.gethand().at(0);
            Card secondcard=this->secondplayer.gethand().at(0);
            this->firstplayer.setstack(this->firstplayer.getstack()-1);
            this->firstplayer.erasefirtshand();
            this->secondplayer.setstack(this->secondplayer.getstack()-1);
            this->secondplayer.erasefirtshand();

            draw=this->firstplayer.getname()+" played "+ rankNames[firstcard.get_rank()-1]+" of "+suitNames[firstcard.get_suit()-1]+ this->secondplayer.getname()+" played "+ rankNames[secondcard.get_rank()-1]+" of "+suitNames[secondcard.get_suit()-1]+" DRAW.";

            if((firstcard.get_rank() > secondcard.get_rank()) || (firstcard.get_rank()==1)){
                if(firstcard.get_rank()==1 && secondcard.get_rank()==2){
                    this->addwin(2,firstcard,secondcard,"",2);
                }
                else if (firstcard.get_rank()==1 && secondcard.get_rank()==1){
                    drawreq(draw,2);
                }
                else if(secondcard.get_rank()==1 && firstcard.get_rank()!=2){
                    this->addwin(2,firstcard,secondcard,"",2);
                }
                else{
                   this->addwin(1,firstcard,secondcard,"",2);

                }

            }
            else if(firstcard.get_rank()<secondcard.get_rank() ||secondcard.get_rank()==1)
            {
                if(firstcard.get_rank()==2 && secondcard.get_rank()==1)
                {
                    this->addwin(1,firstcard,secondcard,"",2);
                }
               else if (firstcard.get_rank()==1 && secondcard.get_rank()==1){
                    drawreq(draw,2);
                }
                else{
                    this->addwin(2,firstcard,secondcard,"",2);
                }
            }
            else{
                drawreq(draw,2);
            }

        }
        else{
            throw("game is over");
        }
    }
    
    void Game::  printLastTurn(){

            std::cout << this->detailsturn.back() << std::endl;
    }


    void Game::   playAll(){
       while (this->firstplayer.stacksize()>0 &&this->secondplayer.stacksize()>0)
       {
            this->playTurn();
        }
        

    }
    void Game::  printWiner(){
        if (this->firstplayer.cardesTaken() == this->secondplayer.cardesTaken())
    {
        throw("there is no winner");
    }
    else if (this->firstplayer.cardesTaken() > this->secondplayer.cardesTaken())
    {
         std::cout << this->firstplayer.getname() ;
        std::cout << "is the winner " << std::endl;

    }
    else{
        std::cout << this->secondplayer.getname() ;
        std::cout << "is the winner " << std::endl;
    }

    }
    void Game::  printLog(){
    for (const std::string& str : this->detailsturn) {
        std::cout << str << std::endl;
    }
    }
    void Game::   printStats(){
        std::cout <<" status of this game:" << std::endl;
        std::cout << this->firstplayer.getname()+ " win ";
        std::cout <<this->firstplayer.getwin();
        std::cout <<" from ";
        std::cout <<this->getcountgame();
        std::cout <<" and take ";
        std::cout <<this->firstplayer.gettaken();
        std::cout <<" cards." << std::endl ;
        std::cout << this->secondplayer.getname()+ " win ";
        std::cout << this->secondplayer.getwin();
        std::cout <<" from ";
        std::cout <<this->getcountgame();
        std::cout <<" and take ";
        std::cout <<this->secondplayer.gettaken();
        std::cout <<" cards." << std::endl ;
        std::cout <<"there was a " ;
        std::cout <<this->getcountdraw();
        std::cout <<" draws in this game" << std::endl;
    }
