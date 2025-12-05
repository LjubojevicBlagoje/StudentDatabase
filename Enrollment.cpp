#include "Enrollment.h"

Enrollment::Enrollment(const std::string& studentId,
                       const std::string& courseCode, int year,
                       const std::string& term, double grade)
    : studentId(studentId),
      courseCode(courseCode),
      year(year),
      term(term),
      grade(grade) {}

const std::string& Enrollment::getStudentId() const { return studentId; };

const std::string& Enrollment::getCourseCode() const { return courseCode; };

int Enrollment::getYear() const { return year; };

const std::string& Enrollment::getTerm() const { return term; };

double Enrollment::getGrade() const { return grade; };

void Enrollment::setGrade(double newGrade) { grade = newGrade; };