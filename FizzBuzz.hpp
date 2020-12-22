#ifndef CPL_FIZZBUZZ_HPP
#define CPL_FIZZBUZZ_HPP

// <<<
template<unsigned N, bool Fizz, bool Buzz>
struct FizzBuzzValue {
    constexpr static unsigned value = N;
};

template<unsigned N>
struct FizzBuzzValue<N, true, false> {
    constexpr static const char* value = "Fizz";
};

template<unsigned N>
struct FizzBuzzValue<N, false, true> {
    constexpr static const char* value = "Buzz";
};

template<unsigned N>
struct FizzBuzzValue<N, true, true> {
    constexpr static const char* value = "FizzBuzz";
};


template<unsigned N>
struct FizzBuzz : FizzBuzzValue<N, N % 3 == 0, N % 5 == 0> {
};

template<unsigned N, unsigned Max>
void fizzbuzz() {
    std::cout << FizzBuzz<N>::value << ' ';

    if constexpr (N < Max) {
        fizzbuzz<N + 1, Max>();
    }
}

template<unsigned N>
void fizzbuzz() {
    fizzbuzz<1, N>();
    std::cout << '\n';
}

constexpr bool equal(unsigned u1, unsigned u2) {
    return u1 == u2;
}

constexpr bool equal(const char* s1, const char* s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        ++s1;
        ++s2;
    }

    return *s1 == *s2;
}

// >>>
static_assert(equal(FizzBuzz< 1>::value, 1u));
static_assert(equal(FizzBuzz< 2>::value, 2u));
static_assert(equal(FizzBuzz< 3>::value, "Fizz"));
static_assert(equal(FizzBuzz< 4>::value, 4u));
static_assert(equal(FizzBuzz< 5>::value, "Buzz"));
static_assert(equal(FizzBuzz< 6>::value, "Fizz"));
static_assert(equal(FizzBuzz< 7>::value, 7u));
static_assert(equal(FizzBuzz< 8>::value, 8u));
static_assert(equal(FizzBuzz< 9>::value, "Fizz"));
static_assert(equal(FizzBuzz<10>::value, "Buzz"));
static_assert(equal(FizzBuzz<11>::value, 11u));
static_assert(equal(FizzBuzz<12>::value, "Fizz"));
static_assert(equal(FizzBuzz<13>::value, 13u));
static_assert(equal(FizzBuzz<14>::value, 14u));
static_assert(equal(FizzBuzz<15>::value, "FizzBuzz"));
static_assert(equal(FizzBuzz<16>::value, 16u));
static_assert(equal(FizzBuzz<17>::value, 17u));
static_assert(equal(FizzBuzz<18>::value, "Fizz"));
static_assert(equal(FizzBuzz<19>::value, 19u));
static_assert(equal(FizzBuzz<20>::value, "Buzz"));

#endif
