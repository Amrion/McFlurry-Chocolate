cmake_minimum_required(VERSION 3.20)
project(client.wt)

set(CMAKE_CXX_STANDARD 14)

add_executable(client.wt src_client/Tinder.cpp
        server_temp/TinderServer.cpp
        src_client/MainPageWidget.cpp
        )

find_package(Wt REQUIRED Wt HTTP)

target_link_libraries(client.wt Wt::Wt Wt::HTTP)

include_directories(headers_client)
