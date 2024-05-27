cmake_minimum_required(VERSION 3.2)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set default value for debug if not specified
if(NOT DEFINED debug)
    set(debug FALSE)
endif()

if(debug)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_SUPPRESS_REGENERATION ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project info
project("raytracer" CXX)
set(PROJECT_BIN_FOLDER ".")
set(PROJECT_BINARY_NAME "raytracer")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BIN_FOLDER})
set(BINARY_PATH ${CMAKE_SOURCE_DIR}/${PROJECT_BIN_FOLDER}/${PROJECT_BINARY_NAME})

# Include directories
file(GLOB_RECURSE INCLUDE_DIRS "src/*.hpp" "src/*.h" "include/*.hpp"
    "include/*.h" "libs/*.hpp" "libs/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "libs/*.cpp")

foreach(INCLUDE_DIR ${INCLUDE_DIRS})
    get_filename_component(DIR ${INCLUDE_DIR} DIRECTORY)
    include_directories(${DIR})
endforeach()

add_executable(${PROJECT_BINARY_NAME} ${INCLUDE_DIRS} ${SOURCE_FILES})

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_library(LIBCONFIG++ libconfig++)

# Link SFML to your executable
target_link_libraries(${PROJECT_BINARY_NAME} sfml-graphics sfml-audio config++)

install(TARGETS ${PROJECT_BINARY_NAME} DESTINATION ${PROJECT_BIN_FOLDER})

# Compiler flags
if (debug)
    target_compile_options(${PROJECT_BINARY_NAME} PRIVATE -Wall -Wextra -Werror -pedantic -Werror=overloaded-virtual -g)
else ()
    target_compile_options(${PROJECT_BINARY_NAME} PRIVATE -Wall -Wextra -O3 -ffast-math)
endif ()

# run will build and run the payload
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "-- Running raytracer --"
    COMMAND raytracer
    DEPENDS raytracer
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

# run valgrind on payload
add_custom_target(valgrind
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "-- Running valgrind on raytracer --"
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --config Debug
    COMMAND valgrind --leak-check=full ${BINARY_PATH}
    DEPENDS raytracer
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

# ppm rule will redirect the output of raytracer to ./tmp/[random_name].ppm folder (create if not exists) and open the file with xdg-open
execute_process(COMMAND date +%s OUTPUT_VARIABLE current_date OUTPUT_STRIP_TRAILING_WHITESPACE)
add_custom_target(ppm
    COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "-- Running raytracer and opening the ppm file --"
    COMMAND mkdir -p .tmp
    COMMAND ${BINARY_PATH} > .tmp/${current_date}.ppm
    COMMAND find .tmp -type f -mmin +60 -delete
    COMMAND xdg-open .tmp/${current_date}.ppm
    DEPENDS raytracer
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
