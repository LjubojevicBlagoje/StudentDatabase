#include "Student.h"

Student::Student(std::string id){
    this->id = id;
};

std::string Student::getId(){
    return id;
}