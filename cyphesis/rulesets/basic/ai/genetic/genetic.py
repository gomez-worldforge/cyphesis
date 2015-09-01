#This file is distributed under the terms of the GNU General Public license.
#Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).

from ai.util import RNG 

class GeneticAlgorithm:
	def __init__(self):
		numbers = []	

	def initialize(self, n):
		for i in range(0,n):
			self.numbers.append(RNG().int(n))

	def add(self, number):
		self.numbers.append(number)

	def fit(self):
		n = 0.0
		m = 0.0
		for o in self.numbers:
			m += o

		return m / n		
