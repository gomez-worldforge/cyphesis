//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "NNMatrix.hpp"
#include<cmath>

namespace utilai
{
namespace nnmat 
{

NNMatrix::NNMatrix(int i, int h, int o)
	: insize(i), outsize(o), hiddensize(h), epsillon(0.001 * h * o * i), 
	W1(math::Matrix<float>(i,h)), W2(math::Matrix<float>(h,o)),
	inlayer(math::Vector<float>(i)), hiddenlayer(math::Vector<float>(h)),outlayer(math::Vector<float>(o))

{}

void NNMatrix::reinit(int i, int h, int o) 
{
	insize = i; 
	outsize = o;
	hiddensize = h;
	epsillon = 0.001 * h * o * i; 
	W1 = math::Matrix<float>(i,h);
	W2 = math::Matrix<float>(h,o);
	inlayer = math::Vector<float>(i);
	hiddenlayer = math::Vector<float>(h);
	outlayer = math::Vector<float>(o);
}

NNMatrix::~NNMatrix()
{}

void NNMatrix::propagateforward(const math::Vector<float> &insizepattern)
{

	inlayer = insizepattern;
	math::Vector<float> vih(W1.getrows());
	vih = W1 * inlayer;
	//apply sigmoid function and set
	vih.transform();
	
	math::Vector<float> vho(W1.getrows());
	vho = W2 * outlayer;
	//apply sigmoid function and set
	vho.transform();
	outlayer = vho;

}

bool NNMatrix::propagate(const math::Vector<float> &insizepattern, const math::Vector<float> &outsizepattern)
{
	propagateforward(insizepattern);

	if (outlayer.dot(outsizepattern) < epsillon)
		return true;
	else
		return false;
}

void NNMatrix::backpropagate(const math::Vector<float> outsizepattern)
{

	math::Vector<float> errorov(const_cast<math::Vector<float> &>(outsizepattern).getcols());
	errorov = outlayer - outsizepattern;
	errorov -= 1.0;
	math::Vector<float> alphaveco(errorov.getcols());
	alphaveco.mulcollect(-alpha);
	float errorW1 = errorov.dot(alphaveco);

	W1 -= errorW1;

	math::Vector<float> errorhv(const_cast<math::Vector<float> &>(outsizepattern).getcols());
	errorhv = outlayer - outsizepattern;
	errorhv -= 1.0;
	math::Vector<float> alphavech(errorhv.getcols());
	alphavech.mulcollect(-alpha);
	float errorW2 = errorhv.dot(alphavech);

	W2 -= errorW2;
}

math::Vector<float> NNMatrix::test(const math::Vector<float> &insizepattern)
{
	propagateforward(insizepattern);
	return outlayer;
}

int NNMatrix::run(const math::Vector<float> & inpattern, const math::Vector<float> & outpattern)
{

	while (true) {

		if (!propagate(const_cast<math::Vector<float> &>(inpattern),
				const_cast<math::Vector<float> &>(outpattern))) {

			backpropagate(outpattern);
		} else { return 1; }
	}
}

void NNMatrix::runnable(const PatternVector& patterns)
{
	int idx;
	while (true) {
		if (idx > patterns.size()) 
			break;				
		if (run(const_cast<PatternVector &>(patterns)[idx].first(), 
			const_cast<PatternVector &>(patterns)[idx].second())) {
			//learned a pattern
			idx++;
		}
	}
}

}//namespace nnmat 
}//namespace utilai	
