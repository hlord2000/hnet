# Create a library target
add_library(hstr_lib STATIC hstr/src/hstr.c)

# Specify include directories
target_include_directories(hstr_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/hstr/src)

