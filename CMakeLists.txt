project(Bauman_Tinder)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include_db)

set(FIND_DB_LIB ${PROJECT_SOURCE_DIR}/include_db/USERS_REC.h  ${PROJECT_SOURCE_DIR}/src_db/USERS_REC.cpp ${PROJECT_SOURCE_DIR}/include_db/USERS_INFO.h ${PROJECT_SOURCE_DIR}/include_db/PHOTOS.h ${PROJECT_SOURCE_DIR}/include_db/MARKS.h ${PROJECT_SOURCE_DIR}/include_db/DIALOGS.h ${PROJECT_SOURCE_DIR}/include_db/DataBase.h)

add_library(find_db_lib SHARED ${FIND_DB_LIB})
target_include_directories(find_db_lib PUBLIC ${PROJECT_SOURCE_DIR}/include_db)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(tests)
add_executable(test_db tests/test.cpp)
target_link_libraries(test_db find_db_lib gtest_main)

include(GoogleTest)
gtest_add_tests(TARGET test_db)