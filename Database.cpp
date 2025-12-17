#include "Database.h"

#include <iostream>
#include <vector>

Database::Database() {};

// ---------- Students ----------

bool Database::addStudent(std::unique_ptr<Student> student) {
  Student* s = student.get();  // Convert to raw pointer to check if this
                               // student already exists
  if (studentExists(s->getId())) {
    // If student already exists exit here (do not add)
    return false;
  }
  students.push_back(
      std::move(student));  // add student to vector (transfer ownership)
  return true;
};

bool Database::removeStudent(const std::string& id) {
  // Loop through the students vector untill matching id is found
  for (size_t i = 0; i < students.size(); i++) {
    if (students[i]->getId() == id) {
      students.erase(students.begin() + i);  // Remove student from the vector
      // Delete enrollments associated with the student
      for (size_t j = 0; j < enrollments.size(); j++) {
        if (enrollments[j].getStudentId() == id) {
          enrollments.erase(enrollments.begin() + j);  // Remove enrollment
        }
      }
      return true;
    }
  }

  return false;  // If no matching student is found
};

const Student* Database::findStudentById(const std::string& id) const {
  // Loop through the students vector untill matching id is found
  for (size_t i = 0; i < students.size(); i++) {
    if (students[i]->getId() == id) {
      return students[i].get();  // Return pointer to the student
    }
  }
  // If no matching student is found return null pointer
  return nullptr;
}

bool Database::updateStudentName(const std::string& id,
                                 const std::string& newFirst,
                                 const std::string& newLast) {
  // Iterate through students vector untill matching ID is found
  for (size_t i = 0; i < students.size(); i++) {
    if (students[i]->getId() == id) {
      students[i]->setFirstName(newFirst);  // Apply new first name
      students[i]->setLastName(newLast);    // Apply new last name
      return true;
    }
  }
  return false;
};

bool Database::updateSemestersCompleted(const std::string& id, int newCount) {
  // iterate through students vector untill matching ID is found
  for (size_t i = 0; i < students.size(); i++) {
    if (students[i]->getId() == id) {
      students[i]->setSemestersCompleted(newCount);  // Apply new semester count
      return true;
    }
  }
  return false;
};

// ---------- Courses ----------
bool Database::addCourse(const Course& course) {
  if (courseExists(course.getCode())) {  // Check if course already exists
    return false;                        // If exists, exit (do not add)
  }
  courses.push_back(course);
  return true;
}

bool Database::removeCourse(const std::string& code) {
  // Loop through courses untill matching course code is found
  for (size_t i = 0; i < courses.size(); i++) {
    if (courses[i].getCode() == code) {
      // Check if there are students enrolled in the course
      if (numberOfStudentsEnrolled(code) > 0) {
        return false;  // Cannot remove course as there are students enrolled in
                       // it
      }
      courses.erase(courses.begin() + i);  // Remove course
      return true;
    }
  }
  return false;  // If such course is not found
};

const Course* Database::findCourseByCode(const std::string& code) const {
  // Loop through the courses vector untill matching id is found
  for (size_t i = 0; i < courses.size(); i++) {
    if (courses[i].getCode() == code) {
      return &courses[i];  // Return pointer to the course
    }
  }
  // If no matching student is found return null pointer
  return nullptr;
};

// ---------- Enrollments ----------
bool Database::enrollStudentInCourse(const std::string& studentId,
                                     const std::string& courseCode, int year,
                                     const std::string& term, double grade) {
  // Check if student exists
  const Student* student = findStudentById(studentId);
  if (!student) {
    return false;
  }

  // Check if course exists
  const Course* course = findCourseByCode(courseCode);
  if (!course) {
    return false;
  }

  // Check if student is already enrolled in this course
  if (isStudentEnrolledIn(studentId, courseCode, year, term) == 1) {
    return false;
  }

  // Add the enrollment
  enrollments.emplace_back(studentId, courseCode, year, term, grade);
  return true;
};

std::vector<Enrollment> Database::getEnrollmentsForStudent(
    const std::string& studentId) const {
  std::vector<Enrollment>
      result;  // Create a result vector to store student enrollment details
  for (size_t i = 0; i < enrollments.size(); i++) {
    if (enrollments[i].getStudentId() == studentId) {
      result.push_back(enrollments[i]);
    }
  }
  return result;
};

