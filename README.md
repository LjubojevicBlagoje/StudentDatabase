Student Database Management System (C++ / SQLite)
A command-line Student Database Management System written in modern C++, using SQLite for persistent storage and an in-memory data layer for fast runtime operations.

Features
Add, remove, and update students
Add and remove courses
Enroll students in courses with year/term/grade tracking
Drop enrollments and update grades
Compute:
Student GPA
Course average grades
Students enrolled in a specific course offering
Persistent storage using SQLite
Fast runtime queries using in-memory data structures

This system intentionally separates runtime performance from persistent storage.
Architecture
CLI (user input)
   ↓
Database (business logic)
   ↓
In-memory vectors (fast queries)
   ↓
SQLite database (durable storage)

SQLite is used for persistence, not for every query
All data is:
Loaded from SQLite at startup
Stored in memory during runtime
Written back to SQLite on every mutation
This allows:
Fast lookups and calculations
Easy future optimisation (e.g. replacing vectors with hash maps or indexes)
A clean, testable design

Database Schema
The SQLite database is stored as a single file (studentdb.sqlite) and uses the following schema:
Students
students(
  id TEXT PRIMARY KEY,
  first_name TEXT,
  last_name TEXT,
  semesters_completed INTEGER
)
Courses
courses(
  code TEXT PRIMARY KEY,
  name TEXT,
  units INTEGER
)
Enrollments
enrollments(
  student_id TEXT,
  course_code TEXT,
  year INTEGER,
  term TEXT,
  grade REAL,
  PRIMARY KEY (student_id, course_code, year, term),
  FOREIGN KEY (student_id) REFERENCES students(id) ON DELETE CASCADE,
  FOREIGN KEY (course_code) REFERENCES courses(code) ON DELETE RESTRICT
)
Foreign key constraints are enforced
Cascading deletes ensure referential integrity
Composite primary keys prevent duplicate enrollments

Build & Run
Requirements
CMake
SQLite3 development library
C++17 compatible compiler
Build
mkdir build
cd build
cmake ..
cmake --build .
./student_cli
