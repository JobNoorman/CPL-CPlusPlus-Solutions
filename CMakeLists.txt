project(CPL CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(hello Hello.cpp)

add_executable(exercsises
    main.cpp
    String.cpp
    Value.cpp
    JsonWriter.cpp
)
