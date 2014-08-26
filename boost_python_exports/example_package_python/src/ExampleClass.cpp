#include <boost/python.hpp>

// NOTE: IMPORTANT: It is crucual that you include this header if you use Eigen matrices that you want to export
#include <numpy_eigen/boost_python_headers.hpp>

#include <boost/shared_ptr.hpp>
#include <example_package/ExampleClass.hpp>

#include <sstream>      // std::ostringstream

using namespace boost::python;
using namespace example;

// ExampleClass::initialize(a, b=0.0) has default arguments that have to be treated special in boost python
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(ExampleClass_initialize_overloads, ExampleClass::initialize, 1, 2)

/**
 * @brief Defines a wrapper to convert class ExampleClass to a string version
 * @param e Reference to a class of type ExampleClass
 * @return string version of this class
 */
inline std::string exampleClassToStringWrapper(const ExampleClass& e) {
  std::ostringstream ss;
  ss << e.getB(); // NOTE: we have already defined the stream operator for this class
  return ss.str();
}

void exportExampleClass() {
  
  // The class ExampleClassBase is not constructible because of the pure virtual function printHello. Thus we do not create a constructor with no_init
  class_<ExampleClassBase, ExampleClassBase::Ptr, boost::noncopyable>("ExampleClassBase", "Description of ExampleClassBase", no_init)
    
    .def("initialize", &ExampleClassBase::initialize, "bool initialize(double b): initializes the class")
    
    // Let's define b in a way that it appears as a member in python, but actually we use the setter and getter methods underneath
    // We have to excplicitly define the function type for getB since there are two overloaded methods and boost python does not know which to choose otherwise
    // We use make_function here because we have to specify a return value policy
    .add_property("b", make_function((const double& (ExampleClassBase::*)(void) const)&ExampleClassBase::getB, return_value_policy<copy_const_reference>()), &ExampleClassBase::setB, "double b: member variable")

    // we can also expose the getB() method as a function to python
    // Again we have to excplicitly define the function type for getB since there are two overloaded methods and boost python does not know which to choose otherwise
    .def("getB", (const double& (ExampleClassBase::*)(void) const)&ExampleClassBase::getB, return_value_policy<copy_const_reference>(), "double getB(): returns member b")
//     
//     // Here is a normal function where we do not have to do magic stuff
    .def("setB", &ExampleClassBase::setB, "void setB(double b)")
  
    // We have to define pure_virtual functions as such
    .def("printHello", pure_virtual(&ExampleClassBase::printHello), "void printHello(): Prints out hello message to stdout")
  ;

  
  // We have to tell boost::python that this class is derived from ExampleClassBase
  // We create the default constructor first
  class_<ExampleClass, ExampleClass::Ptr, bases<ExampleClassBase> >("ExampleClass", "Description of the example class", init<>("ExampleClass(): default constructor, you have to call initialize() later if you use this constructor"))
  
    // We can define more constructors (e.g. the one with default arguments)
    .def(init< double, optional<double> >("ExampleClass(double a, double b = 0.0): Constructor with arguments for a and b"))
    
    // And the one taking the Eigen vector
    .def(init<Eigen::Vector2d>("ExampleClass(const Eigen::Vector2d vec): Constructor taking an array [a,b] as argument. Use a numpy 2d array here."))
  
    .add_property("a", make_function((const double& (ExampleClass::*)(void) const)&ExampleClass::getA, return_value_policy<copy_const_reference>()), &ExampleClass::setB, "double a: member variable")
    
    // We use the above created overloads to deal with default arguments
    .def("initialize", &ExampleClass::initialize, ExampleClass_initialize_overloads("bool initialize(double a, double b=0.0): Initializes the class. Use this method after constructing with default constructor!"))
    
    // We can define a __str__ operator. that way we can define what is show when we call "print ExampleClass"
    .def("__str__", &exampleClassToStringWrapper, "Custom print function for this class")
    
    // We could also export the other methods of ExampleClass, but we don't have to
  ;
}
