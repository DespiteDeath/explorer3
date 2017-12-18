cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIERED ON)
set(CMAKE_CXX_COMPILER "g++")

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)

include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/DespiteDeath/hunter/archive/v0.19.137.1.tar.gz"
    SHA1 "f87f234951173424a4436d866252feeb849a9500"
)

project(explorer)

hunter_add_package(Boost COMPONENTS filesystem)
hunter_add_package(Catch)
find_package(Boost COMPONENTS filesystem REQUIRED)
find_package(Catch CONFIG REQUIRED)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/explorer.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/explorer.hpp)

add_library(explorer ${SOURCES} ${HEADERS})

target_link_libraries(explorer Boost::filesystem Catch::Catch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -I /usr/local/include -L /usr/local/lib -lboost_filesystem -lboost_system")

target_include_directories(explorer PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if(BUILD_EXAMPLES)
  file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
  foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} explorer)
    install(TARGETS ${EXAMPLE_NAME}
      RUNTIME DESTINATION bin
    )
  endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

if(BUILD_TESTS)
enable_testing()
file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
target_link_libraries(check ${PROJECT_NAME} ${DEPENDS_LIBRARIES})
add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes") 
endif()

