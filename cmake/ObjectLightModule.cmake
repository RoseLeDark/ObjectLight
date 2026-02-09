function(add_obl_module TARGET_NAME)
    add_library(${TARGET_NAME} SHARED ${ARGN})
    target_compile_definitions(${TARGET_NAME} PRIVATE -DOBLIGHT_MODULE_BUILD=1)
    target_link_libraries(${TARGET_NAME} PRIVATE ObjectLight)
endfunction()

