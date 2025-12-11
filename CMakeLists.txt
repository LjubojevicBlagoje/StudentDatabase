cmake_minimum_required(VERSION 3.16)
project(StudentDatabase CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(. external)

# Library of your core project
add_library(studentdb
    Course.cpp
    Database.cpp
    Enrollment.cpp
    Student.cpp
)

# Main executable
add_executable(student_app main.cpp)
target_link_libraries(student_app studentdb)

# Add test subdirectory
add_subdirectory(tests)
