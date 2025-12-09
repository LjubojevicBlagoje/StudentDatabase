#ifndef STUDENT_H
#define STUDENT_H

#include <string>

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
  void setSemestersCompleted(int newCount);
  int getSemestersCompleted() const;
  void setFirstName(const std::string& firstName);
  void setLastName(const std::string& lastName);
  const std::string& getFirstName() const;
  const std::string& getLastName() const;
};
#endif