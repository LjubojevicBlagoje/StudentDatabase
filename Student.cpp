#include "Student.h"

Student::Student(std::string id, int semestersCompleted) {
    // Initialise Student object with id and semestersCompleted
  this->id = id;
  this->semestersCompleted = semestersCompleted;
};

std::string Student::getId() { return id; }

int Student::getSemestersCompleted() { return semestersCompleted; }