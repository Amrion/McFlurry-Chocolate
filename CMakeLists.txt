project(Bauman_Tinder CXX)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Werror -fprofile-arcs -ftest-coverage -fPIC")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Boost ublas
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include_db)
include_directories(.build/McFlurry-Chocolate/include_rec)

set(DANIL .build/McFlurry-Chocolate)

set(FIND_REC_LIB ${DANIL}/include_rec/recsys.hpp ${DANIL}/src_rec/recsys.cpp ${DANIL}/src_rec/als.cpp)
set(FIND_DB_LIB ${PROJECT_SOURCE_DIR}/include_db/Postgre_DB.h ${PROJECT_SOURCE_DIR}/src_db/Postgre_DB.cpp ${PROJECT_SOURCE_DIR}/src_db/TABLES.cpp)
add_library(find_db_lib SHARED ${FIND_DB_LIB})
add_library(find_rec_lib SHARED ${FIND_REC_LIB})


target_include_directories(find_db_lib PUBLIC ${PROJECT_SOURCE_DIR}/include_db)
target_include_directories(find_rec_lib PUBLIC ${DANIL}/include_rec)
 
add_executable(${PROJECT_NAME} src_db/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE find_db_lib -ldl -lpqxx -lpq ${Boost_LIBRARIES} find_rec_lib -ldl)

enable_testing()
add_executable(test_db test/test.cpp)
target_link_libraries(test_db find_db_lib -ldl -lpqxx -lpq ${Boost_LIBRARIES} find_rec_lib -ldl gtest_main)
include(GoogleTest)
gtest_add_tests(TARGET test_db)