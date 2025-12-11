#include "../external/catch_amalgamated.hpp"
#include "../Database.h"
#include "../Student.h"
#include "../Course.h"
#include "../Enrollment.h"

#include <memory>

TEST_CASE("GPA is computed correctly for a student", "[database][gpa]") {
    Database db;

    db.addStudent(std::make_unique<Student>("S1", "Alice", "Anderson", 4));
    db.addCourse(Course("COMP1101", "Intro to Programming", 3));
    db.addCourse(Course("COMP2101", "Data Structures", 3));

    REQUIRE(db.enrollStudentInCourse("S1", "COMP1101", 2025, "S1", 7.0));
    REQUIRE(db.enrollStudentInCourse("S1", "COMP2101", 2025, "S2", 5.0));

    double gpa = db.computeGpaForStudent("S1");
    REQUIRE(gpa == 6.0);
}

TEST_CASE("Cannot enroll if student or course does not exist", "[database][enroll]") {
    Database db;

    db.addStudent(std::make_unique<Student>("S1", "Alice", "Anderson", 4));
    db.addCourse(Course("COMP1101", "Intro to Programming", 3));

    REQUIRE_FALSE(db.enrollStudentInCourse("S9", "COMP1101", 2025, "S1", 6.0));
    REQUIRE_FALSE(db.enrollStudentInCourse("S1", "FAKE101", 2025, "S1", 6.0));
}
