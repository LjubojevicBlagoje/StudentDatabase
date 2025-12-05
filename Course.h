#ifndef COURSE_H
#define COURSE_H

#include <iostream>

class Course {
 private:
  std::string code;  // e.g. COMP SCI 1101
  std::string name;  // e.g. Introduction to Programming
  int units;         // credit points e.g. 3 or 6

 public:
  Course(const std::string& code, const std::string& name, int units);

  const std::string& getCode() const;
  const std::string& getName() const;
  int getUnits() const;
};

#endif