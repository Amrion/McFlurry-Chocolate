cmake_minimum_required(VERSION 3.20)
project(server.wt)

set(CMAKE_CXX_STANDARD 14)

add_executable(server.wt src_server/Session.cpp src_server/tinder.cpp src_server/TinderApp.cpp src_server/User.cpp)

find_package(Wt REQUIRED)

target_link_libraries(server.wt Wt::Wt Wt::HTTP Wt::Dbo -lwtdbosqlite3)

include_directories(include_server)