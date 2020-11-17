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

# Setup

> :information_source: To install everything you need to start working on Ubuntu, run the following command:
> ```shell
> $ sudo apt install build-essential cmake
> ```
> For other platforms, manually install the tools explained below.

C++ does not come with an official IDE, compiler, or build system.
To start working with C++, the minimum you need is a compiler and many have been created over the years.
Since complying C++ compilers should follow the ISO standard, the choice of compiler is often dictated by the platform on which you are building your code, as some compiler might support certain platforms better than others.
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

All the exercises in this session have been tested with GCC 9.3.0 and Clang 10.0.
However, any compiler that [supports the core language features of C++17][c++17 support] should work.

This repository includes a file called [`Hello.cpp`](Hello.cpp) which contains the "Hello, world" program shown in the lecture.
You can compile this file to an executable called `hello` using the following command:
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
It supports many different native build systems but the default used is the one shown in the list above.

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

# A simple string implementation

In this exercise, we will create a simple yet fully-functional implementation of a string.
It will have the following features:
- Wraps around a simple C-style string;
- Copyable and movable;
- Iteration over the underlying characters;
- Can be streamed to standard output streams.

The class called `String` should be implemented in [`String.hpp`](String.hpp) and [`String.cpp`](String.cpp).

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
If you want to be able to iterate over `const String`s, also implement `cbegin()` and `cend()` which should return immutable iterators.
Verify that your implementation works by using it in, for example, [range-based for loops][range for] or by using some [algorithms][algorithms].

> :bulb: Remember that pointers are iterators.

# Visitor pattern

In this exercise, we'll implement the [visitor pattern][visitor] to generate [JSON][json] from a class hierarchy representing generic values.

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
  There are two types of map that you can use in C++:
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
The goals of this class is to write a JSON representation of a `Value` (and all its sub-`Value`s, if any) to a `std::ostream`.

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
