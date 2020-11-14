#include "String.hpp"

#include <cstring>
#include <utility>
#include <ostream>

String::String(const char* str) {
    str_ = new char[std::strlen(str) + 1];
    std::strcpy(str_, str);
}

String::String(const String& other) {
    str_ = new char[other.length() + 1];
    std::strcpy(str_, other.str_);
}

String::String(String&& other) {
    str_ = other.str_;
    other.str_ = nullptr;
}

String::~String() {
    delete[] str_;
}

String& String::operator=(String other) {
    std::swap(str_, other.str_);
    return *this;
}

String& String::operator=(String&& other) {
    std::swap(str_, other.str_);
    return *this;
}

std::size_t String::length() const {
    return std::strlen(str_);
}

bool String::empty() const {
    return length() == 0;
}

char* String::begin() {
    return str_;
}

char* String::end() {
    return str_ + length();
}

const char * String::c_str() const {
    return str_;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    return os << str.c_str();
}
