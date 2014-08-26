###########
## Setup ##
###########

cmake_minimum_required(VERSION 2.8.3)
project(example_package_python)

find_package(catkin_simple REQUIRED)
catkin_simple()

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

catkin_python_setup()

# Set up the python exports.
set(PY_PROJECT_NAME ${PROJECT_NAME})
set(PY_PACKAGE_DIR python/${PROJECT_NAME})

##############
## Building ##
##############

add_python_export_library(${PY_PROJECT_NAME} ${PY_PACKAGE_DIR}
  src/ExampleClass.cpp
  
   # NOTE: Don't forget to include this file, otherwise you will get an error at runtime:
   # ImportError: dynamic module does not define init function (initlibexample_package_python)
  src/python_module.cpp
)

target_link_libraries(${PY_PROJECT_NAME} 
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

#############
## Testing ##
#############

# Unit test to test your python exports

catkin_add_nosetests( 
  test/Test.py
)