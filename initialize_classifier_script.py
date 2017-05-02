
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


import sys
if 'threading' in sys.modules:
    del sys.modules['threading']
import gevent
import gevent.socket
import gevent.monkey
gevent.monkey.patch_all()


def initialize_classifier(a):
	print "entered INITIALIZATION python script!"
	clf = SGDClassifier(loss="hinge", penalty="l2")
	return clf