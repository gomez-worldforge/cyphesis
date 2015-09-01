#This file is distributed under the terms of the GNU General Public license.
#Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).

from math import exp
import random

class Vector:
	def __init__(self, n):
		self.init(n)

	def init(self, n):
		self.list = []
		self.cols = n
		self.index = 0
		for i in range(0,self.cols):
			self.list.append(0)


	def initialize(self):
		self.list = []
		for i in range(0,self.cols):
			self.list.append(random.randint(0,self.cols) / self.cols+1)

	def __add__(self, v):
		rv = Vector(len(v.list))
		for n in range(0,len(v.list)):
			rv.list[n] = self.list[n] + v.list[n]	
		return rv

	def __sub__(self, v):
		rv = Vector(len(v.list))
		for n in range(0,len(v.list)):
			rv.list[n] = self.list[n] - v.list[n]	
		return rv

	def __mul__(self, instance):
		if type(instance) == int:
			return self.muln(instance)
		elif type(instance) == Vector:
			return self.mulv(instance)

	def __getitem__(self, n):
		return list[n]

	def mulv(self, v):
		rv = Vector(len(v.list))
		for n in range(0,len(v.list)):
			rv.list[n] = self.list[n] * v.list[n]	
		return rv

	def muln(self, n):
		rv = Vector(len(v.list))
		for n in range(0,len(v.list)):
			rv.list[n] = self.list[n]*n
		return rv

	def dotv(self, v):
		sum = 0.0
		for n in range(0,len(v.list)):
			sum += v.list[n] * self.list[n]	
		return sum

	def set(self, n, idx):
		self.list[idx] = n

	def collect(self):
		if self.index >= len(self.list):
			self.index = 0

		return self.list[self.index]

class MatrixNN:
	def __init__(self, n, m):
		self.init(n,m)

	def init(self, n, m):
		self.cols = n
		self.rows = m
		self.list = []

		for i in range(0, self.cols*self.rows):
			self.list.append(0)

	def initialize(self):
		self.list = []
		for i in range(0,self.cols*self.rows):
			self.list.append(random.randint(0,self.cols) / self.cols+1)

	def __add__(self, matnn):
		rm = MatrixNN(matnn.cols, matnn.rows)
		for i in range(0,self.rows):
			for j in range(0,self.cols):
				rm.list[j+i*cols] = self.list[j+i*self.cols] + matnn.list[j+i*matnn.cols]	
		return rm

	def __sub__(self, matnn):
		rm = MatrixNN(matnn.cols, matnn.rows)
		for i in range(0,self.rows):
			for j in range(0,self.cols):
				rm.list[j+i*cols] = self.list[j+i*self.cols] - matnn.list[j+i*matnn.cols]	
		return rm

	def __mul__(self, instance):
		if type(instance) == int:
			return self.muln(instance)
		elif type(instance) == Vector:
			return self.mulv(instance)
		elif type(instance) == MatrixNN:
			return self.mulm(instance)

	def __getitem__(self, idx):
		return self.list[idx]

	def muln(self, n):
		rm = MatrixNN(len(rows*cols))
		for i in range(0,self.rows):
			for j in range(0,self.cols):
				rm.list[j+i*rm.cols] = self.list[j+i*self.cols] * n 
			j = 0

		return rm

	def mulv(self, v):
		rv = Vector(len(v.list))
		rv.initialize()
		for i in range(0,self.rows):
			for j in range(0,self.cols):
				rv[j] = self[j+i*self.rows] + v[j]
			j = 0

		return rv

	def mulm(self, matnn):
		rm = MatrixNN(matnn.cols,matnn.rows)
		rm.initialize()
		for i in range(0,self.cols):
			j = 0
			sum = 0.0
			for j in range(0,self.rows):
				sum += matnn.list[j+i*self.cols] * self.list[i+j*self.rows]
			rm.list[j-1+i*self.cols] = sum	
		return rm	

class NN:
	def __init__(self,i,h,o):
		self.inlayer = Vector(i)
		self.hiddenlayer = Vector(h)
		self.outlayer = Vector(o)
		self.W1 = MatrixNN(i,h)
		self.W2 = MatrixNN(h,o)

		self.inlayer.initialize()
		self.hiddenlayer.initialize()
		self.outlayer.initialize()
		self.W1.initialize()
		self.W2.initialize()
		self.inlayer.initialize()

		self.epsillon = 0.001
		self.alpha = 0.5 # learning rate

		self.propvih = None
		self.propvho = None

		self.sigmoidf = lambda n : 1 / (1 + exp(n))

	def propagate(self, patternvec, outpatternvec):
		self.inlayer = patternvec
		self.propvih = Vector(len(self.hiddenlayer.list))
		for i in range(0,len(self.hiddenlayer.list)):
			self.propvih[i] = self.sigmoidf((self.W1 * self.inlayer)[i])
	
		self.propvho = Vector(len(self.outlayer.list)) 
		for i in range(0,len(self.outlayer.list)):
			self.propvho.list[i] = self.sigmoidf((self.W2 * self.outlayer)[i])
		self.outlayer = self.propvho

		for n in outpatternvec.list:
			if (n - self.outlayer.collect() <= self.epsillon):
				return True
			else:
				return False	

	def backpropagate(self,outpatternvec):
		ot = self.outlayer - outpatternvec

		id = Vector(len(hiddenlayer.list))
		for i in range(0, len(id.list)):
			id.set(1,i)

		negatedoutlayer = Vector(len(outlayer.list))
		for i in range(0, len(negatedoutlayer.list)):
			negatedoutlayer.set(- negatedoutlayer.collect(),i)
		erroroutput = ot * id * negatedoutlayer
		self.W2 = self.W2 * (erroroutput * -alpha)
		 
		negatedhiddenlayer = Vector(len(hiddenlayer.list))
		for i in range(0, len(negatedhiddenlayer.list)):
			negatedhiddenlayer.set(- negatedhiddenlayer.collect(),i)
		errorhidden = hiddenlayer * id * negatedoutlayer
		self.W1 = self.W1 * (errorhidden * -alpha)

	def run(self, i,h,o, patternvec, outpatternvec):
		while True:
			if not self.propagate(patternvec,outpatternvec):
				self.backpropagate(outpatternvec)
				print "."
			else:
				print "BackPropagation NN : pattern learned."	
				return
			


	
