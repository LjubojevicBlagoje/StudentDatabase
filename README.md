STUDENT DATABASE MANAGEMENT SYSTEM

A command-line student database system implemented in C++ using SQLite for
persistent storage and in-memory data structures for fast runtime operations.

The project demonstrates object-oriented design, safe SQLite integration,
and a clear separation between persistence and application logic.

FEATURES

  - Add, remove, and update students
  - Add and remove courses
  - Enroll students in courses with year, term, and grade
  - Drop enrollments and update grades
  - Compute student GPA
  - Compute course average grades
  - Query students enrolled in a course
  - Persistent storage using SQLite

DESIGN OVERVIEW

The system is intentionally split into two layers:
  - Persistent storage (SQLite)
  - Runtime data structures (in-memory vectors)

Data flow:
  - On startup:
   - SQLite database -> in-memory structures
  - During runtime:
   - All queries operate on in-memory data
  - On modification:
   - Write to SQLite first, then update memory

This design ensures:
  - Fast read operations
  - Data integrity via SQLite constraints
  - Clean separation of concerns
  - Easy future optimisation of in-memory structures
  - DATABASE SCHEMA

Students:
id (TEXT, PRIMARY KEY)
first_name (TEXT)
last_name (TEXT)
semesters_completed (INTEGER)

Courses:
code (TEXT, PRIMARY KEY)
name (TEXT)
units (INTEGER)

Enrollments:
student_id (TEXT)
course_code (TEXT)
year (INTEGER)
term (TEXT)
grade (REAL)

- PRIMARY KEY (student_id, course_code, year, term)
- FOREIGN KEY (student_id) REFERENCES students(id) ON DELETE CASCADE
- FOREIGN KEY (course_code) REFERENCES courses(code) ON DELETE RESTRICT
- Foreign key enforcement is enabled per SQLite connection.

TECHNOLOGIES

  - C++17
  - SQLite3
  - CMake
  - RAII and smart pointers
  - Prepared SQL statements

BUILD INSTRUCTIONS

Requirements:
  - CMake
  - SQLite3 development library
  - C++17 compatible compiler

Build:
  - mkdir build
  - cd build
  - cmake ..
  - cmake --build .
  - ./student_cli
