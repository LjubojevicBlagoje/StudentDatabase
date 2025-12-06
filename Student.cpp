#include "Student.h"

Student::Student(const std::string& id, const std::string& firstName,
                 const std::string& lastName, int semestersCompleted) {
  // Initialise Student object with id and semestersCompleted
  this->id = id;
  this->firstName = firstName;
  this->lastName = lastName;
  this->semestersCompleted = semestersCompleted;
};

const std::string& Student::getId() const { return id; }

int Student::getSemestersCompleted() const { return semestersCompleted; }

const std::string& Student::getFirstName() const { return firstName; }

const std::string& Student::getLastName() const { return lastName; }