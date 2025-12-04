#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "Student.h"

class Database {
 private:
  std::vector<Student*> students;
  int numberOfStudents;

  public:
  Database();
  void addStudent(Student* student);
  void removeStudent(std::string id);
};

#endif;