#include <iostream>
#include <memory>  // for std::make_unique
#include <iomanip> // for std::boolalpha

#include "Database.h"
#include "Student.h"
#include "Course.h"
#include "Enrollment.h"

void section(const std::string& title) {
    std::cout << "\n================== " << title << " ==================\n";
}

void testStudentLookup(Database& db, const std::string& id, const std::string& expectedName) {
    std::cout << "Test: findStudentById(\"" << id << "\")\n";
    std::cout << "  EXPECT: " << (expectedName.empty() ? "nullptr (not found)" 
                                                     : "student with name " + expectedName)
              << "\n";

    const Student* s = db.findStudentById(id);
    if (s) {
        std::cout << "  ACTUAL: found " << s->getFirstName() << " " << s->getLastName()
                  << " (id=" << s->getId() << ")\n";
    } else {
        std::cout << "  ACTUAL: nullptr (not found)\n";
    }
}

void printEnrollmentsForStudent(Database& db, const std::string& studentId) {
    std::cout << "Test: getEnrollmentsForStudent(\"" << studentId << "\")\n";
    auto enrollments = db.getEnrollmentsForStudent(studentId);

    if (enrollments.empty()) {
        std::cout << "  EXPECT/ACTUAL: (none)\n";
        return;
    }

    std::cout << "  EXPECT: list of enrollments for student " << studentId << "\n";
    std::cout << "  ACTUAL:\n";
    for (const auto& e : enrollments) {
        std::cout << "    Course: " << e.getCourseCode()
                  << " | Year: " << e.getYear()
                  << " | Term: " << e.getTerm()
                  << " | Grade: " << e.getGrade() << "\n";
    }
}

void printGpaForStudent(Database& db, const std::string& studentId, double expectedApprox) {
    std::cout << "Test: computeGpaForStudent(\"" << studentId << "\")\n";
    std::cout << "  EXPECT: approximately " << expectedApprox << " on 0–7 scale\n";
    double gpa = db.computeGpaForStudent(studentId);
    std::cout << "  ACTUAL: " << gpa << "\n";
}

void printStudentsInCourse(Database& db,
                           const std::string& courseCode,
                           int year,
                           const std::string& term,
                           const std::string& expectedDesc) {
    std::cout << "Test: getStudentsInCourse(\"" << courseCode << "\", "
              << year << ", \"" << term << "\")\n";
    std::cout << "  EXPECT: " << expectedDesc << "\n";

    auto students = db.getStudentsInCourse(courseCode, year, term);
    if (students.empty()) {
        std::cout << "  ACTUAL: (none)\n";
        return;
    }

    std::cout << "  ACTUAL:\n";
    for (const Student* s : students) {
        if (s) {
            std::cout << "    " << s->getId() << " - "
                      << s->getFirstName() << " " << s->getLastName() << "\n";
        } else {
            std::cout << "    nullptr student pointer (!)\n";
        }
    }
}

