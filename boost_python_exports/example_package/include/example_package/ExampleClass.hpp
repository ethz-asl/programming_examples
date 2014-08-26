#ifndef EXAMPLE_CLASS_HPP_
#define EXAMPLE_CLASS_HPP_

#include <boost/shared_ptr.hpp>
#include <Eigen/Dense>

#include <sm/PropertyTree.hpp>

// NOTE: consider using namespaces that will avoid name collisions
namespace example {
  
  /**
   * @class ExampleClassBase
   * @brief Will be used later to show inheritance
   */
  class ExampleClassBase {
    
    public:
      
      // NOTE: Ptr typedefs are very convenient and let you switch pointer implementation easily if you always use ExampleClass::Ptr instead of e.g. ExampleClass* or boost::shared_ptr<ExampleClass>
      typedef boost::shared_ptr<ExampleClassBase> Ptr;
      typedef boost::shared_ptr<const ExampleClassBase> ConstPtr;
      
    public:
      
      // Default constructor. It is usually a good idea to have a default constructor + initialize method
      ExampleClassBase();
      
      // Overloaded constructor
      ExampleClassBase(double b);
      
      // Destructor
      ~ExampleClassBase();
      
      // Initialization method in case the default constructor was used
      bool initialize(double b);
      
      // getters
      // NOTE: Consider writing getters and setters for all members instead of making them public
      double& getB(); // NOTE: Returns m_b in a way that it is mutable afterwards
      const double& getB() const; // NOTE: Return value cannot be changed
      
      // Define an interface
      // We want to enforce that every class inheriting from this base class has to implement the method printHello().
      // The class ExampleClassBase cannot be constructed any more, since printHello() is pure virtual.
      virtual void printHello() const = 0;
      
      // setters
      inline void setB(double b); // NOTE: This method cannot be const because it has to change the value of member m_a

    private:

      bool m_isInitialized; /// @brief Whether or not the class is correctly initialized. It is not initialized correctly if only the default constructor was called.
      double m_b; /// @brief Double member
    
  }; /* class ExampleClassBase */

  /**
  * @class ExampleClass
  * @brief Class to show some coding aspects. It is publically inherited from ExampleClassBase
  * @note Notice that no definitions are in the header file. They belong into the cpp file or in case of templated or inlined methods into an *Implementation.hpp file.
  * @Note This is a doxygen description. All your methods should be documented.
  */
  class ExampleClass : public ExampleClassBase {
    
    public:
      
      // NOTE: Ptr typedefs are very convenient and let you switch pointer implementation easily if you always use ExampleClass::Ptr instead of e.g. ExampleClass* or boost::shared_ptr<ExampleClass>
      typedef boost::shared_ptr<ExampleClass> Ptr;
      typedef boost::shared_ptr<const ExampleClass> ConstPtr;
      
    public:
      // Default constructor. It is usually a good idea to have a default constructor + initialize method
      ExampleClass();
      
      // Overloaded constructor with default argument
      ExampleClass(double a, double b = 0.0);
      
      // Overloaded constructor taking an Eigen vector. With numpy_eigen, we can directly pass a numpy.array() to this constructor from python.
      ExampleClass(const Eigen::Vector2d vec);

      // Constructor that takes a property tree (convenient to write configuration files)
      ExampleClass(const sm::PropertyTree& propertyTree);
      
      // Destructor
      ~ExampleClass();
      
      // Initialization method in case the default constructor was used
      bool initialize(double a, double b=0.0);
      bool initializeWithPropertyTree(const sm::PropertyTree& propertyTree);
      
      // getters
      // NOTE: Consider writing getters and setters for all members instead of making them public
      double& getA(); // NOTE: Returns m_a in a way that it is mutable afterwards
      const double& getA() const; // NOTE: Return value cannot be changed

      // setters
      inline void setA(double a); // NOTE: This method cannot be const because it has to change the value of member m_a
      
      // Pure virtual functions from base class
      virtual void printHello() const;

      // Definitions of templated methods have to go into an implementation header
      template <typename T>
      inline T getATyped() const;
      
      // Two overloaded methods
      double aTimes(double val) const;
      double aTimes(double val0, double val1) const;
      
      // Just an example of what not to do. The compiler will issue a warning.
      double& dontDoThat(double b) const;
      
    private:
      
      bool m_isInitialized; /// @brief Whether or not the class is correctly initialized. It is not initialized correctly if only the default constructor was called.
      double m_a; /// @brief Double member
    
  }; /* class ExampleClass */

} /* namespace example */

// NOTE: Implementations of templated and inlined methods have to available at compile time. Therefore we have to include the implementation here
#include <example_package/implementation/ExampleClassImplementation.hpp>

#endif