project(Bauman_Tinder CXX)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Werror -fprofile-arcs -ftest-coverage -fPIC")
set(CMAKE_CXX_FLAGS_PROFILE --coverage)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Boost
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include_db)
include_directories(include_rec)

set(FIND_REC_LIB ${PROJECT_SOURCE_DIR}/include_rec/recsys.hpp ${PROJECT_SOURCE_DIR}/src_rec/recsys.cpp ${PROJECT_SOURCE_DIR}/src_rec/als.cpp)
set(FIND_DB_LIB ${PROJECT_SOURCE_DIR}/include_db/Postgre_DB.h ${PROJECT_SOURCE_DIR}/src_db/Postgre_DB.cpp ${PROJECT_SOURCE_DIR}/src_db/TABLES.cpp  ${PROJECT_SOURCE_DIR}/src_db/base64.cpp)
add_library(find_db_lib SHARED ${FIND_DB_LIB})
add_library(find_rec_lib SHARED ${FIND_REC_LIB})


target_include_directories(find_db_lib PUBLIC ${PROJECT_SOURCE_DIR}/include_db)
target_include_directories(find_rec_lib PUBLIC ${PROJECT_SOURCE_DIR}/include_rec)

# Build main
option(BUILD_MAIN OFF)
  if (BUILD_MAIN)
  add_executable(${PROJECT_NAME} src_db/main.cpp)
  target_link_libraries(${PROJECT_NAME} PRIVATE find_db_lib -ldl -lpqxx -lpq ${Boost_LIBRARIES} find_rec_lib -ldl)
endif()

#Build tests
option(BUILD_TESTS ON)
if (BUILD_TESTS)
  enable_testing()
  add_executable(tests_db test/tests_db.cpp)
  add_executable(tests_rec test/tests_rec.cpp)
  target_link_libraries(tests_db find_db_lib -ldl -lpqxx -lpq ${Boost_LIBRARIES} find_rec_lib -ldl gtest_main)
  target_link_libraries(tests_rec find_rec_lib -ldl ${Boost_LIBRARIES} gtest_main)
  include(GoogleTest)
  gtest_add_tests(TARGET tests_db)
  gtest_add_tests(TARGET tests_rec)
endif()

