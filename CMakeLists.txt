# Set minimum CMake version (supports modern features like FetchContent)
cmake_minimum_required(VERSION 4.1)

project(ObjectLight VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_SYSTEM_NAME "Windows")
set(CMAKE_CXX_STANDARD 20)

include(cmake/ObjectLightModule.cmake)

set(YAML_BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
add_subdirectory(extern/yaml-cpp)  

add_subdirectory(Module) # Test Module



add_library(ObjectLight STATIC
	src/ob_uuid_t.cpp
    src/ob_object_factory.cpp
    src/ob_object.cpp
    src/ob_object_light.cpp
)

target_include_directories(ObjectLight
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set_target_properties(ObjectLight
    PROPERTIES
      CXX_STANDARD 20)
endif()

add_library(ObjectLightHost STATIC 
    src/host/ob_host.cpp
    src/host/ob_regestry.cpp
)

target_link_libraries(ObjectLightHost PRIVATE ObjectLight)
# Link against yaml-cpp
target_link_libraries(ObjectLightHost PRIVATE yaml-cpp::yaml-cpp)

set_target_properties(ObjectLightHost
  PROPERTIES
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME oblhost)
