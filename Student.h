#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <iostream>
#include <string>

class Student{
    private:
    std::string id;

    public:
    Student(std::string id);
    std::string getId();
}
#endif;