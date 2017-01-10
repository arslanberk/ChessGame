#include "menu.h"
#include <iostream>

using namespace std;

menu::menu()
{
	system("TITLE Chess Game © Berk Arslan");
	system("COLOR 17");
	cout << "Chess Game:" << "\n";
	cout << "1)Play!" << "\n";
	cout << "2)How to Play?" << "\n";
	cout << "3)Exit!" << "\n";
	cin >> c;
}
void menu::play()
{
	system("CLS");
	cout << "How to Play:" << "\n";
	cout << "->" << "\n";
	cout << "First left-click is for selecting your figure, and the second left-click is for moving." << "\n";
	cout << "Player can play only in his/her turn." << "\n";
	cin.get();
	cin.get();
}