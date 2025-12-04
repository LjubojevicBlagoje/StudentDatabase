#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "Student.h"

class Database {
 private:
  // Initialise a blank vector to which students will be added
  std::vector<Student*> students;
  int numberOfStudents;

 public:
  Database();  // Initialise
  void addStudent(Student* student);
  void removeStudent(std::string id);        // Remove student with this id
  void printStudentDetails(std::string id);  // Print student details
};

#endif