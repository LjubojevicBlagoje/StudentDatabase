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
  Student(const std::string& id, int semestersCompleted);
  const std::string& getId() const;
  int getSemestersCompleted() const;
};
#endif