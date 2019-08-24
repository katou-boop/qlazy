# -*- coding: utf-8 -*-
from qlazypy.error import *
from qlazypy.config import *
from qlazypy.QState import *

class QStateTest(QState):

    def __new__(cls, qubit_num, seed=None):

        ret = super(QStateTest,cls).__new__(cls,qubit_num,seed)
        ret.__class__ = QStateTest
        return ret
        
    def hadamard(self,id):

        for i in range(len(id)):
            self.h(id[i])
            
        return self

