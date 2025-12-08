#ifndef DATABASE_H
#define DATABASE_H

#include <memory>
#include <vector>

#include "Course.h"
#include "Enrollment.h"
#include "Student.h"

class Database {
 private:
  // Initialise a vector of students (smart pointers)
  std::vector<std::unique_ptr<Student>> students;
  // Initialise vectors of courses and enrollments
  std::vector<Course> courses;
  std::vector<Enrollment> enrollments;

 public:
  Database();  // Initialise

  // Students
  void addStudent(std::unique_ptr<Student> student);
  bool removeStudent(const std::string& id);  // Remove student with this id
  const Student* findStudentById(const std::string& id);

  // Courses
  void addCourse(const Course& course);
  bool removeCourse(const std::string code);
  const Course* findCourseByCode(const std::string& code) const;

  // Enrollments
  bool enrollStudentInCourse(const std::string& studentId,
                             const std::string& courseCode, int year,
                             const std::string& term, double grade);
  std::vector<Enrollment> getEnrollmentsForStudent(
      const std::string& studentId) const;

  // Compute GPA
  double computeGpaForStudent(const std::string& studentId) const;
};

#endif