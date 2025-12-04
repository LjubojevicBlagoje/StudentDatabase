#include "Database.h"

#include <iostream>
#include <vector>

Database::Database() {
  // Initialise database and set number of students to 0
  this->numberOfStudents = 0;
};

void Database::addStudent(Student* student) { students.push_back(student); };

void Database::removeStudent(std::string id) {
  for (int i = 0; i < students.size(); i++) { // Loop through the students vector
    if (students[i]->getId() == id) { // If student at index i matches id
      delete students[i];                    // Free memory
      students.erase(students.begin() + i);  // Remove pointer from the vector
      return;
    }
  }
};