#ifndef EXAMPLE_PACKAGE_EXCEPTIONS_HPP_
#define EXAMPLE_PACKAGE_EXCEPTIONS_HPP_

#include <sm/assert_macros.hpp>

namespace example {
    SM_DEFINE_EXCEPTION(RuntimeException, std::runtime_error);
    SM_DEFINE_EXCEPTION(InitializationException, std::runtime_error);
}

#endif
