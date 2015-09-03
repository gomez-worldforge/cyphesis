#This file is distributed under the terms of the GNU General Public license.
#Copyright (C) 1999 Aloril (See the file COPYING for details).
from atlas import *

from random import *

import atlas
import server

class ChessBoard(server.Thing):
    def chop_operation(self, op):
        if self.mass<1:
            return(Operation("set",Entity(self.id,status=-1),to=self))
        res = Oplist()
        ent=Entity(self.id,mode="dead",mass=self.mass-1) ### FIXME 'dead'
        res.append(Operation("set",ent,to=self))
        wood_ent=Entity(name='wood',parents=['wood'])
        if (len(op)>1):
            to_ = op[1].id
        else:
            to_=self
        res.append(Operation("create",wood_ent,to=to_))
        return res
