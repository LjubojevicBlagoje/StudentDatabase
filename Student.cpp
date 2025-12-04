#include "Student.h"

Student::Student(const std::string& id, int semestersCompleted) {
  // Initialise Student object with id and semestersCompleted
  this->id = id;
  this->semestersCompleted = semestersCompleted;
};

const std::string& Student::getId() const { return id; }

int Student::getSemestersCompleted() const { return semestersCompleted; }