#include "Database.h"

#include <iostream>
#include <vector>

Database::Database() {};

void Database::addStudent(std::unique_ptr<Student> student) {
  students.push_back(
      std::move(student));  // add student to vector (transfer ownership)
};

void Database::removeStudent(const std::string& id) {
  // Loop through the students vector untill matching id is found
  for (int i = 0; i < students.size(); i++) {
    if (students[i]->getId() == id) {
      students.erase(students.begin() + i);  // Remove student from the vector
      return;
    }
  }
  std::cout << "Could not locate student"
            << std::endl;  // If no matching student is found
};

const Student* Database::findStudentById(const std::string& id) {
  // Loop through the students vector untill matching id is found
  for (int i = 0; i < students.size(); i++) {
    if (students[i]->getId() == id) {
      return students[i].get();  // Return raw pointer to the student
    }
  }
  // If no matching student is found return null pointer
  return nullptr;
}