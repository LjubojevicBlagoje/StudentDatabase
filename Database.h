#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "Student.h"

class Database {
 private:
  // Initialise a vector of students (smart pointers)
  std::vector<std::unique_ptr<Student>> students;

 public:
  Database();  // Initialise
  void addStudent(std::unique_ptr<Student> student);
  void removeStudent(const std::string& id);  // Remove student with this id
  void printStudentDetails(const std::string& id);  // Print student details
};

#endif