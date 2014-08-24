cmake_minimum_required(VERSION 2.8.3)
project(rocket)

find_package(catkin_simple REQUIRED)
catkin_simple()

cs_add_library(${PROJECT_NAME} 
  src/rocket.cpp
)

cs_install()
cs_export()

