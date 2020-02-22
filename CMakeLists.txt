# CMakeLists.txt --- CMake project settings
#    ex) cmake -G "Visual Studio 9 2008" .
#    ex) cmake -DCMAKE_BUILD_TYPE=Release -G "MSYS Makefiles" .
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 2.4)

# project name and language
project(DumpFontInfo CXX)

##############################################################################

# use freetype libraries
find_package(Freetype REQUIRED)

# include
include_directories(${FREETYPE_INCLUDE_DIRS})

# DumpFontInfo.exe
add_executable(DumpFontInfo DumpFontInfo.cpp)
target_link_libraries(DumpFontInfo ${FREETYPE_LIBRARIES})

##############################################################################
