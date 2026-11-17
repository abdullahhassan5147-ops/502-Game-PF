
#include<iostream>
#include <windows.h>
#include<cstdlib>
#include<iomanip>
#include<string>
using namespace std;

// Set console text and background colours.
void setColor(int textColor, int bgColor) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, (bgColor << 4) | textColor);
}

// Colour values
const int BLACK = 0;
const int GREY = 7;
const int DARK_GREY = 8;
const int WHITE = 15;
const int BLUE = 9;
const int CYAN = 11;
const int MAGENTA = 13;
const int YELLOW = 14;
const int RED = 12;

int chooseplayingtype(){
	system("CLS");
	cout<<"             START NEW GAME"<<endl;
	cout<<"--------------------------------------"<<endl;
	cout<<"1. ";
	setColor(RED, BLACK);
	cout<<"Vs player (2 people share this computer)"<<endl;
	setColor(GREY, BLACK);
	cout<<"2. ";
	setColor(RED, BLACK);
	cout<<"Vs Computer (you against the computer)"<<endl;
	setColor(GREY, BLACK);
	int y;
	cout<<"Enter your choice(1-2): ";
	cin>>y;
	while(y!=1&&y!=2){
		cin>>y;
	}
	cout<<endl;
	return y;
	
}
string Chooseplayer1name(){
	string player;
	cout<<"Enter name for Player 1 (one word): ";
	cin>>player;
	return player;
}
string Chooseplayer2name(string player1name){
	string player;
	cout<<"Enter name for Player 2 (one word): ";
	cin>>player;
	while(player==player1name){
		setColor(RED, BLACK);
		cout<<"That name is already taken.";
		setColor(GREY, BLACK);
		cout<<"Enter a different name: ";
		cin>>player;
	}
	return player;
}
int Choseplayer1color(string player1name){
	cout<<"Choose a color for "<<player1name<<" :"<<endl;
	setColor(BLUE, BLACK);
    cout << "1.Blue ";
	setColor(CYAN, BLACK);
    cout << "2.Cyan text ";
    setColor(MAGENTA, BLACK);
    cout << "3.Magenta text ";
    setColor(YELLOW, BLACK);
    cout << "4.Yellow text"<<endl;
    setColor(GREY, BLACK);
	int pc;
	cout<<"Enter your choice(1-4): ";
	cin>>pc;
	while(pc<1||pc>4){
		cin>>pc;
	}
	cout<<endl;
	return pc;
}
int Choseplayer2color(string player2name,int player1color,string player1name){
	cout<<"Choose a color for "<<player2name<<" :"<<endl;
	if(player1color==BLUE){
		setColor(GREY, BLACK);
    	cout << "1.Blue(taken) ";
	}
	else{
		setColor(BLUE, BLACK);
    	cout << "1.Blue ";
	}
	if(player1color==CYAN){
		setColor(GREY,BLACK);
		cout<<"2.Cyan(taken) ";
	}
	else{
		setColor(CYAN,BLACK);
		cout<<"2.Cyan ";
	}
	if(player1color==MAGENTA){
		setColor(GREY,BLACK);
		cout<<"3.Magenta(taken) ";
	}
	else{
		setColor(MAGENTA,BLACK);
		cout<<"3.Magenta ";
	}
	if(player1color==YELLOW){
		setColor(GREY,BLACK);
		cout<<"4.Yellow(taken) ";
	}
	else{
		setColor(YELLOW,BLACK);
		cout<<"4.Yellow";
	}
	setColor(WHITE,BLACK);
	cout<<endl;
	int pc;
	cout<<"Enter your choice(1-4): ";
	cin>>pc;
	while((pc<1||pc>4)||(pc==1&&player1color==BLUE)||(pc==2&&player1color==CYAN)||(pc==3&&player1color==MAGENTA)||(pc==4&&player1color==YELLOW)){
		if(pc==player1color){
			setColor(RED,BLACK);
			cout<<"That colour is already taken. ";
			setColor(WHITE,BLACK);
			cin>>pc;
		}
		else{
			cin>>pc;
		}	
		
	}
	cout<<"Players ready: "<<player1name<<" vs "<<player2name<<". Press Enter to deal";
	cin.get();
	system("CLS");
	return pc;
}
void output_main_screen(){
	cout<<"======================================"<<endl;
	cout<<"       WELCOME TO 502 CARD GAME"<<endl;
	cout<<"======================================"<<endl;
	cout<<"               MAIN MENU"<<endl;
	cout<<"--------------------------------------"<<endl;
	setColor(RED, BLACK);
	cout<< "1. ";
	setColor(GREY, BLACK);
	cout<<"Start New Game"<<endl;
	setColor(RED, BLACK);
	cout<< "2. ";
	setColor(GREY, BLACK);
	cout<<"Instructions"<<endl;
	setColor(RED, BLACK);
	cout<< "3. ";
	setColor(GREY, BLACK);
	cout<<"View Leaderboard"<<endl;
	setColor(RED, BLACK);
	cout<< "4. ";
	setColor(GREY, BLACK);
	cout<<"EXIT"<<endl;
	cout<<"--------------------------------------"<<endl;
}
int userChoice(){
	int x;
	cout<<"Enter your choice(1-4): ";
	cin>>x;
	while(x>4||x<1){
		cin>>x;
	}
	return x;
}
void displayinstruction(){
	system("CLS");
	cout<<"--------------------------------------"<<endl;
	cout<<"            INSTRUCTIONS              "<<endl;
	cout<<"--------------------------------------"<<endl;
	setColor(RED, BLACK);
	cout<< "1. ";
	setColor(GREY, BLACK);
	cout<<"Each player gets 7 cards.Empty your hand to win."<<endl;
	setColor(RED, BLACK);
	cout<< "2. ";
	setColor(GREY, BLACK);
	cout<<"Match the top card by suit or value, or press 0 to draw."<<endl;
	setColor(RED, BLACK);
	cout<< "3. ";
	setColor(GREY, BLACK);
	cout<<"J  : play on any card and choose the next suit."<<endl;
	setColor(RED, BLACK);
	cout<< "4. ";
	setColor(GREY, BLACK);
	cout<<"2  : next player draws 2 (answer with a 2)."<<endl;
	setColor(RED, BLACK);
	cout<< "5. ";
	setColor(GREY, BLACK);
	cout<<"A \u2660  : next player draws 5 (answer with any Ace)."<<endl;
	setColor(RED, BLACK);
	cout<< "6. ";
	setColor(GREY, BLACK);
	cout<<"8  : next player is skipped (answer with an 8)."<<endl;
	setColor(RED, BLACK);
	cout<< "7. ";
	setColor(GREY, BLACK);
	cout<<"7 \u2665  : play it and you win the round at once!"<<endl;
	setColor(RED, BLACK);
	cout<< "8. ";
	setColor(GREY, BLACK);
	cout<<"Card left in your hand are added to your total."<<endl;
	cout<< "9. ";
	cout<<"Reach 502 points and you lose the game."<<endl;	
	cout<<"--------------------------------------"<<endl;
	cout<<"(Press Enter to return to the Main Menu...)";
	cin.ignore();
	cin.get();
	system("CLS");
}
void clearscreen(){
	system("CLS");
}
int main(){
	SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
	bool running=true;
	while (running){
		output_main_screen();
		int choice=userChoice();
		if(choice==1){
			int playingtype=chooseplayingtype();
			if(playingtype==1){
				string player1name=Chooseplayer1name();
				int player1color;
				int p1c=Choseplayer1color(player1name);
				if(p1c==1){
					player1color=BLUE;
				}
				else if(p1c==2){
					player1color=CYAN;
				}
				else if(p1c==3){
					player1color=MAGENTA;
				}
				else{
					player1color=YELLOW;
				}
				string player2name=Chooseplayer2name(player1name);
				int player2color=Choseplayer2color(player2name,player1color,player1name);
			}
			else{

			}
			
		}
		if(choice==2){
			displayinstruction();
		}
		else if(choice==4){
			running=false;
		}

	}

	return 0;
}
