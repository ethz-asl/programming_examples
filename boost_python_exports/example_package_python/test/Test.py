#!/usr/bin/env python
import example_package_python as epp

import unittest

class TestConstruction(unittest.TestCase):
    def test_construction(self):
        exampleClass = epp.ExampleClass()
        self.assertTrue(exampleClass.initialize(0.1)) # Note: uses default value 0.0 for b
        self.assertEqual(exampleClass.a, 0.1)
        self.assertEqual(exampleClass.b, 0.0)
        
        self.assertTrue(exampleClass.initialize(0.1, 0.2))
        self.assertEqual(exampleClass.a, 0.1)
        self.assertEqual(exampleClass.b, 0.2)

if __name__ == '__main__':
    unittest.main()
