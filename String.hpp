#ifndef CPL_STRING_HPP
#define CPL_STRING_HPP

#include <cstddef>
#include <iosfwd>

class String {
    public:

        String(const char* str = "");
        String(const String& other);
        String(String&& other);
        ~String();

        String& operator=(String other);
        String& operator=(String&& other);

        std::size_t length() const;
        bool empty() const;

        char* begin();
        char* end();

        const char* c_str() const;

    private:

        char* str_;
};

bool operator<(const String& lhs, const String& rhs);

std::ostream& operator<<(std::ostream& os, const String& str);

#endif
