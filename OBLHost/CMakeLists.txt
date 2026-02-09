# Define the library target 
add_library(OBLHost SHARED
    src/OBLHost.cpp  # Source file
    include/OBLHost/OBLHost.h  # Header (optional, but helps IDEs)
)
 
# Set include directories for the library and its dependents
target_include_directories(OBLHost
    PUBLIC  # "PUBLIC" propagates this include path to dependents (e.g., app/tests)
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # Path during build
        $<INSTALL_INTERFACE:include>  # Path when installed (for find_package)
)

# Link ObjectLight
target_link_libraries(OBLHost
    PRIVATE  # "PRIVATE" 
        OObjectLightL  # Link against the math_utils target
)
 

