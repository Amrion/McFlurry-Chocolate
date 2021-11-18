project(Bauman_Tinder)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include_db)

set(FIND_DB_LIB ${PROJECT_SOURCE_DIR}/include_db/db_struct.h  ${PROJECT_SOURCE_DIR}/src_db/db_struct.cpp ${PROJECT_SOURCE_DIR}/include_db/db_pool.h ${PROJECT_SOURCE_DIR}/src_db/db_pool.cpp)

add_library(find_db_lib SHARED ${FIND_DB_LIB})
target_include_directories(find_db_lib PUBLIC ${PROJECT_SOURCE_DIR}/include_db)

add_executable(main test.cpp)
target_link_libraries(main PRIVATE find_db_lib -ldl)
