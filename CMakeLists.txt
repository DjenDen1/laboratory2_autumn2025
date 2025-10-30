cmake_minimum_required(VERSION 3.10.0)
project(laboratory2 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(laboratory2 main.cpp)

include(CTest)

enable_testing()

function(add_unit_test test_name test_source)
    add_executable(${test_name} ${test_source} main.cpp)
    add_test(NAME ${test_name} COMMAND ${test_name})
    target_link_libraries(${test_name} PRIVATE laboratory2)
endfunction()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp)
    add_unit_test(test_main test_main.cpp)
endif()

add_test(NAME MainApplicationTest COMMAND laboratory2)

option(ENABLE_COVERAGE "Enable code coverage" OFF)
if(ENABLE_COVERAGE)
    target_compile_options(laboratory2 PRIVATE --coverage)
    target_link_libraries(laboratory2 PRIVATE --coverage)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

