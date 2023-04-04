#include"player.hpp"
#include "card.hpp"


#include <string>
using namespace std;

namespace ariel
{
    class Game{
    private:
    int countturn=0;
    int drowcount=0;
    vector<string> detailsturn;
    Player & firstplayer;
    Player & secondplayer;
    public:
    Game(Player& player1,Player& player2);
    void addwin(int whowin,Card card1,Card card2, string details,int cardtake);
    void drawreq(string details,int cardtake);
    vector<string> getturns(){
        return this->detailsturn;
    }
    void addturn(string const &thisturn){
        this->detailsturn.push_back(thisturn);
    }
    int getcountgame()const{return this->countturn;}   
    int getcountdraw()const{return this->drowcount;} 
    void pluscount(){this->countturn++;} 
    void plusdraw(){this->drowcount++;} 
    void playTurn();
    void printLastTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();
    };
}
