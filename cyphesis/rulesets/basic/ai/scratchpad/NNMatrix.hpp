//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _NNMatrix_UTILAI_H_
#define _NNMatrix_UTILAI_H_

#include<iostream>
#include<vector>

#include "Matrix.hpp"
#include "Pair.hpp"

/*
 * PatternVector is a vector of Vector instances which are paired as in and output. 
 */

namespace utilai
{
namespace nnmat 
{
typedef std::vector<Pair<math::Vector<float>, math::Vector<float> > > PatternVector;

class NNMatrix 
{
public:
	explicit NNMatrix(int i, int h, int o);
	virtual ~NNMatrix();

	void runnable(const PatternVector& patterns);
	math::Vector<float> test(const math::Vector<float>& inpattern);
	void reinit(int i, int h, int o);

	int getinsize() { return insize; }
	int gethiddensize() { return hiddensize; }
	int getoutsize() { return outsize; }



private:
	void propagateforward(const math::Vector<float> &);
	bool propagate(const math::Vector<float> &, const math::Vector<float> &);
	void backpropagate(const math::Vector<float> outsizepattern);
	int run(const math::Vector<float> & inpattern, const math::Vector<float> & outpattern);

private:
	int insize,outsize,hiddensize;
	math::Matrix<float> W1,W2;
	math::Vector<float> inlayer,hiddenlayer,outlayer;


	float epsillon,alpha;
};
}//namespace nnmat 
}//namespace utilai
#endif	
