#include <stdlib.h>     /* system */

#include <example_package/ExampleClass.hpp>

#include <sm/logging.hpp>

// NOTE: This avoids you having to write "example::ExampleClass", instead you can simply write "ExampleClass"
// NOTE: using directives should not be used in header files, since when other files include your headers they will automatically use the directives and potentially get name collisions. It us ok to use them here.
using namespace example;


// NOTE: We can comment out the variable names of the arguments if we do not use these variables in the code. This will prevent the compiler warning: 
// warning: unused parameter `argc' [-Wunused-parameter]
int main(int /*argc*/, char** /*argv*/) {
  
  SM_INFO_STREAM("Hi, I am a simple example program using the ExampleClass.");

  ExampleClass exampleClass; // Not initialized yet
  
  // We know that exampleClass.getA() will throw because it is not initialized yet. Let's catch this exception here, so we can continue with our program.
  try {
    
    double a = exampleClass.getA();
    SM_INFO_STREAM("a is " << a);
    
  } catch (const std::exception& e) {
    SM_FATAL_STREAM(e.what());
    SM_INFO("I caught an exception. In a real program you probably do not want to continue. Here we do to show some other examples.");
  }
  
  exampleClass.initialize(1.0, 2.0);
  SM_INFO_STREAM("Example class initialized: a = " << exampleClass); // This uses the custom stream operator
  
  // TODO: Initialize with a property tree, how to get path to file?
//   i=system("rospack find example_package");
//   boost::filesystem::path configFile();
//   sm::BoostPropertyTree propertyTree;
//   propertyTree.loadInfo(configFile);
//   exampleClass.initializeWithPropertyTree(propertyTree);
//   SM_INFO_STREAM("I initialized the ExampleClass with the property tree, now Example class is: " << exampleClass); // This uses the custom stream operator
  
  SM_INFO_STREAM("Example program terminated successfully");
  return 0;

}
