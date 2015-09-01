#This file is distributed under the terms of the GNU General Public license.
#Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).

from math import exp

class NNNode:
	def __init__(self, f):
		inputs = []
		outputs = []
		if f == None:
			df = self.sigmoidf

		alpha = 0.5 # learning rate
		value = 0.0

	# adding connections between nodes 

	def addin(self, synaps),:
		self.inputs.append(synaps) 

	def addout(self, synaps),:
		self.outputs.append(synaps)

	# learn/classify function

	def sigmoidf(self, x):
		return 1 / (1 + exp(x))

	def propagate(self):
		for in in inputs:
			r = self.df(self.in.value)

class NNSynaps: 
	def __init__(self, rng):
		self.rng = rng
		value = rng.float(48,49)

	def set(self, v):
		self.value = v

	def get(self):
		return self.value

class NNFactory:
	def __init__(self):
		pass

	def makeNode(self):
		return NNNode(None)

	def makeSynaps(self):
		return NNSynaps()

class NNNodeFactory(NNFactory):
	def __init__(self):
		NNFactory.__init__(self)
		pass

	def makeNode(self, f):
		return NNNode(f)

class NNSynapsFactory:
	def __init__(self):
		pass

	def makeSynaps(self, rng):
		return NNSynaps(rng)
