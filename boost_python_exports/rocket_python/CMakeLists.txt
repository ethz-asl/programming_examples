cmake_minimum_required(VERSION 2.8.3)
project(rocket_python)

find_package(catkin_simple REQUIRED)
catkin_simple(ALL_DEPS_REQUIRED)

SET(PY_PROJECT_NAME ${PROJECT_NAME})
SET(PY_PACKAGE_DIR python/rocket)

# The first argument is the name of the project. This is the library name
# that you have specified in module.cpp (with lib prepended), and
# in your __init__.py file. In this example, ${PROJECT_NAME} is
# rocket_python, so the resulting library will be called librocket_python
#
# The second argument tells CMake where to find the __init__.py file so
# that it can be installed
add_python_export_library(${PY_PROJECT_NAME} ${PY_PACKAGE_DIR}
  src/module.cpp
  src/exportRocket.cpp
)
cs_install()
cs_export()

