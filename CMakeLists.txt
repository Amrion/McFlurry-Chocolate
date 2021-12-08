cmake_minimum_required(VERSION 3.20)
project(server.wt)

set(CMAKE_CXX_STANDARD 14)

add_executable(server.wt src_server/TinderApplication.cpp src_server/main.cpp src_server/TinderServer.cpp src_server/TinderWidget.cpp src_server/User.cpp hash/md5.cpp)

find_package(Wt REQUIRED)

target_link_libraries(server.wt Wt::Wt Wt::HTTP)

include_directories(include_server)
include_directories(hash)