int main() {
    std::cout << std::boolalpha; // print bools as true/false instead of 1/0
    std::cout << "===== Student Database Test Harness =====\n";

    Database db;

    // ------------------------------------------------------------
    // 1. Students
    // ------------------------------------------------------------
    section("STUDENTS: add, find, exists, remove");

    std::cout << "Adding students S1, S2, S3\n";
    db.addStudent(std::make_unique<Student>("S1", "Alice", "Anderson", 4));
    db.addStudent(std::make_unique<Student>("S2", "Bob", "Brown", 2));
    db.addStudent(std::make_unique<Student>("S3", "Charlie", "Clark", 1));

    std::cout << "Test: studentExists(\"S1\")\n";
    std::cout << "  EXPECT: true\n";
    std::cout << "  ACTUAL: " << db.studentExists("S1") << "\n\n";

    std::cout << "Test: studentExists(\"S9\")\n";
    std::cout << "  EXPECT: false\n";
    std::cout << "  ACTUAL: " << db.studentExists("S9") << "\n\n";

    testStudentLookup(db, "S1", "Alice Anderson");
    testStudentLookup(db, "S3", "Charlie Clark");
    testStudentLookup(db, "S9", ""); // expect null

    std::cout << "\nRemoving student S3\n";
    std::cout << "  EXPECT: removeStudent(\"S3\") returns true\n";
    std::cout << "  ACTUAL: " << db.removeStudent("S3") << "\n";
    testStudentLookup(db, "S3", ""); // expect nullptr now

    // ------------------------------------------------------------
    // 2. Courses
    // ------------------------------------------------------------
    section("COURSES: add, find, exists, remove");

    std::cout << "Adding courses COMP1101, COMP2101, MATH1001\n";
    db.addCourse(Course("COMP1101", "Intro to Programming", 3));
    db.addCourse(Course("COMP2101", "Data Structures", 3));
    db.addCourse(Course("MATH1001", "Calculus I", 3));

    std::cout << "Test: courseExists(\"COMP1101\")\n";
    std::cout << "  EXPECT: true\n";
    std::cout << "  ACTUAL: " << db.courseExists("COMP1101") << "\n\n";

    std::cout << "Test: courseExists(\"FAKE101\")\n";
    std::cout << "  EXPECT: false\n";
    std::cout << "  ACTUAL: " << db.courseExists("FAKE101") << "\n\n";

    std::cout << "Test: findCourseByCode(\"COMP1101\")\n";
    const Course* c = db.findCourseByCode("COMP1101");
    std::cout << "  EXPECT: non-null, code COMP1101\n";
    if (c) {
        std::cout << "  ACTUAL: " << c->getCode() << " - " << c->getName()
                  << " (" << c->getUnits() << " units)\n";
    } else {
        std::cout << "  ACTUAL: nullptr\n";
    }

    std::cout << "\nRemoving course MATH1001\n";
    std::cout << "  EXPECT: removeCourse(\"MATH1001\") returns true\n";
    std::cout << "  ACTUAL: " << db.removeCourse("MATH1001") << "\n";

    std::cout << "Test: courseExists(\"MATH1001\") after removal\n";
    std::cout << "  EXPECT: false\n";
    std::cout << "  ACTUAL: " << db.courseExists("MATH1001") << "\n";

    // ------------------------------------------------------------
    // 3. Enrollments & helpers
    // ------------------------------------------------------------
    section("ENROLLMENTS: enroll, isStudentEnrolledIn, drop, updateGrade");

    std::cout << "Enrolling S1 in COMP1101 (2025 S1) with grade 6.0\n";
    std::cout << "  EXPECT: true\n";
    std::cout << "  ACTUAL: " << db.enrollStudentInCourse("S1", "COMP1101", 2025, "S1", 6.0) << "\n";

    std::cout << "Enrolling S1 in COMP2101 (2025 S2) with grade 5.0\n";
    std::cout << "  EXPECT: true\n";
    std::cout << "  ACTUAL: " << db.enrollStudentInCourse("S1", "COMP2101", 2025, "S2", 5.0) << "\n";

    std::cout << "Enrolling S2 in COMP1101 (2025 S1) with grade 4.0\n";
    std::cout << "  EXPECT: true\n";
    std::cout << "  ACTUAL: " << db.enrollStudentInCourse("S2", "COMP1101", 2025, "S1", 4.0) << "\n";

    std::cout << "\nTrying to enroll unknown student S9 in COMP1101 (should fail)\n";
    std::cout << "  EXPECT: false\n";
    std::cout << "  ACTUAL: " << db.enrollStudentInCourse("S9", "COMP1101", 2025, "S1", 6.0) << "\n";

    std::cout << "Trying to enroll S1 in unknown course FAKE101 (should fail)\n";
    std::cout << "  EXPECT: false\n";
    std::cout << "  ACTUAL: " << db.enrollStudentInCourse("S1", "FAKE101", 2025, "S1", 6.0) << "\n\n";

    std::cout << "Test: isStudentEnrolledIn(\"S1\", \"COMP1101\", 2025, \"S1\")\n";
    std::cout << "  EXPECT: true\n";
    std::cout << "  ACTUAL: " << db.isStudentEnrolledIn("S1", "COMP1101", 2025, "S1") << "\n\n";

    std::cout << "Test: isStudentEnrolledIn(\"S1\", \"COMP1101\", 2025, \"S2\")\n";
    std::cout << "  EXPECT: false\n";
    std::cout << "  ACTUAL: " << db.isStudentEnrolledIn("S1", "COMP1101", 2025, "S2") << "\n\n";

    printEnrollmentsForStudent(db, "S1");
    printEnrollmentsForStudent(db, "S2");
    printEnrollmentsForStudent(db, "S3"); // removed earlier; should have none

    std::cout << "\nUpdating grade: S1 in COMP1101 2025 S1 from 6.0 to 7.0\n";
    std::cout << "  EXPECT: true\n";
    std::cout << "  ACTUAL: " << db.updateGrade("S1", "COMP1101", 2025, "S1", 7.0) << "\n";
    printEnrollmentsForStudent(db, "S1");

    std::cout << "\nDropping S2 from COMP1101 2025 S1\n";
    std::cout << "  EXPECT: true\n";
    std::cout << "  ACTUAL: " << db.dropStudentFromCourse("S2", "COMP1101", 2025, "S1") << "\n";
    printEnrollmentsForStudent(db, "S2");

    // ------------------------------------------------------------
    // 4. Reports: GPA, students in course, course average
    // ------------------------------------------------------------
    section("REPORTS: GPA, students in a course, course average");

    // GPA for S1:
    // S1 has:
    //   COMP1101: grade 7.0, units 3
    //   COMP2101: grade 5.0, units 3
    // Weighted: (7*3 + 5*3) / 6 = 6.0
    printGpaForStudent(db, "S1", 6.0);

    // GPA for S2: now dropped from COMP1101, so no enrollments -> 0.0
    printGpaForStudent(db, "S2", 0.0);

    // GPA for S3: was removed before enrolling -> 0.0
    printGpaForStudent(db, "S3", 0.0);

    // Students in COMP1101 2025 S1: only S1 left
    printStudentsInCourse(db, "COMP1101", 2025, "S1",
                          "one student: S1 (Alice Anderson)");

    // Course average for COMP1101 2025 S1:
    // Only S1 remains with grade 7.0 -> average should be 7.0
    std::cout << "\nTest: getCourseAverage(\"COMP1101\", 2025, \"S1\")\n";
    std::cout << "  EXPECT: 7.0 (since only S1 with grade 7.0 is enrolled)\n";
    double avg = db.getCourseAverage("COMP1101", 2025, "S1");
    std::cout << "  ACTUAL: " << avg << "\n";

    std::cout << "\n===== End of tests =====\n";
    return 0;
}
