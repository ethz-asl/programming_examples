#include <gtest/gtest.h>

#include <example_package/ExampleClass.hpp>
#include <example_package/Exceptions.hpp>

using namespace example;


TEST(ExampleClass, construct){
  
  try {
  
    ExampleClass exampleClass1;
    
    // NOTE: You do not need both EXPECT_ here, this just shows two use-cases
    EXPECT_ANY_THROW(exampleClass1.getA()); // We expect getA() to throw an exception, since exampleClass1 is not initialized yet
    EXPECT_THROW(exampleClass1.getA(), InitializationException); // Particularly, we expect getA() to throw an exception of type InitializationException
    
    EXPECT_TRUE(exampleClass1.initialize(1.0,2.0));
    EXPECT_NO_THROW(exampleClass1.getA()) << "This should not throw"; // NOTE: You can add printouts
    
    ExampleClass exampleClass2(1.0, 2.0);
    EXPECT_NO_THROW(exampleClass2.getA());
    
  } catch(const std::exception & e) {
    FAIL() << e.what();
  }
}

TEST(ExampleClass, methods){
  
  try {
        
    ExampleClass exampleClass(1.0, 2.0);
    EXPECT_EQ(exampleClass.getA(), 1.0);
    EXPECT_EQ(exampleClass.getB(), 2.0);
  
  } catch(const std::exception & e) {
    FAIL() << e.what();
  }
}