#ifndef UTILS_TYPE_HPP
#define UTILS_TYPE_HPP

#if __cplusplus

#include <cxxabi.h>
#define type(args) abi::__cxa_demangle(typeid(args).name(), nullptr, nullptr, nullptr)

#endif

#endif //UTILS_TYPE_HPP
