#ifndef ENROLMENT_H
#define ENROLMENT_H

#include <iostream>
#include <string>

class Enrollment {
 private:
  std::string studentId;   // link to Student
  std::string courseCode;  // link to Course
  int year;                // e.g. 2025
  std::string term;        // e.g. "S1", "S2"
  double grade;            // 0.0–7.0

 public:
  Enrollment(const std::string& studentId, const std::string& courseCode,
             int year, const std::string& term, double grade);

  const std::string& getStudentId() const;
  const std::string& getCourseCode() const;
  int getYear() const;
  const std::string& getTerm() const;
  double getGrade() const;

  void setGrade(double newGrade);
};

#endif
