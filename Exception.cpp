#include "Exception.h"

Exception::Exception(const std::string& except):exceptType(except){}

const char* Exception:: what() const noexcept { return exceptType.c_str(); }
