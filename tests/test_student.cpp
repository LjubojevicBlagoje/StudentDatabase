#include "../external/catch_amalgamated.hpp"
#include "../Student.h"

TEST_CASE("Student stores basic data correctly", "[student]") {
    Student s("S1", "Alice", "Anderson", 4);

    REQUIRE(s.getId() == "S1");
    REQUIRE(s.getFirstName() == "Alice");
    REQUIRE(s.getLastName() == "Anderson");
    REQUIRE(s.getSemestersCompleted() == 4);
}
