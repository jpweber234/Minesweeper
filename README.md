# Minesweeper

Minesweeper is a logic game in which the user reveals squares of the gameboard, which are labeled with the number of mines adjacent to that square. The object of the game is to reveal all of the squares that are not occupied by mines. If you click reveal a square that contains a mine, you lose. 

This was my first major coding project, so it is implemented a little more simply than the official game. Squares are selected by inputting it's coordinates (standard matrix format), and then specifying the action the user whiches to execute. The user can enter 'C' to reveal the square (and possibly adjacent squares), or 'F' to mark the square as a mine.

The code creates 2 boards, one of which is displayed to the user (the gameBoard), and the "answer key" board (the mineBoard), which is not displayed to the user as it shows what the completed board will look like. The game is won when the gameBoard matches the mineBoard, so all mines must be marked and all other squares revealed in order to win.

The game has several built in difficulty levels as well as a custom board option. This option is specificed by the user before the game begins. The dimensions for each difficulty are listed below:

***Beginner: 5 X 5 board, 4 mines  
Intermediate: 9 X 9 board, 10 mines  
Expert: 12 X 12 board, 25 mines***

This project has known issues/shortcomings, which can be viewed in the Issues tab. Enjoy!
