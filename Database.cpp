#include "Database.h"

#include <iostream>
#include <vector>

Database::Database() {};

// ---------- Students ----------

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
      return students[i].get();  // Return pointer to the student
    }
  }
  // If no matching student is found return null pointer
  return nullptr;
}

// ---------- Courses ----------
void Database::addCourse(const Course& course) { courses.push_back(course); }

void Database::removeCourse(const std::string code) {
  // Loop through courses untill matching course code is found
  for (int i = 0; i < courses.size(); i++) {
    if (courses[i].getCode() == code) {
      courses.erase(courses.begin() + i);
    }
    std::cout << "Course does not exist"
              << std::endl;  // If such course is not found
  }
}

const Course* Database::findCourseByCode(const std::string& code) const {
  // Loop through the courses vector untill matching id is found
  for (int i = 0; i < courses.size(); i++) {
    if (courses[i].getCode() == code) {
      return &courses[i];  // Return pointer to the course
    }
  }
  // If no matching student is found return null pointer
  return nullptr;
};

// ---------- Enrollments ----------
void Database::enrollStudentInCourse(const std::string& studentId,
                                     const std::string& courseCode, int year,
                                     const std::string& term, double grade) {
  // TODO !!!
};

std::vector<Enrollment> Database::getEnrollmentsForStudent(
    const std::string& studentId) const {
  std::vector<Enrollment>
      result;  // Create a result vector to store student enrollment details
  for (int i = 0; i < enrollments.size(); i++) {
    if (enrollments[i].getStudentId() == studentId) {
      result.push_back(enrollments[i]);
    }
  }
  return result;
};

// Compute GPA
double Database::computeGpaForStudent(const std::string& studentId) const {
  double totalWeighted = 0.0;
  int totalUnits = 0;

  for (const auto& e : enrollments) {
    if (e.getStudentId() == studentId) {
      const Course* c = findCourseByCode(e.getCourseCode());
      if (!c) continue;

      totalWeighted += e.getGrade() * c->getUnits();
      totalUnits += c->getUnits();
    }
  }

  if (totalUnits == 0) return 0.0;
  return totalWeighted / totalUnits;  // 0–7 GPA
}
