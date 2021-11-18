cmake_minimum_required(VERSION 3.8)
set (CMAKE_CXX_STANDARD 23)

project(server)

include_directories(include)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

#  Async HTTP Server
add_executable(server include/server.h src/server.cpp include/connection.h src/connection.cpp include/router.h)
target_link_libraries(server  ${Boost_LIBRARIES} -lpthread)

enable_testing()
find_package(GTest REQUIRED)

include_directories(include)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(test_server tests/test.cpp)
target_link_libraries(test_server ${GTEST_LIBRARIES} -lpthread -lgteat -lgtest_mail)
