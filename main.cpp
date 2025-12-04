#include <iostream>

#include "Database.h"
#include "Student.h"

int main() {
  Database d1;  // Initialise database

  // Initialise students
  Student Alice("1", 6), Bob("2", 1), Charlie("3", 2);

  // Add students to database
  d1.addStudent(&Alice);
  d1.addStudent(&Bob);
  d1.addStudent(&Charlie);

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