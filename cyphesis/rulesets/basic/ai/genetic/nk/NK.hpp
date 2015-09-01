//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _NK_UTILAI_H_
#define _NK_UTILAI_H_

#include<iostream>
#include<vector>

/*
 */

namespace utilai
{
namespace nk 
{
class NK 
{
typedef std::vector<float> FitnessVector;
typedef std::vector<float>::iterator FitnessVectorIter;

public:
	explicit NK(int size); 
	virtual ~NK();
	int init(int size);
	void reinit(int size);
	float run();
	float runfor(int t);

private:
	void mutater();
	void mutater2(int);
	float calcfitness();
private:
	FitnessVector fitnessvector;
	FitnessVector inputs;
	FitnessVector outputs;
	float fitness;
};
}//namespace nk 
}//namespace utilai
#endif	
