// you have to include the declarations here
#include <example_package/ExampleClass.hpp>

#include <example_package/Exceptions.hpp>

// standard includes
#include <limits.h>

// Schweizer Messer includes
#include <sm/logging.hpp>
#include <sm/assert_macros.hpp>

namespace example {

  /**
    * @brief Default constructor.
    */
  ExampleClassBase::ExampleClassBase() :
    m_isInitialized(false), // NOTE: don't forget to set this flag to false in the beginning
    m_b(std::numeric_limits<double>::signaling_NaN()) {
    
    // NOTE: Consider initializing your members to NaN as shown above instead of leaving them undefined
      
  }

  /**
    * @brief Overloaded constructor
    */
  ExampleClassBase::ExampleClassBase(double b) : 
    m_b(b) {

    // NOTE: ": m_b(b)" is an initialization list
    m_isInitialized = true;
  }

  /** 
    * @brief Destructor
    */
  ExampleClassBase::~ExampleClassBase() {
    
    // NOTE: sometimes it is useful to do things only when compiled with debug information. In Release mode, these parts will not slow down your code.
#ifndef NDEBUG
    SM_DEBUG_STREAM("Destructor called");
#endif
    
  }

  /** 
    * @brief Initialization method in case the default constructor was used
    * @param a Description of what "b" is
    * @return Was the initialization successful or not
    */
  bool ExampleClassBase::initialize(double b) {

    // Initialize this class
    m_b = b;
    m_isInitialized = true;
    
    SM_DEBUG_STREAM("Class initialized with " << m_b);
    
    return m_isInitialized;
  }


  /**
    * @brief Gets a mutable version of member m_b
    * @return Mutable version of member m_b
    */
  double& ExampleClassBase::getB() {
    
    // check that the class is correctly initialized before accessing member m_b
    // If you use the macro without _DBG at the end, it will check the condition in all build types
    SM_ASSERT_TRUE( InitializationException, m_isInitialized, "You have to call initialize() first if you used the default constructor");
    
    return m_b;
  }

  /**
    * @brief Gets a const version of member m_b
    * @return Const version of member m_b. The return value cannot be changed.
    */
  const double& ExampleClassBase::getB() const {
    
    // check that the class is correctly initialized before accessing member m_b
    // If you use the macro with _DBG at the end, it will NOT check the condition in RELEASE build type
    SM_ASSERT_TRUE_DBG( InitializationException, m_isInitialized, "You have to call initialize() first if you used the default constructor");
    
    return m_b;
  }



  /**
    * @brief Default constructor. You should explicitely call the constructor of the base class here.
    */
  ExampleClass::ExampleClass() : 
    ExampleClassBase(),
    m_isInitialized(false), // NOTE: don't forget to set this flag to false in the beginning
    m_a(std::numeric_limits<double>::signaling_NaN()) {
    
  }

  /**
    * @brief Overloaded constructor
    * @note Don't specify the default value in the implementation of the method
    */
  ExampleClass::ExampleClass(double a, double b /*= 0.0*/) : 
    ExampleClassBase(b), // NOTE: You should explicitely call the constructor of the base class here.
    m_a(a) {
      
    // NOTE: ": m_a(a)" is an initialization list
    
    // Since both base class and this class have a member m_isInitialized, we should fully specify the name
    ExampleClass::m_isInitialized = true;
  }
  
  /**
   * @brief  Constructor that takes a property tree (convenient to write configuration files)
   * @param propertyTree Property tree from sm_property_tree package
   */
  ExampleClass::ExampleClass(const sm::ConstPropertyTree& propertyTree) :
    ExampleClassBase(),
    m_isInitialized(false), // NOTE: don't forget to set this flag to false in the beginning
    m_a(std::numeric_limits<double>::signaling_NaN()) {

      // NOTE: Every class has a this pointer, which is a pointer to the instance of this class. You don't have to use the this pointer here to call the initialize() method, but it helps the reader to see that this is a method of this class.
      this->ExampleClass::initializeWithPropertyTree(propertyTree); 
      
  }
  
  /**
   * @brief  Constructor that takes a an Eigen vector vec
   * @param vec vec = [a,b]
   */
  ExampleClass::ExampleClass(const Eigen::Vector2d vec) :
    ExampleClassBase(vec(1)), 
    m_isInitialized(true),
    m_a(vec(0)) {
    
  }

  /** 
    * @brief Destructor
    */
  ExampleClass::~ExampleClass() {
    
  }

  /** 
    * @brief Initialization method in case the default constructor was used
    * @param a Description of what "a" is
    * @return Was the initialization successful or not
    */
  bool ExampleClass::initialize(double a, double b /*=0.0*/) {
    
    // Initialize base class
    ExampleClassBase::initialize(b);
    
    // Initialize this class
    m_a = a;
    ExampleClass::m_isInitialized = true;
    
    SM_DEBUG_STREAM("Class initialized with " << m_a);
    
    return true;
  }
  
    
  /**
   * @brief initializes the class with a property tree
   * @param propertyTree Should contain a and b
   * @return Was the initialization successful or not
   **/
  bool ExampleClass::initializeWithPropertyTree(const sm::ConstPropertyTree& propertyTree) {
      double a = propertyTree.getDouble("/parameters/a"); // NOTE: will throw if value cannot be found
      double b = propertyTree.getDouble("/parameters/b", 2.0); // NOTE: You can specify default values, will not throw if parameter b cannot be found
      ExampleClass::initialize(a,b);
      return true;
  }

  /**
    * @brief Gets a mutable version of member m_a
    * @return Mutable version of member m_a
    */
  double& ExampleClass::getA() {
    
    // instead of using SM_ASSERT_, we can also check and just print an error
    if (!m_isInitialized) {
      SM_ERROR("The class was not correctly initialized");
      
      // Maybe we still want to throw. Of course this does not make much sense like this, but it shows the usage of SM_THROW
      SM_THROW(InitializationException, "The class was not correctly initialized");
    }
    
    return m_a;
  }

  /**
    * @brief Gets a const version of member m_a
    * @return Const version of member m_a. The return value cannot be changed.
    */
  const double& ExampleClass::getA() const {
    SM_ASSERT_TRUE( InitializationException, m_isInitialized, "You have to call initialize() first if you used the default constructor" );
    return m_a;
  }
  
  /**
   * @brief Prints hello to stdout
   **/
  void ExampleClass::printHello() const {
    SM_INFO("Hello");
  }


  /**
    * @brief Computes m_a*val
    * @return m_a*val
    */
  double ExampleClass::aTimes(double val) const {
    SM_ASSERT_TRUE( InitializationException, m_isInitialized, "You have to call initialize() first if you used the default constructor" );
    return m_a*val;
  }

  /**
    * @brief Computes m_a*val0*val1;
    * @return m_a*val0*val1
    */
  double ExampleClass::aTimes(double val0, double val1) const {
    SM_ASSERT_TRUE( InitializationException, m_isInitialized, "You have to call initialize() first if you used the default constructor" );
    return m_a*val0*val1;
  }

  /**
    * @brief Just an example of what not to do. The compiler will issue a "warning: reference to local variable `rval' returned [enabled by default]"
    * @return m_a*val
    */
  double& ExampleClass::dontDoThat(double b) const {
    double rval; // This is a local variable that will be destroyed upon exit of this function
    rval = m_a*b;
    return rval; // If you return a reference to the local variable that will be destroyed, you have a dangling reference.
  }
}
