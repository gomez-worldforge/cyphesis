#!/usr/bin/python
#This file is distributed under the terms of the GNU General Public license.
#Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).

from neuralnet import * 

class TestNN:
	def __init__(self, i,h,o):
		net = NN(i,h,o)

		iv = Vector(3)
		ov = Vector(3)

		iv.initialize()
		ov.initialize()

		net.run(i,h,o,iv,ov)


if __name__ == "__main__":
	TestNN(3,3,3)
