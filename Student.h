#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>

class Student {
 private:
  std::string id;
  int semestersCompleted;

 public:
  Student(std::string id, int semestersCompleted); 
  std::string getId();
  int getSemestersCompleted();
};
#endif