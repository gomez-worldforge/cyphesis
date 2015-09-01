//This file is distributed under the terms of the GNU General Public license.
//Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).
#ifndef _NN_UTILAI_H_
#define _NN_UTILAI_H_

#include<list>
#include<cmath>
#include <algorithm>
#include <functional>

#include "Pair.hpp"
#include "Vector.hpp"

namespace utilai
{
namespace nn 
{
typedef std::vector<Pair<math::Vector<float>, math::Vector<float> > > PatternVector;
typedef std::vector<Pair<math::Vector<float>, math::Vector<float> > >::iterator PatternVectorIter;

class NN 
{

public:
class Neuron;
class Connection;

typedef std::list<Neuron> NeuronList;
typedef std::list<Connection> ConnectionList;
typedef std::list<Neuron>::iterator NeuronListIter;
typedef std::list<Connection>::iterator ConnectionListIter;

class SigmoidBase
{
public:
	SigmoidBase() : activation(0.33) {}
	~SigmoidBase() {}
	virtual void run (Neuron *) {}	
protected:
	float activation;
};

class SigmoidBPN0 : public SigmoidBase
{
public:
	SigmoidBPN0() : SigmoidBase(), learningrate(0.5) {}
	~SigmoidBPN0(){}

	void run(Neuron& n) { n.activate(-learningrate * 1 / (1 + std::exp(activation))); } 

private:
	float learningrate;
};
class SigmoidBPN1 : public SigmoidBase
{
public:
	SigmoidBPN1() : SigmoidBase() {}
	~SigmoidBPN1(){}

	void run(Neuron& n) { n.activate(-learningrate * 1 / (1 + activation)); } 

private:
	float learningrate;
};
class SigmoidBPN2 : public SigmoidBase
{
public:
	SigmoidBPN2() : SigmoidBase(), learningrate(0.5) {}
	~SigmoidBPN2(){}

	void run(Neuron& n) { n.activate(-learningrate * 1 / (1 + std::tan(activation))); } 

private:
	float learningrate;
};

class Neuron
{
public:
	Neuron() : activation(0.33) {}
	~Neuron() {}

	float get() { return activation; }	
	ConnectionList getInConnections() { return inputs; }	
	ConnectionList getOutConnections() { return outputs; }	
	void activate(float x) { activation = x; } 
	void forward(SigmoidBase& sigmoid, float x) { 
		activation = x;
		sigmoid.run(this); 

		for (ConnectionListIter vi = outputs.begin();
			vi != outputs.end();
			vi++) {
			(*vi).forward(sigmoid, activation);
		} 

	}

	void addInput(Connection &c) { inputs.push_back(c); } 
	void addOutput(Connection &c) { outputs.push_back(c); } 

private:
	ConnectionList inputs;
	ConnectionList outputs;
	float activation;
public:			
private:
};
class Connection 
{
public:
	Connection() : weight(0.33) {}
	~Connection() {}
	
	void setInput(Neuron& c) { input = c; } 
	Neuron getOutput() { return output; } 
	Neuron getInput() { return input; } 
	void setOutput(Neuron& c) { output = c; } 

	float dot(float x) { return x*weight; } 
	float activate(float x) { return dot(x); }

	void operator-(float x) { weight -= x; } 
	float get() { return weight; }

	void forward(SigmoidBase& sigmoid, float activation) {
		 
		output.forward(sigmoid, activation);
	}


private:
	Neuron input;
	Neuron output;	
	float weight;

};



public:
	explicit NN(int insize, int hiddensize, int outsize);
	virtual ~NN();

	math::Vector<float> test(math::Vector<float>& pattern);	
	bool propagate(math::Vector<float> inputpattern, math::Vector<float> outputpattern);
	int backpropagate(math::Vector<float>& inputpattern, math::Vector<float>& outputpattern);
	
	int getinputsize() { return inputneurons.size(); }
	int getoutputsize() { return outputneurons.size(); }
	int gethiddensize() { return hiddenneurons.size(); }


private:
	inline ConnectionListIter transformIn(ConnectionList l) {
		return l.begin();	
	}
	inline ConnectionListIter transformOut(ConnectionList l) {
		return l.end();
	}
			
private:
	NeuronList inputneurons;
	NeuronList outputneurons;
	NeuronList hiddenneurons;	
	float alpha;
	SigmoidBase *sigmoid;

};
}//namespace nn
}//namespace utilai
#endif	
