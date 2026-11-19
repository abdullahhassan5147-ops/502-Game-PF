#include<iostream>
#include <windows.h>
#include<cstdlib>
#include<iomanip>
#include<string>    
#include<ctime>
#include<cstdlib>
using namespace std;

void setColor(int textColor, int bgColor) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, (bgColor << 4) | textColor);
}

const int BLACK = 0, WHITE = 7, GREY = 8, LIGHT_GREEN = 10, LIGHT_RED = 12;
const int BLUE = 9, CYAN = 11, MAGENTA = 13, YELLOW = 14, BRIGHT_WHITE = 15;
const int PLAYERS = 2;
const int DECK_SIZE = 52;
const int START_CARDS = 7;
const int MAX_HAND = 52;
const int LIMIT = 502;
const int MAX_SCORES = 10;
const int SPADES = 0, HEARTS = 1, DIAMONDS = 2, CLUBS = 3;
const int ACE = 0, TWO = 1, SEVEN = 6, EIGHT = 7, JACK = 10;
const int ACE_OF_SPADES = 0, SEVEN_OF_HEARTS = 19;
const int NO_DEMAND = -1;
const int DRAW = 0;

void clearScreen();
int getSuit(int card);
int getValue(int card);

void shuffleDeck(int deck[], int deckSize);
int drawCard(int deck[], int& deckSize, int discardPile[], int& discardSize);
bool isLegalCard(int card, int topCard, int demandSuit, int pendingDraw, bool pendingSkip);
void applyCardEffect(int card, int chosenSuit, int& pendingDraw, bool& pendingSkip, int& demandSuit);
int getCardPoints(int card);
int chooseComputerCard(int hand[], int handSize, int topCard, int demandSuit, int pendingDraw, bool pendingSkip);
int chooseComputerSuit(int hand[], int handSize);
int readChoice(int low, int high);
void showInstructions();
void setupPlayers(string names[], int colors[], bool isComputer[], bool vsComputer);
void showScoreboard(string names[], int colors[], int totals[], int handSize[], int roundNumber, int currentPlayer);
void showTopCard(int topCard, int deckSize, int pendingDraw, bool pendingSkip, int demandSuit);
void printHand(int hand[], int handSize, bool legal[]);
void showLeaderboard();
void saveWinner(string winnerName, int winnerScore);
void playGame(bool vsComputer);

