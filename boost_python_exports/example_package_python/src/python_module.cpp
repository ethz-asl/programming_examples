#include <boost/python.hpp>
#include <sstream>

using namespace boost::python;

void exportExampleClass();

BOOST_PYTHON_MODULE(libexample_package_python) {
    exportExampleClass();
}
