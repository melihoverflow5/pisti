#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// clubs ♣, diamonds ♦, hearts ♥, spades ♠
class Card {
private:
    string suit;
    string value;
    int point;
public:
    string getSuit(){
        return this->suit;
    }
    string getValue(){
        return this->value;
    }
    Card(string suit_i, string value_i) : suit(suit_i), value(value_i){
        if(value_i == "A")
            point = 1;
        else if(value_i == "J")
            point = 1;
        else if(suit_i == "♣" && value_i == "2")
            point = 2;
        else if(suit_i == "♦" && value_i == "10")
            point = 3;
        else
            point = 0;
    }
    ~Card() {}
};

ostream& operator<<(ostream& os, Card& card){
    os << card.getValue() << " " << card.getSuit();
    return os;
}


class PistiController{
private:
    vector<Card> Deck = {Card("♣", "A"),Card("♣", "2"),Card("♣", "3"),Card("♣", "4"),Card("♣", "5"),Card("♣", "6"),Card("♣", "7"),Card("♣", "8"),Card("♣", "9"),Card("♣", "10"),Card("♣", "J"),Card("♣", "Q"),Card("♣", "K"),
                         Card("♦", "A"),Card("♦", "2"),Card("♦", "3"),Card("♦", "4"),Card("♦", "5"),Card("♦", "6"),Card("♦", "7"),Card("♦", "8"),Card("♦", "9"),Card("♦", "10"),Card("♦", "J"),Card("♦", "Q"),Card("♦", "K"),
                         Card("♥", "A"),Card("♥", "2"),Card("♥", "3"),Card("♥", "4"),Card("♥", "5"),Card("♥", "6"),Card("♥", "7"),Card("♥", "8"),Card("♥", "9"),Card("♥", "10"),Card("♥", "J"),Card("♥", "Q"),Card("♥", "K"),
                         Card("♠", "A"),Card("♠", "2"),Card("♠", "3"),Card("♠", "4"),Card("♠", "5"),Card("♠", "6"),Card("♠", "7"),Card("♠", "8"),Card("♠", "9"),Card("♠", "10"),Card("♠", "J"),Card("♠", "Q"),Card("♠", "K"),};
    vector<Card> P1Hand = {};
    vector<Card> P2Hand = {};
    vector<Card> P1Pocket = {};
    vector<Card> P2Pocket = {};
    vector<Card> CardsOnTable = {};
    int round = 0;
    int p1Point = 0;
    int p2Point = 0;
public:
    void shuffleDeck(){
        random_shuffle(Deck.begin(), Deck.end());
    }
    void draw4(vector<Card> &vectorUse){
        for(int i = 0;i < 4;i++){
            vectorUse.push_back(Deck.back());
            Deck.pop_back();
        }
    }
    void getCards(vector<Card> v1, vector<Card> v2){
        for (int i = 0; i < v1.size(); i++) {
            v2.push_back(v1[i]);
        }
        v1.clear();
    }
    void playCard(int position){
        vector<Card>* v;
        int* p;
        if(round % 2 == 0) {
            v = &P1Hand;
            p = &p1Point;
        }else {
            v = &P2Hand;
            p = &p2Point;
        }
        CardsOnTable.push_back(v->at(position));
        // Delete the card from user hand
        if(CardsOnTable.size() == 1) {

        }else if(CardsOnTable.size() == 2){
            if(CardsOnTable.front().getValue() == CardsOnTable.back().getValue()){
                p += 10;
                getCards(CardsOnTable, *v);
            }
        }else{
            if(CardsOnTable.end()[-2].getValue() == CardsOnTable.end()[-1].getValue())
                getCards(CardsOnTable, *v);
        }
        round++;
    }
};

int main() {
    PistiController a;
    a.shuffleDeck();
    vector<Card> deneme = {};
    a.draw4(deneme);
    for (int i = 1; i < deneme.size(); ++i) {
        cout << deneme[i]<< endl;
    }
}