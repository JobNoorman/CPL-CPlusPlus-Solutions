- [Setup](#setup)
- [A simple string implementation](#a-simple-string-implementation)
  - [Basic constructors and destructors](#basic-constructors-and-destructors)
  - [Accessors and streaming](#accessors-and-streaming)
  - [Copying](#copying)
  - [Moving](#moving)
  - [Iterating](#iterating)
- [Visitor pattern](#visitor-pattern)
  - [Value hierarchy](#value-hierarchy)
  - [Visiting](#visiting)
- [FizzBuzz](#fizzbuzz)
  - [Compile-time string equality](#compile-time-string-equality)
  - [Compile-time FizzBuzz](#compile-time-fizzbuzz)

# Setup

> :information_source: To install everything you need to start working on Ubuntu, run the following command:
> ```shell
> $ sudo apt install build-essential cmake
> ```
> For other platforms, manually install the tools explained below.

C++ does not come with an official IDE, compiler, or build system.
To start working with C++, the minimum you need is a compiler and many have been created over the years.
Since complying C++ compilers should follow the ISO standard, the choice of compiler is often dictated by the platform on which you are building your code, as some compilers might support certain platforms better than others.
Other reasons might be how quickly compilers support the newest standards, how optimized their generated code is, or how fast they are able to compile code.

The three most well-known C++ compilers are:
- [GCC][gcc]: The GNU Compiler Collection.
  An open source compiler that supports many languages, including C and C++.
  It's cross-platform (often installed through [MinGW][mingw] on Windows) and has great support for the newest C++ standards.
- [Clang][clang]: The C/C++ frontend for the [LLVM][llvm] compiler infrastructure.
  Open source, cross-platform and great support for the newest C++ standards.
- [Microsoft Visual C++][msvc]: Proprietary, Windows-only official toolchain from Microsoft.
  Probably the only possible compiler if you want to use Visual Studio.
  Often a bit slower with picking up the newest standards although this seems to have improved in recent years.

All the exercises in this session have been tested with GCC 9.3 and Clang 10.0.
However, any compiler that [supports the core language features of C++17][c++17 support] should work.

This repository includes a file called [`Hello.cpp`](Hello.cpp) which contains the "Hello, world" program shown in the lecture.
You can compile this file to an executable called `hello` using one of the following commands:
- GCC: `g++ Hello.ccp -o hello`
- Clang: `clang++ Hello.ccp -o hello`
- Microsoft Visual C++: `cl Hello.cpp /out:hello.exe` (Sorry, not tested.)

For larger projects, are build system is typically used to manage the compilation of a larger number of source files.
Some "native" build systems include:
- [GNU Makefiles][gnu make] on Linux;
- [Xcode] projects on macOS;
- [Visual Studio][vs] projects on Windows.

But there are many more.
In this session, we use [CMake][cmake], a cross-platform build system generator.
It works by reading a file called [`CMakeLists.txt`](CMakeLists.txt) and generating a native build system for the host platform.
It supports many different native build systems but the default used for each platform is the one shown in the list above.

CMake encourages to use a so-called _out of source_ build where all build files are kept in a separate directory.
The following commands can be run from the directory of this repository to create the native build system:
```shell
$ mkdir build
$ cd build
$ cmake ..
```

Now we have a directory called `build` that contains the native build system (e.g., GNU Makefiles on Linux).
Note that this step only has to be run once, after that the native build system will be used.
Even when `CMakeLists.txt` is updated, the native build system will automatically run `cmake` again.

To actually compile our project, we have to invoke the native build system.
This can be done in a platform-independent way using `cmake` (from the `build` directory):
```shell
$ cmake --build .
```

Or we can invoke the native build system directly (example for GNU Make):
```shell
$ make
```

After compilation, two executable should have been created in the `build` directory: `hello` compiled from `Hello.cpp`, and `exercises`, compiled from `main.cpp` and all other source files used for the exercises.
You can add code to `main.cpp` to test the various classes created in this session.

The choice for an IDE is often a personal one and I won't enforce the use of any specific tool for this session.
Of course, a simple text editor is enough to start writing C++ code and the build system can simply be invoked from the command line.
For the people looking for an editor with some more C++ support, here are some popular ones:
- [KDevelop][kdevelop] (Ubuntu package `kdevelop`): Open source cross-platform IDE but works best on Linux.
  Has very good support for C++ and CMake.
  I personally use this one.
- [Qt Creator][qtcreator] (Ubuntu package `qtcreator`): Open source cross-platform IDE from the [Qt][qt] project.
  Has very good support for C++ and CMake.
- [Xcode][xcode] on macOS.
- [Visual Studio][vs] on Windows.

I want to note that I don't have a lot (if any) experience with the latter two, and I've used Qt Creator only a handful of times.
If you want to use them, I probably won't be able to give a lot of support about their setup.
But since CMake is a very popular build system, you'll find a lot of support online.

# A simple string implementation

In this exercise, we will create a simple yet fully-functional implementation of a string.
It will have the following features:
- Wraps around a simple C-style string;
- Copyable and movable;
- Iteration over the underlying characters;
- Can be streamed to standard output streams.

The class called `String` should be implemented in [`String.hpp`](String.hpp) and [`String.cpp`](String.cpp).
At every step, verify your implementation by writing test code in [`main.cpp`](main.cpp).

## Basic constructors and destructors

This `String` class should support two constructors:
- `String()`: Creates an empty string (`""`);
- `String(const char* str)`: Creates a string by copying the given C-style string.

> :bulb: Functions in C++ support [default arguments][default args].
> You can use this to implement a single constructor that supports both use cases.

The constructors should allocate enough memory on the heap to store the string including the terminating null-character.
For this exercise, we will use raw pointers, as opposed to smart pointers, to practice building our own [RAII][raii]-enabled class.

To allocate an array on the heap, the following special syntax of the [`new` operator][new] can be used:
```cpp
char* a = new char[size];
```

Make sure all resources are released at the end of a `String`'s lifetime by implementing a destructor.
Note that memory allocated using `new[]` should deallocated using [`delete[]`][delete].

## Accessors and streaming

Now add the following accessors:
- `length()`: Return the length of the string (_without_ null-terminator);
- `empty()`: Return `true` of the string is empty;
- `c_str()`: Return a pointer to the underlying C-style string.

Make these methods `const` where possible.
`c_str()` should be overloaded to either return a mutable or immutable pointer to the underlying C-string.

C++ uses the `<<` operator for sending data to a stream.
We have already seen this operator in action when printing to stdout:
```cpp
std::cout << "Hello, world!\n";
```

`std::cout` is an instance of the [`std::ostream`][ostream] class which represent an _output stream_; a stream that can be written to.
Another example of an `std::ostream` is the [`std::stringstream`][stringstream] class which allows data to be written to a [`std::string`][string].

`operator<<` for `std::ostream` has overloads for [all fundamental type][ostream stream op1] as well as for [characters and character arrays][ostream stream op2].
This operator can be overloaded for custom types to add support for streaming:
```cpp
std::ostream& operator<<(std::ostream& os, const CustomType& ct);
```

Note that a reference to the original stream should be returned.
This is to support _chaining_:
```cpp
std::cout << "Hello, " << "World" << '!';
```

Implement this operator for the `String` class.

## Copying

Try to make a copy of a `String` instance and see what happens.
Since the C++ compiler will implicitly define a [copy constructor][copy ctor] that simply copies the underlying pointer, your program will most likely crash when this pointer is deleted twice.
Fix this problem by implementing a copy constructor that clones the underlying data.

There is one other problem that has not been discussed in the lecture: [assignment][assignment].
Try to create two `String` instances and assign one to the other:
```cpp
auto s1 = String(...);
auto s2 = String(...);
s1 = s2;
```

This code will assign `s1` from `s2`.
C++ will implicitly define an _assignment operator_ for custom types that allow such types to be assigned from objects of their own type.
As with copy constructors, this implicit assignment operator simply assigns all members from the corresponding members of the source.
This will create the same problems when the members contain pointers or references.

Assignment can be customized by overloading `operator=` as a member function.
It commonly has the following signature:
```cpp
CustomType& operator=(const CustomType& other);
```

Although not enforced by C++, assignment operators are encouraged to return a reference to `*this` to allow assignment chaining (which fundamental types support):
```cpp
String s1, s2, s3;
s1 = s2 = s3;
(s1 = s2) = s3
```

Implement an assignment operator that fixes the problems with the implicitly generated one.
Make sure that your implementation correctly handles _self assignment_ which, although uncommon, may happen due to references being passed around:
```cpp
s1 = s1;
```

## Moving

Now implement support for moving `String` objects.
We already mentioned move constructors in the lecture:
```cpp
CustomType(CustomType&& other);
```

There is also _move assignment_:
```cpp
CustomType& operator=(CustomType&& other);
```

Implement both these operations.
Remember that the object which is moved into the current object, should be left in a safe state to be destructed.
Note that C++ allows `delete` to be called on a `nullptr`.

Experiment a bit with constructing and assigning `String`s in various ways and check when the different constructor and assignment operators are called.

## Iterating

Now make sure your `String` supports iterating over its characters by implementing `begin()` and `end()` methods.
Make sure you can iterate over `const String`s by adding overloads.
Verify that your implementation works by using it in, for example, [range-based for loops][range for] or by using some [algorithms][algorithms].
Try, for example, to transform a string to upper case in two ways: one using range-based for loops, and one using [`std::transform`][transform].

> :bulb: Remember that pointers are iterators.

# Visitor pattern

In this exercise, we'll implement the [visitor pattern][visitor] to generate [JSON][json] from a class hierarchy representing values.

## Value hierarchy

Implement the classes described below in [`Value.hpp`](Value.hpp) and [`Value.cpp`](Value.cpp).

Start with implementing a class hierarchy to represent values.
The abstract base class `Value` should not currently contain any methods but make sure it's safe to use as a base class.
To ensure this class cannot be constructed, you could mark its default constructor as `protected`.

The following concrete subclasses should be defined:
- `BoolValue`: Wrapper around a `bool`.
  Should have a constructor accepting a `bool` and a getter returning it.
- `IntValue`, `StringValue`: Similar to `BoolValue` except for wrapping an `int` and a `String` respectively.
  Use the `String` class created in the previous exercise.
- `SeqValue`: Represents an ordered sequence of `Value`s.
  Chose an appropriate [container][containers] that allows elements to be added.
  The container should store `Value`s inside a [`std::unique_ptr`][unique_ptr].
  Add a method to add a value to the sequence.
  Also make sure you can iterate over the values (immutable iteration is enough).
  > :bulb: You can just use the iterators of the underlying container.
  > Iterators of STL containers can have very long and annoying names to spell, though.
  > You can make your life easier by using a [_type alias_][type alias].
  > For example:
  > ```cpp
  > using IntIterator = std::vector<int>::const_iterator;
  > ```
- `StructValue`: Represents a mapping from `String`s to `Value`s, again storing the values inside a `std::unique_ptr`.
  There are two types of maps that you can use in C++:
  - [`std::map<K, V>`][map]: Map that sorts its elements based on the key.
    This means that `K` should have `operator<` overloaded.
  - [`std::unordered_map<K, V>`][unordered_map]: Hash-map that requires [`std::hash`][hash] to be specialized for `K`.

  Since our custom `String` class will be used as the key, support has to be added for either of those maps.
  The easiest to support would be `std::map`.

  Both maps represent their key-value mapping as pairs; that is, as [`std::pair<K, V>`][pair].
  Elements can be added as a pair using [`insert`][map insert] and their iterators iterate over pairs.
  > :bulb: Note that all containers have a type alias called `value_type` to represents the underlying value.
  > For maps this is `std::pair<K, V>`.

  Add methods to insert new values and to iterate (immutably) over the existing ones.

## Visiting

Now add an abstract class called `ValueVisitor` in [`ValueVisitor.hpp`](#ValueVisitor.hpp) that defines pure-virtual `visit` methods for all concrete value classes described above.
Also implement the necessary `accept` methods in the `Value` hierarchy.

> :bulb: You will now run into an annoying circular dependency between `ValueVisitor` (which needs to know the concrete `Value` subclasses) and `Value` (which needs to know `ValueVisitor` for `accept`).
> Simply having each header `#include` the other will not work (why not?).
> You can break this circle by [_forward declaring_][forward declaration] some classes.
> For example:
> ```cpp
> class ValueVisitor;
> ```
> This tells the compiler "there exists a class called ValueVisitor".
> From this point on, it is legal to declare pointers or references to a `ValueVisitor`.
> You cannot dereference them, though, as the compiler needs to know the contents of the class for that.

Make a class called `JsonWriter` in [`JsonWriter.hpp`](JsonWriter.hpp) and [`JsonWriter.cpp`](JsonWriter.cpp) that implements the `ValueVisitor` interface.
The goal of this class is to write a JSON representation of a `Value` (and all its sub-`Value`s, if any) to a `std::ostream`.

> :bulb: We mentioned in the lecture that we should never store raw pointers or references.
> However, if we want our `JsonWriter` class to support global output streams like `std::cout`, it is impossible to store an owning smart pointer.
> Since a `JsonWriter` is supposed to be a short-lived object who's lifetime can end immediately after calling `accept` on a value, this is a case where storing a raw reference can be justified.
> There will always be cases where breaking one of the guidelines is fine, just don't make a habit out of it.

> :bulb: The C++17 feature called [_structured bindings_][structured binding] may help in this exercise.
> It provides an easy syntax to _destructure_ values like `std::pair`.
> For example:
> ```cpp
> auto p = std::pair<int, double>(1, 2.3);
> auto& [i, d] = p;
> ```
> Here, `i` and `d` will be references to the values in `p`.

Verify your implementation by creating a `Value` that represents the following JSON and converting it back to JSON:
```json
{
    "seq": [false, "Hello"],
    "val": 42
}
```

# FizzBuzz

As should be clear by now, no self-respecting CPL exercise session can ignore the important [FizzBuzz][fizzbuzz] challenge.
However, we will give it a C++-twist here and do something that, AFAIK, neither Rust nor WebAssembly can do: calculate FizzBuzz at compile-time.
Our end-goal is to make the following code compile:
```cpp
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
```

[`static_assert`][static_assert] is an assertion that is evaluated at compile-time.
This means that if its argument evaluates to `false`, a compilation error will be generated.

The main goal of this exercise is to create a template class who's forward declaration looks like this:
```cpp
template<unsigned N>
struct FizzBuzz;
```

Depending on the value of `N`, this class should either have a `value` member of type `unsigned` equal to `N`, or of type `const char*` equal to `"Fizz"`, `"Buzz"`, or `"FizzBuzz"`.
Yes, varying the type of a member based on template parameters is possible in C++.

## Compile-time string equality

First things first: to evaluate the `static_assert`s above, we need a way to compare strings at compile time.
Since C++11, C++ supports the [`constexpr`][constexpr] specifier that allows us to create, among others, variables and functions that _could_ be evaluated at compile time.
I say _could_ because these functions may also be used at run-time; only if they are provided with compile-time constants as arguments, they can be evaluated at compile-time.

Initially, `constexpr` functions where very restricted and could essentially contain a single `return` statement.
They were allowed to be recursive, though, so this could be used to implement our compile-time string equality check.
Fortunately, C++17 relaxed the requirements on `constexpr` functions and they can now contain almost everything except `goto`s and `try`-blocks.

Implement a string equality function with the following signature:
```cpp
constexpr bool equal(const char* s1, const char* s2);
```

Verify your implementation by writing some `static_assert`s.

> :bulb: If the compiler needs to evaluate something at compile time, it needs to be able to see the full implementation.
> This means you cannot put the implementation of `equal` in a `.cpp` file if you want to be able to use it, at compile-time, from another file.
> This also holds in general for template classes and functions.
> Both templates and `constexpr` functions should therefore be implemented in header files.

Also make an overload of this function that accepts `unsigned` parameters.

## Compile-time FizzBuzz

The challenge here is to make the `FizzBuzz` class have a different implementation based on the value of `N`.
We've already seen a basic way of doing this: template specialization.
For example:
```cpp
template<unsigned N>
struct FizzBuzz {
    constexpr static unsigned value = N;
};

template<>
struct FizzBuzz<3> {
    constexpr static const char* value = "Fizz";
};
```

> :bulb: Like in Java, the `static` specifier makes a variable a class-member.
> This means we don't need an object to access it.
> `static` members in C++ can be accessed using `ClassName::member`.

However, we obviously don't want to manually add specializations for all multiples of 3 and 5.
For one, this would be boring.
Also, it would only allow us to calculate a fixed number of FizzBuzz values.

I will give a hint about a possible solution and then leave the joy of solving this challenge up to you.

Let's say we want to design a matrix class with compile-time size parameters.
Of course, we would like this class to have a `determinant` method only if the matrix is square.
This could be done using specialization as follows:
```cpp
template<typename T, unsigned Rows, unsigned Cols, bool IsSquare>
struct MatrixMixins {};

template<typename T, unsigned Rows, unsigned Cols>
struct MatrixMixins<T, Rows, Cols, true> {
    T determinant() {
        // Calculate determinant
    }

    // Other methods specific to square matrices
};

template<typename T, unsigned Rows, unsigned Cols>
struct Matrix : MatrixMixins<T, Rows, Cols, /*IsSquare=*/Rows == Cols> {
    // General matrix methods go here
};

Matrix<int, 1, 2>().determinant(); // compiler error
Matrix<int, 2, 2>().determinant(); // ok
```

Have fun!

[gcc]: https://gcc.gnu.org/
[mingw]: http://www.mingw.org/
[clang]: https://clang.llvm.org/
[llvm]: https://www.llvm.org/
[msvc]: https://docs.microsoft.com/en-us/cpp
[c++17 support]: https://en.cppreference.com/w/cpp/compiler_support/17
[gnu make]: https://www.gnu.org/software/make/
[xcode]: https://developer.apple.com/xcode/
[vs]: https://visualstudio.microsoft.com/vs/
[cmake]: https://cmake.org/
[kdevelop]: https://www.kdevelop.org/
[qtcreator]: https://wiki.qt.io/Qt_Creator
[qt]: https://www.qt.io/
[default args]: https://en.cppreference.com/w/cpp/language/default_arguments
[new]: https://en.cppreference.com/w/cpp/memory/new/operator_new
[delete]: https://en.cppreference.com/w/cpp/language/delete
[raii]: https://en.cppreference.com/w/cpp/language/raii
[ostream]: https://en.cppreference.com/w/cpp/io/basic_ostream
[stringstream]: https://en.cppreference.com/w/cpp/io/basic_ostream
[string]: https://en.cppreference.com/w/cpp/string/basic_string
[ostream stream op1]: https://en.cppreference.com/w/cpp/io/basic_ostream/operator_ltlt
[ostream stream op2]: https://en.cppreference.com/w/cpp/io/basic_ostream/operator_ltlt2
[copy ctor]: https://en.cppreference.com/w/cpp/language/copy_constructor
[assignment]: https://en.cppreference.com/w/cpp/language/operator_assignment
[range for]: https://en.cppreference.com/w/cpp/language/range-for
[algorithms]: https://en.cppreference.com/w/cpp/algorithm
[visitor]: https://en.wikipedia.org/wiki/Visitor_pattern
[json]: https://en.wikipedia.org/wiki/JSON
[containers]: https://en.cppreference.com/w/cpp/container
[unique_ptr]: https://en.cppreference.com/w/cpp/memory/unique_ptr
[type alias]: https://en.cppreference.com/w/cpp/language/type_alias
[map]: https://en.cppreference.com/w/cpp/container/map
[unordered_map]: https://en.cppreference.com/w/cpp/container/unordered_map
[hash]: https://en.cppreference.com/w/cpp/utility/hash
[pair]: https://en.cppreference.com/w/cpp/utility/pair
[map insert]: https://en.cppreference.com/w/cpp/container/map/insert
[structured binding]: https://en.cppreference.com/w/cpp/language/structured_binding
[forward declaration]: https://en.wikipedia.org/wiki/Forward_declaration
[fizzbuzz]: https://en.wikipedia.org/wiki/Fizz_buzz
[static_assert]: https://en.cppreference.com/w/cpp/language/static_assert
[constexpr]: https://en.cppreference.com/w/cpp/language/constexpr
[transform]: https://en.cppreference.com/w/cpp/algorithm/transform
