#include <iostream>

#include "Database.h"
#include "Student.h"

int main() {
  Database d1;  // Initialise database

  // Add students to database
d1.addStudent(std::make_unique<Student>("1", 6));
d1.addStudent(std::make_unique<Student>("2", 2));
d1.addStudent(std::make_unique<Student>("3", 1));

  // TEST1: should print details of all 3 students
  d1.printStudentDetails("1");
  d1.printStudentDetails("2");
  d1.printStudentDetails("3");

  // Remove charlie for test 2
  d1.removeStudent("3");
  std::cout<<"----------------------------------"<<std::endl;

  // TEST2: Should print details of just Alice and Bob
  d1.printStudentDetails("1");
  d1.printStudentDetails("2");
  d1.printStudentDetails("3");

  return 0;
}