# Files
target_sources( cpp_logger_tests
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/tests.cpp
)

# Directories
target_include_directories( cpp_logger_tests PUBLIC ${CMAKE_CURRENT_LIST_DIR} )
