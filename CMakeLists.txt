cmake_minimum_required(VERSION 3.10)
project(TTT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include all source files from src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(TTT ${SOURCES})
target_include_directories(TTT PRIVATE src)

# add_subdirectory(tests) # Uncomment when tests are properly configured to link against core logic
