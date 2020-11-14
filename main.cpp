#include <iostream>
#include <algorithm>

#include "String.hpp"

int main() {
    auto s = String("Hello, world");
    std::cout << s << '\n';

    std::sort(s.begin(), s.end());
    std::cout << s << '\n';
}
