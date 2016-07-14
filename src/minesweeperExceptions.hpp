//
//  minesweeperExceptions.hpp
//  minesweeper
//
//  Created by Leo Dastur on 7/13/16.
//
//

#ifndef minesweeperExceptions_hpp
#define minesweeperExceptions_hpp

#include <exception>


class InvalidCell: public std::exception
{
	virtual const char* what() const throw()
	{
		return "Cell does not exist.";
	}
} invalidCell;



class GameOver: public std::exception
{
	virtual const char* what() const throw()
	{
		return "Game is already complete.";
	}
} gameOver;

#endif /* minesweeperExceptions_hpp */
