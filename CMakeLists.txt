cmake_minimum_required(VERSION 3.0.0)
project(TATLINDATASERVICESTEST VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB_RECURSE SRC_FILES 
    src/reader_interface/*.cpp
    src/tape/*.cpp)
    
add_executable(TATLINDATASERVICESTEST main.cpp ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)
