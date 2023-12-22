# Add the current directory to the include paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add your main executable
add_executable(hnet hnet.c)

# Include HTTP source files directly
target_sources(hnet PRIVATE 
    http/http_req.c
)

# Link with other libraries as needed
target_link_libraries(hnet hstr_lib)

