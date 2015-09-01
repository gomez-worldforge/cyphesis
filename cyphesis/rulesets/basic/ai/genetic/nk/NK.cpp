//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "NK.hpp"
#include<cstdlib>
#include<cmath>

namespace utilai
{
namespace nk 
{

NK::NK(int size)
{
	(int)init(size);
}	

int NK::init(int size) 
{
	fitnessvector.reserve(size);
	//Too much entropy
	for (int i = 0; i < (int)fitnessvector.size(); i++) {	
		fitnessvector.push_back(std::rand()/RAND_MAX);
	}
	//Good entropy
	/****
	for (int i = 0; i < (int)fitnessvector.size(); i++) {	
		float r = std::rand()/RAND_MAX;
		if (r > RAND_MAX / 2)
			fitnessvector.push_back(1);
		else
			fitnessvector.push_back(0);
	}
	*****/

	fitness = 0.999999;

	int l = fitnessvector.size();
	float r;
	for (int i = 0; i < (int)fitnessvector.size(); i++) {
		if (l == 0)
			r = std::sqrt (l); 
		else
			r = 0.0;	
			
		outputs[i] = l;
		l = r - i;
	}

	return 0;
}

void NK::reinit(int size) 
{
	init(size);
}

NK::~NK()
{}

void NK::mutater()
{

	int r = std::rand();
	r %= fitnessvector.size();

	int r2 = std::rand();
	if (r2 > RAND_MAX / 2) 
		fitnessvector[r] += std::rand()/RAND_MAX;
	else	
		fitnessvector[r] -= std::rand()/RAND_MAX;

}

void NK::mutater2(int idx)
{
	fitnessvector[idx] += std::rand()/RAND_MAX;	
}

float NK::run()
{

	for (int i = 0; i < (int)fitnessvector.size(); i++) {
		for (int j = 0; j < (int)outputs.size(); j++) {
			mutater2(i);	
		}
	}

	fitness = calcfitness();
	if (fitness > 0.9) {
		std::cout<<"fitness is converging."<<std::endl;
	} else {
		run();
	}	
	return fitness;		
}

float NK::runfor(int t)
{

	for (int i = 0; i < (int)fitnessvector.size(); i++) {
		for (int j = 0; j < (int)outputs.size(); j++) {
			mutater2(i);	
		}
	}

	fitness = calcfitness();
	if (fitness > 0.9) {
		std::cout<<"fitness is converging."<<std::endl;
	} else if (t <= 0) {
		return fitness;
	} else {
		runfor(t-1);
	}	
	return fitness;		
}

float NK::calcfitness()
{
	float f = 0.0;
	for (int i = 0; i < (int)fitnessvector.size(); i++) {
		f += fitnessvector[i];
	}
	return f / fitnessvector.size();
}
}//namespace nk 
}//namespace utilai	
