#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
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
        if(rank == "A")
            point = 1;
        else if(rank == "J")
            point = 1;
        else if(suit == "♣" && rank == "2")
            point = 2;
        else if(suit == "♦" && rank == "10")
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
protected:
    string name;
    int point = 0;
    int pisti;
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
    void addPisti(){
        pisti++;
    }
    int getPisti(){
        return pisti;
    }
    vector<Card> PlayerHand = {};
    vector<Card> PlayerPocket = {};
    Player(string name1) : name(name1), pisti(0){};

    virtual void nextGame() {
        PlayerPocket.clear();
        pisti = 0;
    }
};

class ComputerPlayer : public Player {
private:
    vector<Card> KnownCards = {};
    vector<Card> CardsOnTable = {};
    vector<int> Possibilities = {};
public:
    void getKnownCards() {
        cout << endl;
        for (int i = 0; i < KnownCards.size(); ++i) {
            cout << KnownCards[i] << " ";
        }
        cout << endl;
    }
    void getCardsOnTable(){
        cout << endl;
        for (int i = 0; i < CardsOnTable.size(); ++i) {
            cout << CardsOnTable[i] << " ";
        }
        cout << endl;
    }
    void addPlayedCard(Card c){
        KnownCards.push_back(c);
    }
    void addPlayedCard(vector<Card> c){
        for (int i = 0; i < c.size(); i++) {
            KnownCards.push_back(c[i]);
        }
    }
    void addCardOnTheTable(Card c) {
        CardsOnTable.push_back(c);
    }
    void clearCardsOnTheTable(){
        CardsOnTable.clear();
    }
    int isThereJ() {
        for (int i = 0; i < PlayerHand.size(); i++) {
            if(PlayerHand[i].getRank() == "J")
                return i;
        }
        return -1;
    }
    int play() {
        int p = 0;
        for (int i = 0; i < PlayerHand.size(); ++i) {
            if(KnownCards.back().getRank() == PlayerHand[i].getRank()){
                return i;
            }
        }
        for(int i = 0; i < CardsOnTable.size(); i++) {
            p += CardsOnTable[i].getPoint();
        }
        CalculatePossibility();
        if(p != 0){
            if(isThereJ() != -1)
                return isThereJ();
        }
        int selected = max_element(Possibilities.begin(), Possibilities.end()) - Possibilities.begin();
//        cout << selected;
        if (PlayerHand[selected].getRank() != "J")
            return selected;
        else
            return 0;
    }
    void CalculatePossibility(){
        int poss;
        Possibilities.clear();
        for (int i = 0; i < PlayerHand.size(); i++) {
            poss = 0;
            for (int j = 0; j < KnownCards.size(); j++) {
                if(PlayerHand[i].getRank() == KnownCards[j].getRank())
                    poss++;
            }
            Possibilities.push_back(poss);
        }
    }
    void nextGame() override {
        PlayerPocket.clear();
        pisti = 0;
        KnownCards.clear();
        CardsOnTable.clear();
    }
    ComputerPlayer(string name1) : Player(name1) {}
};


class PistiController{
private:
    vector<Card> Deck = {Card("♣", "A"),Card("♣", "2"),Card("♣", "3"),Card("♣", "4"),Card("♣", "5"),Card("♣", "6"),Card("♣", "7"),Card("♣", "8"),Card("♣", "9"),Card("♣", "10"),Card("♣", "J"),Card("♣", "Q"),Card("♣", "K"),
                         Card("♦", "A"),Card("♦", "2"),Card("♦", "3"),Card("♦", "4"),Card("♦", "5"),Card("♦", "6"),Card("♦", "7"),Card("♦", "8"),Card("♦", "9"),Card("♦", "10"),Card("♦", "J"),Card("♦", "Q"),Card("♦", "K"),
                         Card("♥", "A"),Card("♥", "2"),Card("♥", "3"),Card("♥", "4"),Card("♥", "5"),Card("♥", "6"),Card("♥", "7"),Card("♥", "8"),Card("♥", "9"),Card("♥", "10"),Card("♥", "J"),Card("♥", "Q"),Card("♥", "K"),
                         Card("♠", "A"),Card("♤", "2"),Card("♠", "3"),Card("♠", "4"),Card("♠", "5"),Card("♠", "6"),Card("♠", "7"),Card("♠", "8"),Card("♠", "9"),Card("♠", "10"),Card("♠", "J"),Card("♠", "Q"),Card("♠", "K"),};

    vector<Card> CardsOnTable = {};
    int round = 0;
    Card lastPlayedCard = Card("   ", "   ");
    string lastWinner = " ";
    int res1 = 0, res2 = 0;
public:
    Card getLastPlayedCard() {
        return lastPlayedCard;
    }

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
        lastPlayedCard = player.PlayerHand.at(position);
        player.PlayerHand.erase(player.PlayerHand.begin()+position);

