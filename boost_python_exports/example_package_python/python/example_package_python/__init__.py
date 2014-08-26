import os
# Import the numpy to Eigen type conversion.
import numpy_eigen # NOTE: we only need this if we want to automatically convert numpy arrays to Eigen types

isCompiled = False
pathToSo = os.path.dirname(os.path.realpath(__file__))
if os.path.isfile(os.path.join(pathToSo,"libexample_package_python.so")):
    # Import the the C++ exports from your package library.
    from libexample_package_python import *
    # Import other files in the directory
    # from mypyfile import *
    isCompiled = True
else:
    print "Warning: the package libexample_package_python is not compiled."
    PACKAGE_IS_NOT_COMPILED = True;


