#!/usr/bin/env python

import numpy as np
import example_package_python as ex

print "We construct ExampleClass with default constructor. The class is not correctly initialized afterwards. We expect a call to member a to throw an exception."
exampleClass = ex.ExampleClass()

try:
  a = exampleClass.a
except Exception,e:
  print e
  
print "Now we initialize the class, using the default argument for b. We expect a=1.0 and b=0.0"
exampleClass.initialize(1.0)
# NOTE: the following print will call the __str__ method defined in the python wrapper
print "exampleClass =",exampleClass

print "Now we initialize the class without using the default argument for b. We expect a=1.0, b=2.0"
exampleClass.initialize(1.0,2.0)
print "exampleClass =",exampleClass

print "calling exampleClass.printHello()"
exampleClass.printHello()
