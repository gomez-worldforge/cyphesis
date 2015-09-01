#!/usr/bin/python
#This file is distributed under the terms of the GNU General Public license.
#Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).

from nk import * 

class TestNK:
	def __init__(self, size):
		### NK(size).runadd()
		NK(size).run()

if __name__ == "__main__":
	TestNK(100)
