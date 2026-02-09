add_library(ObjectLight STATIC
  "include/ObjectLight/Common.h"
  "include/ObjectLight/Function.h"
  "include/ObjectLight/uuid.h"
  "include/ObjectLight/Object.h"
  "include/ObjectLight/Objects.h"
  "include/ObjectLight/ObjectFactory.h"
  "include/ObjectLight/ObjectLight.h"
  "src/Object.cpp"
  "src/ObjectFactory.cpp"
  "src/ObjectLight.cpp"
  "src/uuid.cpp"
)

set(CMAKE_SYSTEM_NAME "Windows")
set(CMAKE_CXX_STANDARD 20)

set_target_properties(ObjectLight PROPERTIES COMPILE_DEFINITIONS "OBL_API_EXPORTS=1")

# Set include directories for the library and its dependents
target_include_directories(ObjectLight
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # Path during build
        $<INSTALL_INTERFACE:include>  # Path when installed (for find_package)
)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ObjectLight PROPERTY CXX_STANDARD 20)
endif()
