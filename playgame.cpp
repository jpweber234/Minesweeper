#include <iostream>

using namespace std;

namespace playgame
{
	inline int getXCoord() //gets X Coordinate from user
	{
		int x{};
		cout << "Enter X Coordinate: ";
		cin >> x;
		return x;
	}

	inline int getYCoord() //gets Y Coordinate from user
	{
		int x{};
		cout << "Enter Y Coordinate: ";
		cin >> x;
		return x;
	}

	inline char getAction() //gets action from user (C for Click, F for Flag)
	{
		char action{};
		cout << "Click or Flag (C for Click, F for Flag): ";
		cin >> action;
		return action;
	}

	/*inline char executeAction(char action)
	{
		if (action == 'C')
			return 'O';
		else
			return 'F';
	}*/

}