# Set minimum CMake version (supports modern features like FetchContent)
cmake_minimum_required(VERSION 4.1)
 
# Project name and language (CXX for C++)
project(ObjectLightProject LANGUAGES CXX)

set(CMAKE_SYSTEM_NAME "Windows")
# Global C++ standard (applies to all subprojects by default)
set(CMAKE_CXX_STANDARD 20)

include(cmake/ObjectLightModule.cmake)
 
add_subdirectory(ObjectLight)  
add_subdirectory(OBLHost)        
add_subdirectory(Module) # Test Module
