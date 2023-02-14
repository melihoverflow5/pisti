#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;


// clubs ♣, diamonds ♦, hearts ♥, spades ♠
class Card {
private:
    string suit;
    string rank;
    int point;
public:
    int getPoint(){
        return point;
    }
    string getSuit() const {
        return suit;
    }
    string getRank() const {
        return rank;
    }
    Card(string suit_i, string rank_i) : suit(suit_i), rank(rank_i){
        if(rank_i == "A")
            point = 1;
        else if(rank_i == "J")
            point = 1;
        else if(suit_i == "♣" && rank_i == "2")
            point = 2;
        else if(suit_i == "♦" && rank_i == "10")
            point = 3;
        else
            point = 0;
    }
    ~Card() {}
};

ostream& operator<< (ostream& os, const Card& card){
    os << card.getSuit() << " " << card.getRank();
    return os;
}
int randomize(int i){
    return rand() % i;
};

class Player{
private:
    string name;
    int point = 0;
public:
    string getName(){
        return name;
    }
    int getPoints() {
        return point;
    }
    void addPoints(int p){
        point += p;
    }
    vector<Card> PlayerHand = {};
    vector<Card> PlayerPocket = {};
    Player(string name1) : name(name1){};
};

class PistiController{
private:
    vector<Card> Deck = {Card("♣", "A"),Card("♣", "2"),Card("♣", "3"),Card("♣", "4"),Card("♣", "5"),Card("♣", "6"),Card("♣", "7"),Card("♣", "8"),Card("♣", "9"),Card("♣", "10"),Card("♣", "J"),Card("♣", "Q"),Card("♣", "K"),
                         Card("♦", "A"),Card("♦", "2"),Card("♦", "3"),Card("♦", "4"),Card("♦", "5"),Card("♦", "6"),Card("♦", "7"),Card("♦", "8"),Card("♦", "9"),Card("♦", "10"),Card("♦", "J"),Card("♦", "Q"),Card("♦", "K"),
                         Card("♥", "A"),Card("♥", "2"),Card("♥", "3"),Card("♥", "4"),Card("♥", "5"),Card("♥", "6"),Card("♥", "7"),Card("♥", "8"),Card("♥", "9"),Card("♥", "10"),Card("♥", "J"),Card("♥", "Q"),Card("♥", "K"),
                         Card("♠", "A"),Card("♤", "2"),Card("♠", "3"),Card("♠", "4"),Card("♠", "5"),Card("♠", "6"),Card("♠", "7"),Card("♠", "8"),Card("♠", "9"),Card("♠", "10"),Card("♠", "J"),Card("♠", "Q"),Card("♠", "K"),};

