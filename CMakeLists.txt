cmake_minimum_required( VERSION 3.9 )

# Build commands
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_BUILD_TYPE "Debug" )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}" )

option( BUILD_SHARED_LIBS "Build using shared libraries" ON )

# Create library
project( cpp_logger VERSION 0.0.1 LANGUAGES CXX )
add_library( cpp_logger SHARED ${CMAKE_CURRENT_SOURCE_DIR} )
set_target_properties( cpp_logger PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER src/logger.hpp
    )

# Libraries
target_link_libraries( cpp_logger
    fmt
)

# Source files
add_subdirectory( src )

# Installation
include( GNUInstallDirs )
configure_file( cpp_logger.pc.in cpp_logger.pc @ONLY )
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
