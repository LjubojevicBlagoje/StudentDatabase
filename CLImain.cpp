#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "Course.h"
#include "Database.h"
#include "Enrollment.h"
#include "Student.h"

// ---------- Input helpers ----------
int readInt(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    int value;
    if (std::cin >> value) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return value;
    }
    std::cout << "Invalid integer. Try again.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

double readDouble(const std::string& prompt, double minVal, double maxVal) {
  while (true) {
    std::cout << prompt;
    double value;
    if (std::cin >> value) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (value >= minVal && value <= maxVal) return value;
      std::cout << "Value must be in [" << minVal << ", " << maxVal
                << "]. Try again.\n";
    } else {
      std::cout << "Invalid number. Try again.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

std::string readLine(const std::string& prompt) {
  std::cout << prompt;
  std::string s;
  std::getline(std::cin, s);
  return s;
}

// ---------- UI helpers ----------
void printMenu() {
  std::cout << "\n========== Student Database (CLI) ==========\n"
            << "1) Add student\n"
            << "2) Remove student\n"
            << "3) Find student\n"
            << "4) Add course\n"
            << "5) Remove course\n"
            << "6) Find course\n"
            << "7) Enroll student in course\n"
            << "8) Drop student from course\n"
            << "9) Update grade\n"
            << "10) Show student's enrollments\n"
            << "11) Compute student GPA\n"
            << "12) List students in a course offering\n"
            << "13) Course average for offering\n"
            << "0) Exit\n"
            << "-------------------------------------------\n";
}

void printStudent(const Student* s) {
  if (!s) {
    std::cout << "Student not found.\n";
    return;
  }
  std::cout << "ID: " << s->getId() << " | Name: " << s->getFirstName() << " "
            << s->getLastName()
            << " | Semesters: " << s->getSemestersCompleted() << "\n";
}

void printCourse(const Course* c) {
  if (!c) {
    std::cout << "Course not found.\n";
    return;
  }
  std::cout << "Code: " << c->getCode() << " | Name: " << c->getName()
            << " | Units: " << c->getUnits() << "\n";
}

// ---------- Actions ----------
void actionAddStudent(Database& db) {
  std::cout << "\n[Add student]\n";
  std::string id = readLine("Student ID: ");
  std::string first = readLine("First name: ");
  std::string last = readLine("Last name: ");
  int semesters = readInt("Semesters completed: ");

  bool ok =
      db.addStudent(std::make_unique<Student>(id, first, last, semesters));
  std::cout << (ok ? "Student added.\n"
                   : "Failed: student ID already exists.\n");
}

void actionRemoveStudent(Database& db) {
  std::cout << "\n[Remove student]\n";
  std::string id = readLine("Student ID: ");
  bool ok = db.removeStudent(id);
  std::cout << (ok ? "Student removed.\n" : "Failed: student not found.\n");
}

void actionFindStudent(Database& db) {
  std::cout << "\n[Find student]\n";
  std::string id = readLine("Student ID: ");
  const Student* s = db.findStudentById(id);
  printStudent(s);
}

void actionAddCourse(Database& db) {
  std::cout << "\n[Add course]\n";
  std::string code = readLine("Course code: ");
  std::string name = readLine("Course name: ");
  int units = readInt("Units: ");

  bool ok = db.addCourse(Course(code, name, units));
  std::cout << (ok ? "Course added.\n"
                   : "Failed: course code already exists.\n");
}

void actionRemoveCourse(Database& db) {
  std::cout << "\n[Remove course]\n";
  std::string code = readLine("Course code: ");
  bool ok = db.removeCourse(code);
  std::cout << (ok ? "Course removed.\n"
                   : "Failed: course not found OR students still enrolled.\n");
}

void actionFindCourse(Database& db) {
  std::cout << "\n[Find course]\n";
  std::string code = readLine("Course code: ");
  const Course* c = db.findCourseByCode(code);
  printCourse(c);
}

void actionEnroll(Database& db) {
  std::cout << "\n[Enroll student in course]\n";
  std::string studentId = readLine("Student ID: ");
  std::string courseCode = readLine("Course code: ");
  int year = readInt("Year (e.g. 2025): ");
  std::string term = readLine("Term (e.g. S1, S2): ");
  double grade = readDouble("Grade (0.0 to 7.0): ", 0.0, 7.0);

  bool ok = db.enrollStudentInCourse(studentId, courseCode, year, term, grade);
  std::cout << (ok ? "Enrollment recorded.\n"
                   : "Failed: missing student/course OR already enrolled.\n");
}

void actionDrop(Database& db) {
  std::cout << "\n[Drop student from course]\n";
  std::string studentId = readLine("Student ID: ");
  std::string courseCode = readLine("Course code: ");
  int year = readInt("Year: ");
  std::string term = readLine("Term: ");

  bool ok = db.dropStudentFromCourse(studentId, courseCode, year, term);
  std::cout << (ok ? "Dropped.\n" : "Failed: enrollment not found.\n");
}

void actionUpdateGrade(Database& db) {
  std::cout << "\n[Update grade]\n";
  std::string studentId = readLine("Student ID: ");
  std::string courseCode = readLine("Course code: ");
  int year = readInt("Year: ");
  std::string term = readLine("Term: ");
  double grade = readDouble("New grade (0.0 to 7.0): ", 0.0, 7.0);

  bool ok = db.updateGrade(studentId, courseCode, year, term, grade);
  std::cout << (ok ? "Grade updated.\n" : "Failed: enrollment not found.\n");
}

void actionShowEnrollments(Database& db) {
  std::cout << "\n[Show student enrollments]\n";
  std::string studentId = readLine("Student ID: ");

  auto list = db.getEnrollmentsForStudent(studentId);
  if (list.empty()) {
    std::cout << "(No enrollments found for this student.)\n";
    return;
  }

  for (const auto& e : list) {
    std::cout << "Course: " << e.getCourseCode() << " | Year: " << e.getYear()
              << " | Term: " << e.getTerm() << " | Grade: " << e.getGrade()
              << "\n";
  }
}

void actionComputeGpa(Database& db) {
  std::cout << "\n[Compute student GPA]\n";
  std::string studentId = readLine("Student ID: ");
  double gpa = db.computeGpaForStudent(studentId);
  std::cout << "GPA for " << studentId << " = " << gpa << " (0–7 scale)\n";
}

void actionStudentsInCourse(Database& db) {
  std::cout << "\n[List students in a course offering]\n";
  std::string courseCode = readLine("Course code: ");
  int year = readInt("Year: ");
  std::string term = readLine("Term: ");

  auto students = db.getStudentsInCourse(courseCode, year, term);
  if (students.empty()) {
    std::cout << "(No students found for this offering.)\n";
    return;
  }

  for (const Student* s : students) {
    if (s) {
      std::cout << s->getId() << " - " << s->getFirstName() << " "
                << s->getLastName() << "\n";
    }
  }
}

void actionCourseAverage(Database& db) {
  std::cout << "\n[Course average]\n";
  std::string courseCode = readLine("Course code: ");
  int year = readInt("Year: ");
  std::string term = readLine("Term: ");

  double avg = db.getCourseAverage(courseCode, year, term);
  std::cout << "Average grade for " << courseCode << " (" << year << " " << term
            << ") = " << avg << "\n";
}

int main() {
  Database db("studentdb.sqlite");

  while (true) {
    printMenu();
    int choice = readInt("Choose an option: ");

    switch (choice) {
      case 1:
        actionAddStudent(db);
        break;
      case 2:
        actionRemoveStudent(db);
        break;
      case 3:
        actionFindStudent(db);
        break;
      case 4:
        actionAddCourse(db);
        break;
      case 5:
        actionRemoveCourse(db);
        break;
      case 6:
        actionFindCourse(db);
        break;
      case 7:
        actionEnroll(db);
        break;
      case 8:
        actionDrop(db);
        break;
      case 9:
        actionUpdateGrade(db);
        break;
      case 10:
        actionShowEnrollments(db);
        break;
      case 11:
        actionComputeGpa(db);
        break;
      case 12:
        actionStudentsInCourse(db);
        break;
      case 13:
        actionCourseAverage(db);
        break;
      case 0:
        std::cout << "Goodbye!\n";
        return 0;
      default:
        std::cout << "Unknown option. Try again.\n";
        break;
    }
  }
}
