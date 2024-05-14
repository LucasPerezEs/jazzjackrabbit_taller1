/*
 * Created by Federico Manuel Gomez Peter
 * Date: 02/05/2018.
 */

#include "Exception.h"

#include <cstdarg>
#include <sstream>
#include <string>

Exception::Exception(const char* fmt, ...) noexcept {
    va_list args, args_copy;
    va_start(args, fmt);
    va_copy(args_copy, args);
    std::size_t size = std::vsnprintf(nullptr, 0, fmt, args) + 1;

    this->msg_error.reserve(size);
    std::vsnprintf(&this->msg_error.front(), size, fmt, args_copy);

    va_end(args_copy);
    va_end(args);
}

const char* Exception::what() const noexcept { return this->msg_error.c_str(); }
