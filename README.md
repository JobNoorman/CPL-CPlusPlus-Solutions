- [Setup](#setup)

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
