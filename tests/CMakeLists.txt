cmake_minimum_required(VERSION 2.8.7)

project (pwm)

# include project source
include_directories(${PROJECT_SOURCE_DIR}/..)

# include CppUTest headers
include_directories($ENV{CPPUTEST_HOME})

# add cpputest library
add_library(imp_cpputest STATIC IMPORTED)
set_property(TARGET imp_cpputest PROPERTY
             IMPORTED_LOCATION $ENV{CPPUTEST_HOME}/libCppUTest.a)

add_library(libpwmtest ./pwm_tests.cpp)

add_executable(RunAllTests RunAllTests.cpp)
target_link_libraries(RunAllTests imp_cpputest libpwmtest)

