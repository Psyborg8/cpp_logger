cmake_minimum_required( VERSION 3.9 )
project( cpp_logger )

# Build commands
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Create library
file( GLOB_RECURSE SRC src/*.cpp )
add_library( cpp_logger ${SRC})

add_subdirectory( ${CMAKE_CURRENT_LIST_DIR}/deps/cpp_consoler )
add_dependencies( cpp_logger cpp_consoler )

target_include_directories( cpp_logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src )

find_package( fmt )
target_link_libraries( cpp_logger fmt::fmt cpp_consoler )

target_compile_options( cpp_logger 
    PRIVATE 
        -std=c++17 
        -Wall 
        -Wextra 
        -Wno-unused-parameter
)

# Build Type
if( CMAKE_BUILD_TYPE STREQUAL "DEBUG" )
    target_compile_options( cpp_logger PRIVATE -ggdb3 -Og )
    target_compile_definitions( cpp_logger PRIVATE _DEBUG=1 )
elseif( CMAKE_BUILD_TYPE EQUAL "RELEASE" )
    target_compile_options( cpp_logger PRIVATE -O2 )
endif()

# Tests
if( CPP_LOGGER_BUILD_TESTS )
    file( GLOB_RECURSE TEST_SRC tests/*.cpp )
    add_executable( cpp_logger_tests ${TEST_SRC} )
    target_link_libraries( cpp_logger_tests cpp_logger )
endif()
