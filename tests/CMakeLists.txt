cmake_minimum_required(VERSION 3.15)


project(BitFlagsTests)

add_executable(${PROJECT_NAME}
    tests.cpp
    ../include/bitflags.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ../include
    ../thirdparty/doctest
)


add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
