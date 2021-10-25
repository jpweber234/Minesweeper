#include <iostream>
#include <random>
#include <ctime>
#define BOARDSIZE 25

using namespace std;

namespace boardinitialize
{
	
	inline char getGameType() //gets game difficulty via user input
	{
		char type{};
		cout << "Enter game difficulty: ";
		cin >> type; //char should be B: Beginner, I: Intermediate, E: Expert, or C: Custom
		return type;
	}

	inline int getHorizontalDimension(char gameType) //determines dimensions of board based on difficulty
	{
		int x{};

		switch (gameType)
		{
		case 'C':
			cout << "Enter the horizontal dimension: ";
			cin >> x;
			break;
		case 'B':
			x = 5;
			break;
		case 'I':
			x = 9;
			break;
		case 'E':
			x = 12;
			break;
		}
		
		return x;
	}

	inline int getVerticalDimension(char gameType) //determines dimensions of board based on difficulty
	{
		int y{};

		switch (gameType)
		{
		case 'C':
			cout << "Enter the vertical dimension: ";
			cin >> y;
			break;
		case 'B':
			y = 5;
			break;
		case 'I':
			y = 9;
			break;
		case 'E':
			y = 12;
			break;
		}

		return y;
	}

	inline int getMines(char gameType) //determines number of mines based on difficulty
	{
		int m{};

		switch (gameType)
		{
		case 'C':
			cout << "Enter the horizontal dimension: ";
			cin >> m;
			break;
		case 'B':
			m = 4;
			break;
		case 'I':
			m = 10;
			break;
		case 'E':
			m = 25;
			break;
		}

		return m;
	}

	/*inline void boardInfo(int x, int y, int m) //prints board info
	{
		cout << "The board is " << x << " by " << y << ", and there are " << m << " mines\n\n";

	}*/
}