# Files
target_sources( cpp_logger
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/enums.h
    ${CMAKE_CURRENT_LIST_DIR}/logger.h

    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/logger.cpp
)

# Directories
target_include_directories( cpp_logger PUBLIC ${CMAKE_CURRENT_LIST_DIR} )
