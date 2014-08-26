#!/usr/bin/env python
import example_package_python as epp

import unittest

class TestConstruction(unittest.TestCase):
    def test_construction(self):
        exampleClass = epp.ExampleClass()

if __name__ == '__main__':
    import rostest
    rostest.rosrun('example_package_python', 'Construction', TestConstruction)