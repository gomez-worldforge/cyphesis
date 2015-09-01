//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _CHESSTREEGRID_UTILAI_H_
#define _CHESSTREEGRID_UTILAI_H_

#include "ChessRam.hpp"
/*
 */

namespace utilai
{
namespace tree 
{
namespace chess 
{

class Grid 
{
public:
	explicit Grid() : chessram() {}
	~Grid() {}

	int strikeWith(ChessPieceNum striker, ChessPieceNum n) {
		return chessram.strikeWith(striker,n);
	}

private:
	ChessRam chessram;	
};

}//namespace chess 
}//namespace tree 
}//namespace utilai
#endif	
