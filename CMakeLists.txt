# - Main (Make a buildscript for mpags-cipher

# - Set (Make requirments then declare prokect
cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 0.1.0)

# - When Makefiles are generated, output all command lines by default
set(CMAKE_VERBOSE_MAKEFILE ON)

# - Don't allow C++ Compiler Vendor Extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# - Use our standard set of flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

# - Declare the build of mpags-cipher main program
add_executable(mpags-cipher mpags-cipher.cpp MPAGSCipher/TransformChar.cpp MPAGSCipher/TransformChar.hpp MPAGSCipher/ProcessCommandLine.cpp MPAGSCipher/ProcessCommandLine.hpp MPAGSCipher/RunCaesarCipher.cpp MPAGSCipher/RunCaesarCipher.hpp)

target_include_directories(mpags-cipher PRIVATE MPAGSCipher)

target_compile_features(mpags-cipher PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization)
