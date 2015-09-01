#This file is distributed under the terms of the GNU General Public license.
#Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).

from random import * 

# Random Number God class (RNG)

class RNG:
	def __init__(self):
		rng = Random()
		
	def int(self, n):
		return self.rng.randint(n) 

	def float(self, n, m):
		return self.rng.randint(n) / m 
