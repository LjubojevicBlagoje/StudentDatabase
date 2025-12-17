cmake_minimum_required(VERSION 3.16)
project(StudentDatabase CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(. external)

# ---- SQLite ----
find_package(SQLite3 REQUIRED)

# Library of your core project
add_library(studentdb
    Course.cpp
    Database.cpp
    Enrollment.cpp
    Student.cpp
    SqliteDB.cpp
)

target_link_libraries(studentdb PRIVATE SQLite::SQLite3)

# Main executable
add_executable(student_cli CLImain.cpp)
target_link_libraries(student_cli studentdb)

add_subdirectory(tests)