int readChoice(int low, int high) {
    int choice;
    while (true) {
        cin >> choice;
        if (choice >= low && choice <= high) {
            return choice;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        setColor(LIGHT_RED, BLACK);
        cout << "Invalid choice. Please enter a number between " << low << " and " << high << ": ";
        setColor(WHITE, BLACK);
    }
}

int chooseplayingtype() {
    clearScreen();
    cout << "             START NEW GAME" << "\n";
    cout << "--------------------------------------" << "\n";
    cout << "1. ";
    setColor(LIGHT_RED, BLACK);
    cout << "Vs player (2 people share this computer)" << "\n";
    setColor(WHITE, BLACK);
    cout << "2. ";
    setColor(LIGHT_RED, BLACK);
    cout << "Vs Computer (you against the computer)" << "\n";
    setColor(WHITE, BLACK);
    cout << "Enter your choice(1-2): ";
    int playingType = readChoice(1, 2);
    cout << "\n";
    return playingType;
}

string Chooseplayer1name() {
    string player;
    cout << "Enter name for Player 1 (one word): ";
    cin >> player;
    return player;
}

string Chooseplayer2name(string player1name) {
    string player;
    cout << "Enter name for Player 2 (one word): ";
    cin >> player;
    while (player == player1name) {
        setColor(LIGHT_RED, BLACK);
        cout << "That name is already taken.";
        setColor(WHITE, BLACK);
        cout << " Enter a different name: ";
        cin >> player;
    }
    return player;
}

int Choseplayer1color(string player1name) {
    cout << "Choose a color for " << player1name << " :" << "\n";
    setColor(BLUE, BLACK);
    cout << "1.Blue ";
    setColor(CYAN, BLACK);
    cout << "2.Cyan text ";
    setColor(MAGENTA, BLACK);
    cout << "3.Magenta text ";
    setColor(YELLOW, BLACK);
    cout << "4.Yellow text" << "\n";
    setColor(WHITE, BLACK);
    cout << "Enter your choice(1-4): ";
    int pc = readChoice(1, 4);
    cout << "\n";
    return pc;
}

int Choseplayer2color(string player2name, int player1color) {
    cout << "Choose a color for " << player2name << " :" << "\n";
    if (player1color == BLUE) {
        setColor(GREY, BLACK);
        cout << "1.Blue(taken) ";
    }
    else {
        setColor(BLUE, BLACK);
        cout << "1.Blue ";
    }
    if (player1color == CYAN) {
        setColor(GREY, BLACK);
        cout << "2.Cyan(taken) ";
    }
    else {
        setColor(CYAN, BLACK);
        cout << "2.Cyan ";
    }
    if (player1color == MAGENTA) {
        setColor(GREY, BLACK);
        cout << "3.Magenta(taken) ";
    }
    else {
        setColor(MAGENTA, BLACK);
        cout << "3.Magenta ";
    }
    if (player1color == YELLOW) {
        setColor(GREY, BLACK);
        cout << "4.Yellow(taken) ";
    }
    else {
        setColor(YELLOW, BLACK);
        cout << "4.Yellow";
    }
    setColor(WHITE, BLACK);
    cout << "\n";
    cout << "Enter your choice(1-4): ";
    int pc = readChoice(1, 4);
    while ((pc == 1 && player1color == BLUE) || (pc == 2 && player1color == CYAN) || (pc == 3 && player1color == MAGENTA) || (pc == 4 && player1color == YELLOW)) {
        setColor(LIGHT_RED, BLACK);
        cout << "That colour is already taken. ";
        setColor(WHITE, BLACK);
        cout << "Enter a different choice: ";
        pc = readChoice(1, 4);
    }
    return pc;
}

int getPlayerColor(int colorChoice) {
    if (colorChoice == 1) {
        return BLUE;
    }
    else if (colorChoice == 2) {
        return CYAN;
    }
    else if (colorChoice == 3) {
        return MAGENTA;
    }
    else {
        return YELLOW;
    }
}

void setupPlayers(string names[], int colors[], bool isComputer[], bool vsComputer) {
    names[0] = Chooseplayer1name();
    colors[0] = getPlayerColor(Choseplayer1color(names[0]));
    isComputer[0] = false;

    if (vsComputer) {
        names[1] = "Computer";
        isComputer[1] = true;
        if (colors[0] == BLUE) {
            colors[1] = CYAN;
        }
        else {
            colors[1] = BLUE;
        }
    }
    else {
        names[1] = Chooseplayer2name(names[0]);
        colors[1] = getPlayerColor(Choseplayer2color(names[1], colors[0]));
        isComputer[1] = false;
    }

    cout << "Players ready: " << names[0] << " vs " << names[1] << ". Press Enter to deal";
    cin.ignore(10000, '\n');
    cin.get();
    clearScreen();
}

void output_main_screen() {
    cout << "======================================" << "\n";
    cout << "       WELCOME TO 502 CARD GAME" << "\n";
    cout << "======================================" << "\n";
    cout << "               MAIN MENU" << "\n";
    cout << "--------------------------------------" << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "1. ";
    setColor(WHITE, BLACK);
    cout << "Start New Game" << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "2. ";
    setColor(WHITE, BLACK);
    cout << "Instructions" << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "3. ";
    setColor(WHITE, BLACK);
    cout << "View Leaderboard" << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "4. ";
    setColor(WHITE, BLACK);
    cout << "EXIT" << "\n";
    cout << "--------------------------------------" << "\n";
}

void showInstructions() {
    clearScreen();
    cout << "--------------------------------------" << "\n";
    cout << "            INSTRUCTIONS              " << "\n";
    cout << "--------------------------------------" << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "1. ";
    setColor(WHITE, BLACK);
    cout << "Each player gets 7 cards. Empty your hand to win." << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "2. ";
    setColor(WHITE, BLACK);
    cout << "Match the top card by suit or value, or press 0 to draw." << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "3. ";
    setColor(WHITE, BLACK);
    cout << "J  : play on any card and choose the next suit." << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "4. ";
    setColor(WHITE, BLACK);
    cout << "2  : next player draws 2 (answer with a 2)." << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "5. ";
    setColor(WHITE, BLACK);
    cout << "A \u2660  : next player draws 5 (answer with any Ace)." << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "6. ";
    setColor(WHITE, BLACK);
    cout << "8  : next player is skipped (answer with an 8)." << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "7. ";
    setColor(WHITE, BLACK);
    cout << "7 \u2665  : play it and you win the round at once!" << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "8. ";
    setColor(WHITE, BLACK);
    cout << "Cards left in your hand are added to your total." << "\n";
    setColor(LIGHT_RED, BLACK);
    cout << "9. ";
    setColor(WHITE, BLACK);
    cout << "Reach 502 points and you lose the game." << "\n";
    cout << "--------------------------------------" << "\n";
    cout << "(Press Enter to return to the Main Menu...)";
    cin.ignore(10000, '\n');
    cin.get();
    clearScreen();
}
void createDeck(int deck[], int& deckSize) {
    for (int i = 0;i < 7;i++) {
        deck[i]
    }
}

void clearScreen() {
    system("CLS");
}

int getSuit(int card) {
    return card / 13;
}

int getValue(int card) {
    return card % 13;
}

void showLeaderboard() {
}

void playGame(bool vsComputer) {
}

int main() {
    srand(time(0));
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int player1hand[MAX_HAND], player2hand[MAX_HAND];
    int deck[decksize];
    bool running = true;
    while (running) {
        clearScreen();
        output_main_screen();
        int choice = readChoice(1, 4);
        if (choice == 1) {
            int playingtype = chooseplayingtype();
            bool vsComputer = (playingtype == 2);
            string names[PLAYERS];
            int colors[PLAYERS];
            bool isComputer[PLAYERS];
            setupPlayers(names, colors, isComputer, vsComputer);
            playGame(vsComputer);
        }
        else if (choice == 2) {
            showInstructions();
        }
        else if (choice == 3) {
            showLeaderboard();
        }
        else if (choice == 4) {
            running = false;
        }
    }
    setColor(WHITE, BLACK);
    return 0;
}