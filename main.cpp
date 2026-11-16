#include<iostream>
#include <windows.h>
#include<cstdlib>
#include<iomanip>
using namespace std;

void output_main_screen(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout<<"======================================"<<endl;
	cout<<"       WELCOME TO 502 CARD GAME"<<endl;
	cout<<"======================================"<<endl;
	cout<<"               MAIN MENU"<<endl;
	cout<<"--------------------------------------"<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "1. ";
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"Start New Game"<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "2. ";
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"Instructions"<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "3. ";
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"View Leaderboard"<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "4. ";
	SetConsoleTextAttribute(hConsole, 7);
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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout<<"--------------------------------------"<<endl;
	cout<<"            INSTRUCTIONS              "<<endl;
	cout<<"--------------------------------------"<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "1. ";
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"Each player gets 7 cards.Empty your hand to win."<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "2. ";
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"Match the top card by suit or value, or press 0 to draw."<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "3. ";
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"J  : play on any card and choose the next suit."<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "4. ";
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"2  : next player draws 2 (answer with a 2)."<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "5. ";
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"A \u2660  : next player draws 5 (answer with any Ace)."<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "6. ";
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"8  : next player is skipped (answer with an 8)."<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "7. ";
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"7 \u2665  : play it and you win the round at once!"<<endl;
	SetConsoleTextAttribute(hConsole, 4);
	cout<< "8. ";
	SetConsoleTextAttribute(hConsole, 7);
	cout<<"Card left in your hand are added to your total."<<endl;
	cout<< "9. ";
	cout<<"Reach 502 points and you lose the game."<<endl;	
	cout<<"--------------------------------------"<<endl;
	cout<<"(Press Enter to return to the Main Menu...)"<<endl;
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
		if(choice==2){
			displayinstruction();
		}
		else if(choice==4){
			running=false;
		}

	}

	return 0;
}