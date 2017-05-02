
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


def return_results(classifier1):
	print "entered RETURN_RESULTS python script!!"
	print classifier1.coef_
	return [classifier1.coef_[0,0], classifier1.coef_[0,1], classifier1.intercept_[0]]