#include <iostream>
#include <memory>  // for std::make_unique

#include "Course.h"
#include "Database.h"
#include "Enrollment.h"
#include "Student.h"

void printStudent(Database& db, const std::string& id) {
  const Student* s = db.findStudentById(id);
  if (s) {
    std::cout << "Student ID: " << s->getId()
              << " | Full name: " << s->getFirstName() << " "
              << s->getLastName()
              << " | Semesters completed: " << s->getSemestersCompleted()
              << std::endl;
  } else {
    std::cout << "Student with id " << id << " not found\n";
  }
}

void printEnrollmentsForStudent(Database& db, const std::string& studentId) {
  std::cout << "\nEnrollments for student " << studentId << ":\n";

  auto enrollments = db.getEnrollmentsForStudent(studentId);
  if (enrollments.empty()) {
    std::cout << "  (none)\n";
    return;
  }

  for (const auto& e : enrollments) {
    std::cout << "  Course: " << e.getCourseCode() << " | Year: " << e.getYear()
              << " | Term: " << e.getTerm() << " | Grade: " << e.getGrade()
              << std::endl;
  }
}

void printGpaForStudent(Database& db, const std::string& studentId) {
  double gpa = db.computeGpaForStudent(studentId);
  std::cout << "GPA for student " << studentId << " = " << gpa
            << " (0–7 scale)\n";
}

int main() {
  Database db;  // Initialise database

  // ---------- Students ----------
  std::cout << "=== Adding students ===\n";
  db.addStudent(
      std::make_unique<Student>("1", "Anthony", "Smith", 6));  // 6 semesters
  db.addStudent(
      std::make_unique<Student>("2", "Bob", "Lowe", 2));  // 2 semesters
  db.addStudent(
      std::make_unique<Student>("3", "Charlie", "Cole", 1));  // 1 semester

  std::cout << "\nAll students after insertion:\n";
  printStudent(db, "1");
  printStudent(db, "2");
  printStudent(db, "3");

  std::cout << "\n=== Removing student 3 ===\n";
  db.removeStudent("3");

  std::cout << "Students after removal:\n";
  printStudent(db, "1");
  printStudent(db, "2");
  printStudent(db, "3");  // should now be "not found"

  // ---------- Courses ----------
  std::cout << "\n=== Adding courses ===\n";
  db.addCourse(Course("COMP1101", "Intro to Programming", 3));
  db.addCourse(Course("COMP2101", "Data Structures", 3));
  db.addCourse(Course("MATH1001", "Calculus I", 3));

  // Try finding a course
  if (const Course* c = db.findCourseByCode("COMP1101")) {
    std::cout << "Found course: " << c->getCode() << " - " << c->getName()
              << " (" << c->getUnits() << " units)\n";
  } else {
    std::cout << "Course COMP1101 not found\n";
  }

  // ---------- Enrollments & Grades ----------
  std::cout << "\n=== Enrolling students in courses ===\n";

  // Valid enrollments
  db.enrollStudentInCourse("1", "COMP1101", 2025, "S1",
                           6.0);  // Distinction-ish
  db.enrollStudentInCourse("1", "COMP2101", 2025, "S2", 5.0);
  db.enrollStudentInCourse("2", "COMP1101", 2025, "S1", 4.0);
  db.enrollStudentInCourse("2", "MATH1001", 2025, "S1", 3.0);

  // Invalid enrollments (to test error handling)
  db.enrollStudentInCourse("999", "COMP1101", 2025, "S1", 6.0);  // bad student
  db.enrollStudentInCourse("1", "FAKE101", 2025, "S1", 6.0);     // bad course

  // ---------- Show enrollments ----------
  printEnrollmentsForStudent(db, "1");
  printEnrollmentsForStudent(db, "2");
  printEnrollmentsForStudent(db,
                             "3");  // removed student, but may still have none

  // ---------- GPA ----------
  std::cout << "\n=== GPA computation ===\n";
  printGpaForStudent(db, "1");
  printGpaForStudent(db, "2");
  printGpaForStudent(db, "3");  // no enrollments => GPA 0.0

  return 0;
}
