###########
## Setup ##
###########

cmake_minimum_required(VERSION 2.8.3)
project(example_package) # NOTE: It's IMPORTANT to specify the same name as in your package.xml here

# The next two lines are REQUIRED. 
# They will get the include and linker flags from your dependencies and include the include directory in your current package.
find_package(catkin_simple REQUIRED)
catkin_simple()

# The next two lines are OPTIONAL. Use it in case you have dependencies to boost.
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

##############
## Building ##
##############

# Add a library
cs_add_library(${PROJECT_NAME}
  src/ExampleClass.cpp
)

# Link the library you created above against boost libraries. 
# You do not need to link against ${catkin_LIBRARIES}, this is done by the cs_add_library command automatically
target_link_libraries(${PROJECT_NAME} 
  ${Boost_LIBRARIES}
)

# Add an executable
cs_add_executable(${PROJECT_NAME}_node
  src/ExampleProgram.cpp
)
# Since the executable uses the ExampleClass class we compiles into a library, we have to link against it here
target_link_libraries(${PROJECT_NAME}_node 
  ${PROJECT_NAME}
)

#############
## Install ##
#############

# This will install headers located in include folder and all libraries and executables 
# you specified with cs_add_library() and cs_add_executable() insto your install folder
cs_install()

# Install launch files
install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
  FILES_MATCHING PATTERN "*.launch"
  PATTERN ".svn" EXCLUDE
)

############
## Export ##
############

# This command will let other packages depending on your current package find its headers and link against its libraries
cs_export()

#############
## Testing ##
#############

# It is highly RECOMMENDED to write unit tests. 
# Unit tests are a convenient way to determine whether your code wors as expected.

# Add gtest based cpp test target and link libraries against your project.
catkin_add_gtest(${PROJECT_NAME}-test
  test/test_main.cpp
  test/TestExampleClass.cpp
)
if(TARGET ${PROJECT_NAME}-test)
  target_link_libraries(${PROJECT_NAME}-test 
    ${PROJECT_NAME}
    ${GTEST_LIBRARIES}
    pthread
  )
endif()