    vector<Card> CardsOnTable = {};
    int round = 0;
    Player lastWinner = Player("none");
public:
    int getRound(){
        return round;
    }
    void shuffleDeck(){
        srand(unsigned(time(0)));
        random_shuffle(Deck.begin(), Deck.end(), randomize);
    }
    void draw4(vector<Card> &vectorUse){
        for(int i = 0;i < 4;i++){
            vectorUse.push_back(Deck.back());
            Deck.pop_back();
        }
    }
    void startGame(){
        shuffleDeck();
        draw4(CardsOnTable);
    }
    void getCards(vector<Card> &v1){
        for (int i = 0; i < CardsOnTable.size(); i++) {
            v1.push_back(CardsOnTable[i]);
        }
        CardsOnTable.clear();
    }
    Card cardOnTheTable() {
        if(CardsOnTable.empty())
            return Card("   ", "   ");
        return CardsOnTable.back();
    }
    void playCard(Player &player, int position){
        CardsOnTable.push_back(player.PlayerHand.at(position));
        player.PlayerHand.erase(player.PlayerHand.begin()+position);

        if(CardsOnTable.size() == 1) {
        }else if(CardsOnTable.size() == 2){
            if(CardsOnTable.front().getRank() == CardsOnTable.back().getRank()){
                player.addPoints(10);
                if(CardsOnTable.front().getRank() == "J")
                    player.addPoints(10);
                getCards(player.PlayerPocket);
                lastWinner = player;
            }else if(CardsOnTable.back().getRank() == "J"){
                getCards(player.PlayerPocket);
                lastWinner = player;
            }
        }else{
            if(CardsOnTable.end()[-2].getRank() == CardsOnTable.end()[-1].getRank() ||
                    CardsOnTable.back().getRank() == "J") {
                getCards(player.PlayerPocket);
                lastWinner = player;
            }
        }
        round++;
    }
    void endGame(Player player1, Player player2) {
        cout << endl << setw(8) << "Game Finished";
        getCards(lastWinner.PlayerPocket);
        for (int i = 0; i < player1.PlayerPocket.size(); i++) {
            player1.addPoints(player1.PlayerPocket[i].getPoint());
        }
        for (int i = 0; i < player2.PlayerPocket.size(); i++) {
            player2.addPoints(player2.PlayerPocket[i].getPoint());
        }
        if(player1.PlayerPocket.size() > player2.PlayerPocket.size())
            player1.addPoints(3);
        else
            player2.addPoints(3);
        cout << endl << setw(8) <<"Player 1:" << player1.getPoints() << endl;
        cout << setw(8) <<"Player 2:" << player2.getPoints() << endl;
        if(player1.getPoints() > player2.getPoints()){
            cout << setw(8) << "Player 1 WON";
        }else if(player1.getPoints() == player2.getPoints()){
            cout << setw(8) << "DRAW";
        }else{
            cout << setw(8) << "Player 2 WON";
        }
    }
};

int main() {
    cout << "---------------------Start Game---------------------"<< endl << endl;
    Player player1("Bob");
    Player player2("Joey");

    cout << "Press enter to start . . .";
    cin.get();
    while(1) {
        PistiController controller;
        controller.startGame();

        int choice;
        while (controller.getRound() < 48) {
            int position;

            if (controller.getRound() % 8 == 0) {
                controller.draw4(player1.PlayerHand);
                controller.draw4(player2.PlayerHand);
            }
            cout << endl << setw(26) << controller.cardOnTheTable() << endl << endl;
            if (controller.getRound() % 2 == 0) {

                for (int i = 0; i < player1.PlayerHand.size(); ++i) {
                    cout << setw(9) << player1.PlayerHand[i];
                }
                cout << endl;
                for (int i = 0; i < player1.PlayerHand.size(); ++i) {
                    cout << setw(9) << "  " << i + 1 << " ";
                }
                cout << endl << setw(4) << player1.getName() << ", which card do you want to play ? ";
                while (1) {
                    cin >> position;
                    if (position > 0 && position <= player1.PlayerHand.size())
                        break;
                    cout << "Invalid Input ";
                }
                controller.playCard(player1, position - 1);
            } else {
                for (int i = 0; i < player2.PlayerHand.size(); ++i) {
                    cout << setw(9) << player2.PlayerHand[i];
                }
                cout << endl;
                for (int i = 0; i < player2.PlayerHand.size(); ++i) {
                    cout << setw(9) << "  " << i + 1 << " ";
                }
                cout << endl << setw(4) << player2.getName() << ", which card do you want to play ? ";
                while (1) {
                    cin >> position;
                    if (position > 0 && position <= player2.PlayerHand.size())
                        break;
                    cout << "Invalid Input ";
                }
                controller.playCard(player2, position - 1);
            }
        }
        controller.endGame(player1, player2);

        cout << endl << setw(8) << "1 - Continue\n2- Exit\n";
        while(1){
            cin >> setw(8) >> choice;
            if(choice == 1 || choice == 2)
                break;
            cout << setw(8) << "Invalid Input " << endl;
        }
        if(choice == 2)
            break;
    }

    return 0;
}