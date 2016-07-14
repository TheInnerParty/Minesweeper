//
//  minesweeper.hpp
//  minesweeper
//
//  Created by Leo Dastur on 7/13/16.
//
//

#ifndef minesweeper_hpp
#define minesweeper_hpp

#include <vector>
#include <tuple>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <random>
#include <time.h>
#include <iostream>
#include "minesweeperExceptions.hpp"

class MinesweperGame {

public:
	MinesweperGame(int height = 20, int width = 20, int mineCount = 15);
	enum GameStatus {ACTIVE = 0, WON, LOST};
	GameStatus status;
	int getCell(int x, int y);
	void probeCell(int x, int y);
	
	int height;
	int width;
	int mineCount;
	
	
private:
	struct BoardCoordinate {
		BoardCoordinate();
		BoardCoordinate(int x, int y);
		BoardCoordinate(const BoardCoordinate& old, int xAdd, int yAdd);
		bool operator==(const BoardCoordinate& b) const;
		int x;
		int y;
	};
	enum CellFog {FOGGY=0, DISCOVERED};
	
	typedef std::tuple<CellFog, int> Cell; //-1 = mine, 0 = blank 1+ = clue ... -2 is for public fog

	std::vector<std::vector<Cell>> board;
	
	
	Cell * getCellPtr(BoardCoordinate coord);
	void revealAdjacent(BoardCoordinate coord);
	void checkWin();
	
	
};

#endif /* minesweeper_hpp */
