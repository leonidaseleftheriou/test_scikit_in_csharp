
import gevent.monkey; gevent.monkey.patch_thread()
import threading
import numpy as np
from numpy import genfromtxt
from sklearn.linear_model import SGDClassifier
#from numpy import genfromtxt
#from sklearn.linear_model import SGDClassifier
import sys
import DLFCN
import matplotlib
import json

import os
import sys
if 'threading' in sys.modules:
    del sys.modules['threading']
import gevent
import gevent.socket
import gevent.monkey
gevent.monkey.patch_all()


def train(array1, size1, classifier1, coeff_ptr1):
    print "entered TRAIN python script!!"
    numOfChunks = array1.size/size1
    array_fragmented = np.array_split(array1,numOfChunks)
    X1 = array_fragmented[:-1]
    y1 = array_fragmented[-1]
    X = np.array(X1).transpose()
    y = np.array(y1)
    print "in the train script, random message BEFORE using the classifier again, because this is where the problem appears"
    print classifier1.coef_
    print "in the train script, random message AFTER using the classifier again"
    classifier1.partial_fit(X, y, np.unique(y))
    print classifier1.coef_
    print classifier1.intercept_
    coefficients = [classifier1.coef_[0,0], classifier1.coef_[0,1], classifier1.intercept_[0]]
    thefile = open('test.txt', 'w')
    thefile.write("[")
    for item in coefficients:
        thefile.write("%s " % item)
    thefile.seek(-1, os.SEEK_END)
    thefile.truncate()
    thefile.write("]")
    thefile.close()
    coeff_ptr1 = np.asarray(coefficients)
    return classifier1