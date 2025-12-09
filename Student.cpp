#include "Student.h"

Student::Student(const std::string& id, const std::string& firstName,
                 const std::string& lastName, int semestersCompleted)
    : id(id),
      firstName(firstName),
      lastName(lastName),
      semestersCompleted(semestersCompleted) {};

const std::string& Student::getId() const { return id; }

void Student::setSemestersCompleted(int newCount) {
  this->semestersCompleted = newCount;
}

int Student::getSemestersCompleted() const { return semestersCompleted; }

void Student::setFirstName(const std::string& firstName) {
  this->firstName = firstName;
};
void Student::setLastName(const std::string& lastName) {
  this->lastName = lastName;
};

const std::string& Student::getFirstName() const { return firstName; }

const std::string& Student::getLastName() const { return lastName; }