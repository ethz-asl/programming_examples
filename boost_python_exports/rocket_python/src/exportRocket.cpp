#include <numpy_eigen/boost_python_headers.hpp>
#include <rocket/rocket.h>
#include <boost/shared_ptr.hpp>

void exportRocket() {
  using namespace boost::python;
  using namespace rocket;

  // Rocket has an overloaded function for "getInertiaMatrix()" 
  // Boost python requires that we use function pointers to
  // disambiguate.
  // This assigns the const version to the variable "getInertiaMatrix1"
  const Eigen::Matrix2d& (Rocket::*getInertiaMatrix1)() const = &Rocket::getInertiaMatrix;

  // The class_ directive tells boost::python about a class
  class_<Rocket,  // This is the class name
         boost::shared_ptr<Rocket>, // This tells boost::python that you may use shared pointers with this class.
         boost::noncopyable // This tells boost::python that the class is abstract
         >("Rocket", no_init) // This line gives the name of the class, and says that it cannot be constructed (no_init)
      // Next we define our functions
      .def("getMaxSpeed", &Rocket::getMaxSpeed,
           (args("self")),
           "Get the maximum speed of the rocket")
      .def("setMaxSpeed", &Rocket::setMaxSpeed,
           (args("self","max_speed")), 
           "Set the maximum speed of the rocket")
      .def("setInertiaMatrix", &Rocket::setInertiaMatrix,
           (args("self","inertia_matrix")),
           "Set the rocket's inertia matrix")
      // This version of "getInertiaMatrix" returns a
      // const reference. We must explictly tell boost
      // python what to do about this. For Eigen matrices
      // They are *always* copied at the python/C++ border
      // so we must choose "copy_const_reference"
      .def("getInertiaMatrix", getInertiaMatrix1,
           args("self"),
           "Gets the rocket's inertia matrix",
           return_value_policy<copy_const_reference>())
      ;

  class_<Booster,  // Export the Booster clase
         boost::shared_ptr<Booster>, // Also shared_ptr (good practice)
         bases<Rocket> // Tell boost::python that Booster inherits from Rocket
         >("Booster", init<>(args("self"))) // Tell boost::python there is a default constructor
      .def(init<double, const Eigen::Matrix2d&, unsigned>(
          args("self", "max_speed", "inertia_matrix", "num_boosts"),
          "initialize the booster with properties"))
      .def("getNumBoosts", &Booster::getNumBoosts,
           args("self"),
           "Get the number of boosts that this rocket is capable of")
      .def("setNumBoosts", &Booster::setNumBoosts,
           args("self", "num_boosts"),
           "Set the number of boosts that this rocket is capable of")
      ;

}
