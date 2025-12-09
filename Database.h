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
  bool addStudent(std::unique_ptr<Student> student);
  bool removeStudent(const std::string& id);  // Remove student with this id
  const Student* findStudentById(const std::string& id) const;
  bool updateStudentName(const std::string& id, const std::string& newFirst,
                         const std::string& newLast);
  bool updateSemestersCompleted(const std::string& id, int newCount);

  // Courses
  bool addCourse(const Course& course);
  bool removeCourse(const std::string& code);
  const Course* findCourseByCode(const std::string& code) const;

  // Enrollments
  bool enrollStudentInCourse(const std::string& studentId,
                             const std::string& courseCode, int year,
                             const std::string& term, double grade);
  std::vector<Enrollment> getEnrollmentsForStudent(
      const std::string& studentId) const;

  bool dropStudentFromCourse(const std::string& studentId,
                             const std::string& courseCode, int year,
                             const std::string& term);

  bool updateGrade(const std::string& studentId, const std::string& courseCode,
                   int year, const std::string& term, double newGrade);

  // Compute GPA
  double computeGpaForStudent(const std::string& studentId) const;

  // Helpers
  bool studentExists(const std::string& id) const;
  bool courseExists(const std::string& code) const;
  const int numberOfStudentsEnrolled(const std::string& code) const; // returns number of students enrolled in a course
  bool isStudentEnrolledIn(const std::string& studentId,
                           const std::string& courseCode, int year,
                           const std::string& term) const;

  // Queries/Reports
  std::vector<const Student*> getStudentsInCourse(
      const std::string& courseCode, int year, const std::string& term) const;

  double getCourseAverage(const std::string& courseCode, int year,
                          const std::string& term) const;
};

#endif