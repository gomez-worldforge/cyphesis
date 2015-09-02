#This file is distributed under the terms of the GNU General Public license.
#(GNU Public license version 2 or later)
#Copyright (C) 1999 Aloril (See the file COPYING for details).
#Copyright (C) 2015 Johan Ceuppens (See the file COPYING for details).

#import random
#import traceback

from atlas import *
#from physics import *
#from physics import Quaternion
#from common import const
#from types import *

#from physics import Vector3D

import server

#from mind.Memory import Memory
#from mind.Knowledge import Knowledge
#from mind.panlingua import interlinguish,ontology
#from mind.compass import vector_to_compass
#from common import log,const
#import dictlist
#import mind.goals
#import mind.goals.common

class AIMind(server.Mind):###FIXME server.Thing):

    """Alternative to NPCMind.py for the server AI engine, non-goal based"""   

    def __init__(self, cppthing):
        self.mind = cppthing

