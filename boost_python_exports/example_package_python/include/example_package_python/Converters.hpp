#ifndef EXAMPLE_PACKAGE_PYTHON_CONVERTERS_HPP
#define EXAMPLE_PACKAGE_PYTHON_CONVERTERS_HPP

#include <sm/assert_macros.hpp>
#include <numpy_eigen/boost_python_headers.hpp>
#include <numpy_eigen/type_traits.hpp>
#include <numpy/arrayobject.h> 

struct MyClassConverter {

  // The "Convert from C to Python" API
  static PyObject * convert(const exmaple::MyClass & point) {

    const int nd = 1;
    npy_intp dims[] = { 3 };
    PyObject * P = NULL;
    P = PyArray_SimpleNew(nd, dims, NPY_DOUBLE);
    
    double* p;
    p = static_cast<double*>(PyArray_GETPTR1(P, 0));
    *p = point.x;
    
    // incrementing the reference seems to cause a memory leak.
    // boost::python::incref(P);
    // This agrees with the sample code found here:
    // http://mail.python.org/pipermail/cplusplus-sig/2008-October/013825.html
    return P;
  }

  static void* convertible(PyObject *obj_ptr) {
    
    if(!obj_ptr) {
      return 0;
    }
    // Make sure this is a numpy array.
    if(!PyArray_Check(obj_ptr)) {
      return 0;
    }
    // Check that the numpy type is convertible to a double
    int npyType = PyArray_ObjectType(obj_ptr, 0);
    if ( !(npyType == NPY_DOUBLE || npyType == NPY_INT || npyType == NPY_FLOAT)) {
      return 0;
    };
    // Check the array dimensions.
    if (PyArray_NDIM(obj_ptr) != 1) {
      return 0;
    }
    if (PyArray_DIM(obj_ptr, 0) != 3) {
      return 0;
    }

    return obj_ptr;
  }
  

  static void construct(PyObject *obj_ptr, boost::python::converter::rvalue_from_python_stage1_data *data) {
    
    boost::python::converter::rvalue_from_python_storage<BTTrafo::Point3> * matData = reinterpret_cast<boost::python::converter::rvalue_from_python_storage<BTTrafo::Point3> * >(data);
    void* storage = matData->storage.bytes;
    BTTrafo::Point3* pointP = new (storage) BTTrafo::Point3();
    // Stash the memory chunk pointer for later use by boost.python
    // This signals boost::python that the new value must be deleted eventually
    data->convertible = storage;
    BTTrafo::Point3& point = *pointP;
    
    int npyType = PyArray_ObjectType(obj_ptr, 0);
    pyArrayToPoint(obj_ptr, npyType, point);

  }
  
  static void pyArrayToPoint(PyObject *obj_ptr, int npyType, BTTrafo::Point3& point) {
    
    switch (npyType) {
      case NPY_DOUBLE:
        point.x = *(static_cast<double*>(PyArray_GETPTR1(obj_ptr, 0)));
        point.y = *(static_cast<double*>(PyArray_GETPTR1(obj_ptr, 1)));
        point.z = *(static_cast<double*>(PyArray_GETPTR1(obj_ptr, 2)));
        break;
      case NPY_INT:
        point.x = *(static_cast<int*>(PyArray_GETPTR1(obj_ptr, 0)));
        point.y = *(static_cast<int*>(PyArray_GETPTR1(obj_ptr, 1)));
        point.z = *(static_cast<int*>(PyArray_GETPTR1(obj_ptr, 2)));
        break;
      case NPY_FLOAT:
        point.x = *(static_cast<float*>(PyArray_GETPTR1(obj_ptr, 0)));
        point.y = *(static_cast<float*>(PyArray_GETPTR1(obj_ptr, 1)));
        point.z = *(static_cast<float*>(PyArray_GETPTR1(obj_ptr, 2)));
        break;
      default:
        SM_THROW(std::runtime_error, "missing conversion rule for numpy arrays of type " << npyTypeToString(npyType));
    }
  }

  // The registration function.
  static void register_converter()
  {
    boost::python::to_python_converter<BTTrafo::Point3,Point3Converter>();
    boost::python::converter::registry::push_back(
              &Point3Converter::convertible,
              &Point3Converter::construct,
              boost::python::type_id<BTTrafo::Point3>());

  }
  
}; /* MyClassConverter */
  
};


#endif /* EXAMPLE_PACKAGE_PYTHON_CONVERTERS_HPP */
