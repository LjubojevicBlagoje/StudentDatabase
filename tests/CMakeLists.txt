file(GLOB TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(db_tests
    ${TEST_SOURCES}
    ${PROJECT_SOURCE_DIR}/external/catch_amalgamated.cpp
)

target_link_libraries(db_tests studentdb)
