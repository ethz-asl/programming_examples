#ifndef EXAMPLE_CLASS_IMPLEMENTATION_HPP_
#define EXAMPLE_CLASS_IMPLEMENTATION_HPP_

// NOTE: Put you doxygen documentation of methods into the implementation or cpp file. If you only change the documentation afterwards, programs including your header files do not have to be recompiled.

// NOTE: templated and inlined methods have to go into this file

namespace example {
  
  

  /**
  * @brief setter for m_b
  * @param b Sets m_b to b
  */
  void ExampleClassBase::setB(double b) {
    m_b = b;
    m_isInitialized = true;
  }
  

  /**
  * @brief setter for m_a
  * @param a Sets m_a to a
  */
  void ExampleClass::setA(double a) {
    m_a = a;
    ExampleClass::m_isInitialized = true;
  }


  /**
    * @brief Gets member m_a as a different type
    * @tparam T return value type
    * @return m_a as type T
    */
  template <typename T>
  inline T ExampleClass::getATyped() const {
    
    // Explicitely cast m_a to type T. Compiler will raise an error if that is not possible, e.g. if T is std::string.
    return (T)m_a;
  }

} /* namespace example */

#endif