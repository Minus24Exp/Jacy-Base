cmake_minimum_required(VERSION 3.10)

project(Jacy VERSION 0.0.1)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/**/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} ${SOURCES} src/object/Object.cpp src/object/Bool.cpp src/object/Int.cpp src/object/Float.cpp src/object/String.cpp src/object/Class.cpp include/object/Class.h src/object/Func.cpp)

target_include_directories(Jacy PRIVATE ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS}")
