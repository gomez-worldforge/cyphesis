//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _PAIR_UTILAI_H_
#define _PAIR_UTILAI_H_

#include<iostream>
#include<vector>

namespace utilai
{
namespace nn 
{

template<class First, class Second> 
class Pair
{
public:
	explicit Pair(First f, Second s);
	virtual ~Pair();

	First first() { return _first; }  
	Second second() { return _second; } 

private:
	Second _second;
	First _first;
};
}//namespace vector
}//namespace utilai
#endif	
