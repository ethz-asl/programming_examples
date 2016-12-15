###########
## Setup ##
###########

cmake_minimum_required(VERSION 2.8.3)
project(nlopt_export_test) # NOTE: It's IMPORTANT to specify the same name as in your package.xml here

# The next two lines are REQUIRED. 
# They will get the include and linker flags from your dependencies and include the include directory in your current package.
find_package(catkin_simple REQUIRED)
catkin_simple(ALL_DEPS_REQUIRED)

# Add an executable
cs_add_executable(${PROJECT_NAME}_node
  src/ExampleProgram.cpp
)

