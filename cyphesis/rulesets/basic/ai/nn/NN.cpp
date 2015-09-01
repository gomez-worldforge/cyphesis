//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).


#include "NN.hpp"

#include "Vector.hpp"

namespace utilai
{
namespace nn 
{

NN::NN(int insize, int hiddensize, int outsize)

	: alpha(0.5), sigmoid(new SigmoidBPN0())
{

	for (int i = 0; i < insize; i++) {
		Neuron *in = new Neuron;
		for (int j = 0; j < hiddensize; j++) {
			Neuron *hidden = new Neuron;
			Connection *c = new Connection;
			c->setInput(*in);
			c->setOutput(*hidden);
			in->addInput(*c);
			hidden->addOutput(*c);
			hiddenneurons.push_back(*hidden);
		}
		inputneurons.push_back(*in);	
	}
	for (NeuronListIter vi = hiddenneurons.begin(); vi != hiddenneurons.end(); vi++) {
		Neuron *out = new Neuron;
		for (int j = 0; j < outsize; j++) {
			Connection *c = new Connection;
			c->setInput(*vi);
			c->setOutput(*out);
			out->addInput(*c);
			(*vi).addOutput(*c);
		}
		outputneurons.push_back(*out);	
	}	
			
}

NN::~NN()
{
}

math::Vector<float> NN::test(math::Vector<float>& pattern)
{

	for (NeuronListIter vi = inputneurons.begin();
		vi != inputneurons.end(); vi++)  {

		(*vi).forward(*sigmoid, (float)pattern.collect());

	}
	utilai::math::Vector<float> rv(outputneurons.size());
	int i = 0;
	for (NeuronListIter vi = inputneurons.begin();
		vi != inputneurons.end(); vi++, i++)  {
			rv.set(i, (*vi).get());
	}	
	return rv;
}

bool NN::propagate(math::Vector<float> inputpattern, math::Vector<float> outputpattern)
{

	for (NeuronListIter vi = inputneurons.begin();
		vi != inputneurons.end(); vi++)  {

		(*vi).forward(*sigmoid, (float)inputpattern.collect());
	}
	math::Vector<float> ot(getoutputsize());
	int i = 0;
	for (NeuronListIter vi = outputneurons.begin();
		vi != outputneurons.end(); vi++, i++)  {
		if (std::abs((float)(*vi).get() - const_cast<math::Vector<float> &>(outputpattern)[i]) < 0.001) 
			continue;
		else
			return false;
	}
	return true;		
}

int NN::backpropagate(math::Vector<float>& inputpattern, math::Vector<float>& outputpattern) {
	math::Vector<float> o(getoutputsize());
	math::Vector<float> ot(getoutputsize());
	math::Vector<float> oid(getoutputsize());
	int i = 0;
	for (NeuronListIter vi = outputneurons.begin();
		vi != outputneurons.end(); vi++, i++) {
		o.setcollect((float)(*vi).get());
		ot.setcollect((float)(*vi).get() - outputpattern[i]);
		oid.setcollect(1 - (float)(*vi).get());
	}

	math::Vector<float> erroroutv = ot * o * oid - alpha;	
	float errorout = outputpattern.dot(erroroutv);	

	for (NeuronListIter vi = outputneurons.begin();
		vi != outputneurons.end(); vi++) {

		ConnectionListIter wi = transformIn((*vi).getInConnections());
		for ( ; wi != transformOut((*vi).getInConnections()); ) {
			(*wi++) - errorout;	
		}	
	}

	math::Vector<float> h(gethiddensize());
	math::Vector<float> ih(gethiddensize());
	math::Vector<float> hid(gethiddensize());
	int j;
	for (NeuronListIter vi = hiddenneurons.begin();
		vi != hiddenneurons.end(); vi++, j++) {
		h.setcollect((float)(*vi).get());
		ih.setcollect((float)(*vi).get()); //FIXME
		hid.setcollect(1 - (float)(*vi).get());
	}

	math::Vector<float> errorhidv = ih * h * hid - alpha;	
	float errorhid = outputpattern.dot(errorhidv);	

	for (NeuronListIter vi = hiddenneurons.begin();
		vi != hiddenneurons.end(); vi++) {

		ConnectionListIter wi = transformIn((*vi).getInConnections());
		for ( ; wi != transformOut((*vi).getInConnections()); ) {
			(*wi++) - errorhid;	
		}	
	}

	return 0;
}

}//namespace nnoo 
}//namespace utilai	
