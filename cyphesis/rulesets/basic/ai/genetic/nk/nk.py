#This file is distributed under the terms of the GNU General Public license.
#Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).

# This is an implmentation of the NK and NKd genetic algorithms

#from ai.util.rng import RNG
import random 
from math import sqrt,exp

#
# use a run method to make the NK system fitter
#

class NK:

	class FitnessVector:
		def __init__(self, size):
			self.vector = []
			### Too much entropy 
			for i in range(0,size):
				r = random.randint(0,100000)
			 	r2 = random.randint(0,100000)
			 	self.vector.append((float)(min(r,r2)/max(r,r2)))

			### Good entropy
			#for i in range(0, size):
			#	if (random.randint(0,1) == 1):
			#		self.vector.append(-1)
			#	else:
			#		self.vector.append(1)

		def max(self, r, r2):
			if r >= r2:
				return r	
			else:
				return r2	
			
		def min(self, r, r2):
			if r >= r2:
				return r2	
			else:
				return r	
			

		def mutate(self,idx):
			if (idx <= 0 or idx >= len(self.vector)):
				idx = len(self.vector) -1
			self.vector[idx] = -self.vector[idx]	

		def mutater(self,idx):
			if (idx <= 0 or idx >= len(self.vector)):
				idx = len(self.vector) -1
			r = random.randint(0,1000000)	
			r2 = random.randint(0,1000000)

			if random.randint(0,1) == 0:	
				self.vector[idx] += (float)(min(r,r2) / max(r,r2)) 
			else:
				self.vector[idx] -= (float)(min(r,r2) / max(r,r2)) 

		# vectors must be of same size
		def crossover(self, vector):
			r = random.randint(0, len(self.vector)-1)
			r2 = random.randint(0, len(self.vector)-r-1)

			for i in range(r2,r):
				self.vector[i] = vector[i]	

	def __init__(self,size):
		self.v = NK.FitnessVector(size) 		
		self.i = NK.FitnessVector(size)
		self.o = NK.FitnessVector(size)
		self.f = 0.9999999 
		self.initsqrt()

	def initsqrt(self):
		l = len(self.v.vector) 
		for i in range(0,len(self.v.vector)):
			if l == 0:
				r = sqrt(l)
			else:
				r = 0
			self.o.vector[i] = l 
			l = r - i
		self.v.vector.reverse() 
	
	def initexp(self):
		j = 0
		r = exp(random.randint(0,len(self.v)))
		if r > len(self.v):
			r = len(self.v);
		else:
			r = sqrt(l);
		for i in range(0, r):
			self.o.vector[j] = i
			j += 1
		
	def run(self):
		for i in range(0, len(self.o.vector)):
			self.v.mutate(i)
		if (self.run_rec()):
			return
		else:
			self.run()	

	def runadd(self):
		for j in range(0, len(self.v.vector)):
			for i in range(0, len(self.o.vector)):
				self.v.mutater(j)

		for i in range(0, len(self.v.vector)):
			if (self.v.vector[i] > 1):
				self.v.vector[i] = 1
	
		if (self.run_rec()):
			return
		else:
			self.runadd()	

	def run_rec(self):
		f = self.fitness()
		if f > 0.8:
			print "fitness is converging"
			return True
		else:
			print "fitness=%f" % f
			self.f = f
			return False 
			

	def fitness(self):
		sum = 0
		for i in range(0,len(self.v.vector)):
			sum += self.v.vector[i]
		 	
		sum /= len(self.v.vector)
		return sum	
