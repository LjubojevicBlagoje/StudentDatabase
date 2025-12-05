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
  if(const Student* s = d1.findStudentById("1")){
    std::cout<<d1.findStudentById("1")->getId()<<" | "<<d1.findStudentById("1")->getSemestersCompleted()<<std::endl;
  } else {
    std::cout<<"Student not found"<<std::endl;
  }

  if(const Student* s = d1.findStudentById("2")){
    std::cout<<d1.findStudentById("2")->getId()<<" | "<<d1.findStudentById("2")->getSemestersCompleted()<<std::endl;
  } else {
    std::cout<<"Student not found"<<std::endl;
  }

  if(const Student* s = d1.findStudentById("3")){
    std::cout<<d1.findStudentById("3")->getId()<<" | "<<d1.findStudentById("3")->getSemestersCompleted()<<std::endl;
  } else {
    std::cout<<"Student not found"<<std::endl;
  }

  // Remove charlie for test 2
  d1.removeStudent("3");
  std::cout << "----------------------------------" << std::endl;

  // TEST2: Should print details of just Alice and Bob
  if(const Student* s = d1.findStudentById("1")){
    std::cout<<d1.findStudentById("1")->getId()<<" | "<<d1.findStudentById("1")->getSemestersCompleted()<<std::endl;
  } else {
    std::cout<<"Student not found"<<std::endl;
  }

  if(const Student* s = d1.findStudentById("2")){
    std::cout<<d1.findStudentById("2")->getId()<<" | "<<d1.findStudentById("2")->getSemestersCompleted()<<std::endl;
  } else {
    std::cout<<"Student not found"<<std::endl;
  }

  if(const Student* s = d1.findStudentById("3")){
    std::cout<<d1.findStudentById("3")->getId()<<" | "<<d1.findStudentById("3")->getSemestersCompleted()<<std::endl;
  } else {
    std::cout<<"Student not found"<<std::endl;
  }

  return 0;
}