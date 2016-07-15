//
//  minesweeper.cpp
//  minesweeper
//
//  Created by Leo Dastur on 7/13/16.
//
//

#include "minesweeper.hpp"

MinesweperGame::MinesweperGame(int height, int width, int mineCount) {
	this->height = height;
	this->width = width;
	this->mineCount = mineCount;
	
	
	
	
	// Generate mineCount mine locations
	srand ((unsigned int) time(NULL));
	std::list<BoardCoordinate> mines;
	//std::unordered_map<BoardCoordinate, bool, BCHasher> mines;
	for (int i = 0; i<mineCount; i++) {
		bool retry = false;
		do {
			BoardCoordinate mine(rand() % width, rand() % height);
			// TODO: Use Map for mines to reduce running time
			if (std::find(mines.begin(), mines.end(), mine) == mines.end()) {
				mines.push_back(mine);
				retry = false;
			} else retry= true;
		} while (retry);
		
	}
	
	// init board
	for (int x = 0; x < width; x++) {
		board.emplace(board.end());
		for (int y = 0; y < height; y++) {
			int cellValue = 0;
			board[x].push_back(std::make_tuple(FOGGY, cellValue));
		}
	}
	// set mines and clues
	for (std::list<BoardCoordinate>::iterator iter = mines.begin(); iter != mines.end(); iter++) {
		BoardCoordinate cMine = *iter;
		std::get<1>(board[cMine.x][cMine.y]) = -1;
		//for all 6 adjacent cells that aren't a mine, increase value
		
		for (int x = -1; x<2; x++) {
			for (int y = -1; y<2; y++) {
				BoardCoordinate * tempMine = new BoardCoordinate(cMine, x, y);
				if (tempMine->x >= 0 && tempMine->y >= 0 && tempMine->x < width && tempMine->y < height) {
					if (std::get<1>(*getCellPtr(*tempMine)) != -1) {
						std::get<1>(*getCellPtr(*tempMine))++;
					}
				}
				
				delete tempMine;
			}
		}
		
	}
	
	
}

MinesweperGame::BoardCoordinate::BoardCoordinate() {}

MinesweperGame::BoardCoordinate::BoardCoordinate(int x, int y) {
	this->x = x;
	this->y = y;
}
MinesweperGame::BoardCoordinate::BoardCoordinate(const BoardCoordinate& old, int xAdd, int yAdd) {
	x = old.x+xAdd;
	y = old.y+yAdd;
}
bool MinesweperGame::BoardCoordinate::operator==(const MinesweperGame::BoardCoordinate &b) const {
	//std::cout << "\nCalled operator== of BoardCoordinate! Value:" << x << " and " <<b.x << ";   " << y << " and " << b.y;
	return (x == b.x && y == b.y);
}

int MinesweperGame::getCell(int x, int y) {
	if (x >=width || y >=height) {
		throw invalidCell;
	} else {
		Cell * cell = getCellPtr(BoardCoordinate(x,y));
		if (std::get<0>(*cell) == FOGGY) {
			return -2;
		}
		return std::get<1>(*cell);
	}
}

void MinesweperGame::probeCell(int x, int y) {
	if (status == WON || status == LOST) {
		throw gameOver;
	}
	std::cout << "\nProbing " << x << ", " << y;
	BoardCoordinate coord(x,y);
	Cell * cell = getCellPtr(coord);
	int value = std::get<1>(*cell);
	switch (value) {
		case -1:
			std::get<0>(*cell) = DISCOVERED;
			status = LOST;
			break;
		case 0:
			revealAdjacent(coord);
			checkWin();
			
			break;
		default:
			std::get<0>(*cell) = DISCOVERED;
			checkWin();
			break;
	}
}

void MinesweperGame::revealAdjacent(MinesweperGame::BoardCoordinate coord) {
	if (std::get<1>(*getCellPtr(coord)) == 0 && std::get<0>(*getCellPtr(coord))== FOGGY) {
		std::get<0>(*getCellPtr(coord)) = DISCOVERED;
		
		if (coord.x<width-1) {
			revealAdjacent(BoardCoordinate(coord,1,0));
		}
		if (coord.x>0) {
			revealAdjacent(BoardCoordinate(coord,-1,0));
		}
		if (coord.y<height-1) {
			revealAdjacent(BoardCoordinate(coord,0,1));
		}
		if (coord.y>0) {
			revealAdjacent(BoardCoordinate(coord,0,-1));
		}
		
	}
}

MinesweperGame::Cell * MinesweperGame::getCellPtr(BoardCoordinate c) {
	return &board[c.x][c.y];
}

void MinesweperGame::checkWin() {
	for (auto column : board) {
		for (auto cell : column) {
			CellFog fogginess = std::get<0>(cell);
			int value = std::get<1>(cell);
			if (value !=-1) {
				return;
			}
		}
	}
	std::cout << "Game Won!";
	status = WON;
}

