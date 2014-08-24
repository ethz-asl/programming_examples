#include <numpy_eigen/boost_python_headers.hpp>

void exportRocket();

BOOST_PYTHON_MODULE(librocket_python)
{
  exportRocket();
}
