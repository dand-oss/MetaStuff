#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "MovieInfo.h"

#include <iostream>

struct Person {
    // add this if you want to register private members:
    // template <>
    // auto meta::registerMembers<Person>();

    // we like to specify the compiler generated functions
    Person() = default;
    ~Person() = default;

    // copy not needed for this project
    Person(const Person& ) = delete ;
    Person& operator=(const Person& ) = delete ;

    // JSON uses move construction semantics
    Person(Person&& ) = default ;
    Person& operator=(Person&& ) = delete ;

    // constructor to set data
    explicit Person( int iage, float isalary, const std::string& iname)
       : age(iage)
       , salary(isalary)
       , name(iname) {}

    // setter/getter pairs
    void setAge(int a)
    {
        //std::cout << "Age is set by calling setter!\n";
        if (a >= 0 && a < 128) { // sorry, if you're older than 128
            age = a;
        } else {
            std::cout << "Can't set age. " << a << " is out of allowed range\n";
        }
    }

    int getAge() const {
        std::cout << "Got age with getter!\n";
        return age;
    }

    void setName(const std::string& name)
    {
        //std::cout << "Name is set by calling setter!\n";
        this->name = name;
    }

    const std::string& getName() const
    {
        std::cout << "Got name with getter!\n";
        return name;
    }

    // data
    int age { 25 };
    std::string name { "Alex" };
    float salary { 35.0f };
    std::unordered_map<std::string, std::vector<MovieInfo>> favouriteMovies;
};