bool Database::dropStudentFromCourse(const std::string& studentId,
                                     const std::string& courseCode, int year,
                                     const std::string& term) {
  // Iterate through enrollments vector untill enrollment with matching criteria
  // is found, then delete the enrollment
  for (size_t i = 0; i < enrollments.size(); i++) {
    if (enrollments[i].getStudentId() == studentId &&
        enrollments[i].getCourseCode() == courseCode &&
        enrollments[i].getYear() == year && enrollments[i].getTerm() == term) {
      enrollments.erase(enrollments.begin() + i);
      return true;
    }
  }
  return false;
}

bool Database::updateGrade(const std::string& studentId,
                           const std::string& courseCode, int year,
                           const std::string& term, double newGrade) {
  // Iterate through enrollments vector untill enrollment with matching criteria
  // is found, then update grade
  for (size_t i = 0; i < enrollments.size(); i++) {
    if (enrollments[i].getStudentId() == studentId &&
        enrollments[i].getCourseCode() == courseCode &&
        enrollments[i].getYear() == year && enrollments[i].getTerm() == term) {
      enrollments[i].setGrade(newGrade);
      return true;
    }
  }
  return false;
}

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

// ---------- Helpers ----------
bool Database::studentExists(const std::string& id) const {
  // Loop through the students vector untill matching id is found
  for (size_t i = 0; i < students.size(); i++) {
    if (students[i]->getId() == id) {
      return true;  // Student already exists
    }
  }
  return false;
}

bool Database::courseExists(const std::string& code) const {
  // Iterate through courses vector untill course with matching code is found
  for (size_t i = 0; i < courses.size(); i++) {
    if (courses[i].getCode() == code) {
      return true;  // Course already exists
    }
  }
  return false;
}

int Database::numberOfStudentsEnrolled(const std::string& code) const {
  int number = 0;
  // Iterate through enrollments untill one with the desired course code is
  // found
  for (size_t i = 0; i < enrollments.size(); i++) {
    if (enrollments[i].getCourseCode() == code) {
      number++;  // Increment counter
    }
  }
  return number;
};

bool Database::isStudentEnrolledIn(const std::string& studentId,
                                   const std::string& courseCode, int year,
                                   const std::string& term) const {
  // Iterate through enrollments untill enrollment with matching criteria is
  // found
  for (size_t i = 0; i < enrollments.size(); i++) {
    if (enrollments[i].getStudentId() == studentId &&
        enrollments[i].getCourseCode() == courseCode &&
        enrollments[i].getYear() == year && enrollments[i].getTerm() == term) {
      return true;  // Student already enrolled
    }
  }
  return false;
}

// ---------- Queries/Reports ----------

// Return a vector containing all students enrolled in a specific course
std::vector<const Student*> Database::getStudentsInCourse(
    const std::string& courseCode, int year, const std::string& term) const {
  // Initialise a vector to store pointers to student objects
  std::vector<const Student*> studentsInCourse;
  // Iterate through enrollments untill course code, year, and term match
  for (size_t i = 0; i < enrollments.size(); i++) {
    if (enrollments[i].getCourseCode() == courseCode &&
        enrollments[i].getYear() == year && enrollments[i].getTerm() == term) {
      // Store ID of the enrolled student
      std::string id = enrollments[i].getStudentId();
      // Find the pointer to student with this ID and assign it to
      // enrolledStudent
      const Student* enrolledStudent = findStudentById(id);
      if (enrolledStudent != nullptr) {
        // Add enrolledStudent to the studentsInCourse vector
        studentsInCourse.push_back(enrolledStudent);
      }
    }
  }
  return studentsInCourse;
};

// Find average GPA for a course
double Database::getCourseAverage(const std::string& courseCode, int year,
                                  const std::string& term) const {
  double aggregateGrade = 0;
  int recordedGrades = 0;
  // Iterate through enrollments untill course code, year, and term match
  for (size_t i = 0; i < enrollments.size(); i++) {
    if (enrollments[i].getCourseCode() == courseCode &&
        enrollments[i].getYear() == year && enrollments[i].getTerm() == term) {
      aggregateGrade +=
          enrollments[i].getGrade();  // Add the grade value to aggregateGrade
      recordedGrades++;               // Increment count of recorded grades
    }
  }

  if (recordedGrades == 0) {  // If no grades have been recorded for this course
                              // return 0.0 to prevent undefined behaviour
    return 0.0;
  }
  return aggregateGrade /
         recordedGrades;  // Return the average grade for this course
};
