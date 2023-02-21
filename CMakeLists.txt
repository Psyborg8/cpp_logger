cmake_minimum_required( VERSION 3.9 )
project( cpp_logger VERSION 0.0.1 LANGUAGES CXX )

# Build commands
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_BUILD_TYPE "DEBUG" )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( cpp_logger_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src )
set( cpp_logger_LIBRARY_DIRS ${PROJECT_BINARY_DIR} )

# Create library
file( GLOB_RECURSE SRC src/*.cpp )
add_library( cpp_logger MODULE ${SRC})

target_include_directories( cpp_logger PUBLIC ${cpp_logger_INCLUDE_DIRS} )

link_directories( cpp_logger PUBLIC ${cpp_logger_LIBRARY_DIRS} )

target_link_libraries( cpp_logger PRIVATE fmt )

target_compile_options( cpp_logger PRIVATE -std=c++17 -Wall -Wextra )

if( CMAKE_BUILD_TYPE STREQUAL "DEBUG" )
    target_compile_options( cpp_logger PUBLIC -g3 )
    target_compile_definitions( cpp_logger PRIVATE _DEBUG=1 )
elseif( CMAKE_BUILD_TYPE EQUAL "RELEASE" )
    target_compile_options( cpp_logger PUBLIC -O2 )
endif()

set( cpp_logger_LIBRARY_DIRS "${cpp_logger_LIBRARY_DIRS} ${PROJECT_BINARY_DIR}" )

get_directory_property( HAS_PARENT_DIR PARENT_DIRECTORY )
if( HAS_PARENT_DIR )
    set( cpp_logger_LIBRARY_DIRS ${cpp_logger_LIBRARY_DIRS} PARENT_SCOPE )
    set( cpp_logger_INCLUDE_DIRS ${cpp_logger_INCLUDE_DIRS} PARENT_SCOPE )
endif()

# Installation
include( GNUInstallDirs )
configure_file( build/cpp_logger.pc.in cpp_logger.pc @ONLY )
install( TARGETS cpp_logger
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )
install( FILES ${CMAKE_BINARY_DIR}/cpp_logger.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR} )


# Tests
if( BUILD_TESTS )
    add_executable( cpp_logger_tests tests/tests.cpp )
    target_link_libraries( cpp_logger_tests cpp_logger )
    add_subdirectory( tests )
endif()
