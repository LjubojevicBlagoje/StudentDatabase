#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {
 private:
  std::string id;
  std::string firstName;
  std::string lastName;
  int semestersCompleted;

 public:
  Student(const std::string& id, const std::string& firstName,
          const std::string& lastName, int semestersCompleted);
  const std::string& getId() const;
  int getSemestersCompleted() const;
  const std::string& getFirstName() const;
  const std::string& getLastName() const;
};
#endif