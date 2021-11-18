cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 11)

project(recsys CXX)

include(FetchContent)
FetchContent_Declare( 
    googletest 
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
) 
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) 
FetchContent_MakeAvailable(googletest)


# This flags are used if cmake is called with -DCMAKE_BUILD_TYPE=PROFILE
set(CMAKE_CXX_FLAGS_PROFILE --coverage)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set cpp compile flags
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Werror -fprofile-arcs -ftest-coverage -fPIC")

include_directories(include_rec)

set(FIND_RECSYS_LIB ${PROJECT_SOURCE_DIR}/include_rec/recsys.hpp ${PROJECT_SOURCE_DIR}/src_rec/recsys.cpp ${PROJECT_SOURCE_DIR}/src_rec/nmf.cpp ${PROJECT_SOURCE_DIR}/src_rec/matrix.cpp)
add_library(find_recsys_lib SHARED ${FIND_RECSYS_LIB})
target_include_directories(find_recsys_lib PUBLIC ${PROJECT_SOURCE_DIR}/include_rec)

# Build main
option(BUILD_MAIN OFF)
if (BUILD_MAIN)
    add_executable(${PROJECT_NAME} src_rec/main.cpp)
    target_link_libraries(${PROJECT_NAME} PRIVATE find_recsys_lib -ldl)
endif()

# Build test
option(BUILD_TESTS ON)
if (BUILD_TESTS)
    enable_testing()
    include(GoogleTest)

    include_directories(${GTEST_INCLUDE_DIRS})

    add_executable(libgtest tests/gtests.cpp)
    target_link_libraries(libgtest ${GTEST_LIBRARIES} find_recsys_lib -ldl gtest_main)
    gtest_add_tests(TARGET libgtest)
endif()
