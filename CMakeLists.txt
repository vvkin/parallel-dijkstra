# set up CMake version
cmake_minimum_required(VERSION 3.7...3.22)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# project settings
project(
  dijkstra
  VERSION 1.0.0
  DESCRIPTION "Parallel implementation of Dijkstra's algorithm"
  LANGUAGES CXX)

# configure compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# add executable
set(SOURCES
    src/main.cpp
    src/graph.cpp
    src/factory.cpp
    src/writer.cpp
    src/serial.cpp
    src/parallel.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

# include headers
set(INCLUDES include src)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

# external packages
find_package(Boost 1.78 REQUIRED COMPONENTS program_options graph)
find_package(TBB REQUIRED COMPONENTS tbb)

# link external libraries
set(LIBRARIES Boost::program_options Boost::graph TBB::tbb)
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBRARIES})