        if(CardsOnTable.size() == 1) {
        }else if(CardsOnTable.size() == 2){
            if(CardsOnTable.front().getRank() == CardsOnTable.back().getRank()){
                player.addPisti();
                if(CardsOnTable.front().getRank() == "J")
                    player.addPisti();
                getCards(player.PlayerPocket);
                lastWinner = player.getName();
            }else if(CardsOnTable.back().getRank() == "J"){
                getCards(player.PlayerPocket);
                lastWinner = player.getName();
            }
        }else{
            if(CardsOnTable.end()[-2].getRank() == CardsOnTable.end()[-1].getRank() ||
                    CardsOnTable.back().getRank() == "J") {
                getCards(player.PlayerPocket);
                lastWinner = player.getName();
            }
        }
        round++;
    }
    void endGame(Player &player1, Player &player2) {
        cout << endl << setw(8) << "Game Finished" << setw(20) << "Total Points";
        if(player1.getName() == lastWinner)
            getCards(player1.PlayerPocket);
        else if( player2.getName() == lastWinner)
            getCards(player2.PlayerPocket);
        else
            cout << "Last Winner is not working"<< endl;
        for(int i = 0; i < player1.PlayerPocket.size(); i++) {
            res1 += player1.PlayerPocket[i].getPoint();
        }
        for(int i = 0; i < player2.PlayerPocket.size(); i++) {
            res2 += player2.PlayerPocket[i].getPoint();
        }

        if (player1.PlayerPocket.size() > player2.PlayerPocket.size()){
            res1 += 3;
        }else if (player1.PlayerPocket.size() < player2.PlayerPocket.size()) {
            res2 +=3;
        }else {
            if(res1 > res2)
                res1 += 3;
            else
                res2 += 3;
        }
        res1 += (player1.getPisti() * 10);
        res2 += (player2.getPisti() * 10);
        player1.addPoints(res1);
        player2.addPoints(res2);
        cout << endl << setw(8) <<player1.getName() << setw(4)<< res1 << setw(14) << player1.getPoints() << endl;
        cout << setw(8) << player2.getName() << setw(4) << res2 << setw(14) << player2.getPoints() << endl << endl;
        if(res1 > res2){
            cout << setw(4) << player1.getName() << " is ahead now. Which one do you want?";
        }else if(res1 == res2){
            cout << setw(4) << "DRAW";
        }else{
            cout << setw(4) << player2.getName() << " is ahead now. Which one do you want?";
        }
        player1.nextGame();
        player2.nextGame();

    }
};












int main() {
    cout << "---------------------Start Game---------------------"<< endl << endl;
    Player player1("Bob");
    ComputerPlayer player2("Joey");

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
                player2.addPlayedCard(player2.PlayerHand);
            }
            if(controller.getRound() == 0){
                player2.addPlayedCard(controller.cardOnTheTable());
                player2.addCardOnTheTable(controller.cardOnTheTable());
            }

            if (controller.getRound() % 2 == 0) {
                cout << endl << setw(25) << controller.cardOnTheTable() << endl << endl;
                for (int i = 0; i < player1.PlayerHand.size(); ++i) {
                    cout << setw(10) << player1.PlayerHand[i];
                }
                cout << endl;
                for (int i = 0; i < player1.PlayerHand.size(); ++i) {
                    cout << setw(8) << " " << i + 1 << " ";
                }
                cout << endl << setw(4) << player1.getName() << ", which card do you want to play ? ";
                while (1) {
                    cin >> position;
                    if (position > 0 && position <= player1.PlayerHand.size())
                        break;
                    cout << "Invalid Input ";
                }
                controller.playCard(player1, position - 1);
                player2.addPlayedCard(controller.getLastPlayedCard());
            } else {
                cout << endl;
                position = player2.play();
                controller.playCard(player2, position);
            }
            player2.addCardOnTheTable(controller.getLastPlayedCard());
            if(controller.cardOnTheTable().getRank() == "   ")
                player2.clearCardsOnTheTable();
//            player2.getKnownCards();
//            player2.getCardsOnTable();
        }
        controller.endGame(player1, player2);

        cout << endl << setw(8) << "1 - Continue\n2 - Exit\n";
        while(1){
            cin >> setw(8) >> choice;
            if(choice == 1 || choice == 2)
                break;
            cout << setw(8) << "Invalid Input " << endl;
        }
        if(choice == 2)
            break;
    }
    if(player1.getPoints() > player2.getPoints())
        cout << "\n\n\n" << setw(10) << player1.getName() << " WON THE GAME!!!!\n\n";
    else if(player2.getPoints() > player1.getPoints())
        cout << "\n\n\n" << setw(10) << player2.getName() << " WON THE GAME!!!!\n\n";
    else
        cout << "\n\n\n" << setw(10) << "DRAW\n\n";
    return 0;
}