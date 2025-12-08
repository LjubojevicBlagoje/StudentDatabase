#include "Course.h"

#include <iostream>

Course::Course(const std::string& code, const std::string& name, int units)
    : code(code), name(name), units(units) {};

const std::string& Course::getCode() const { return code; };

const std::string& Course::getName() const { return name; };

int Course::getUnits() const { return units; }