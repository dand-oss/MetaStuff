
// example class
#include "PersonMeta.h"

#include <json.hpp> // supplied header lib
#include "JsonCast.h"

#include <iostream>

class Unregistered
{ };

void printSeparator()
{
    std::cout << "========================\n";
}

extern int main( int, char*[] )
{
    Person person;

    // set some data
    person.age = 35;
    person.salary = 4.50f;
    person.name = "Fred"; // I'm a person!

    person.favouriteMovies["Nostalgia Critic"] = { MovieInfo{ "The Room", 8.5f } };
    person.favouriteMovies["John Tron"] = { MovieInfo{ "Goosebumps", 10.0f },
        MovieInfo{ "Talking Cat", 9.0f } };

    // printing members of different classes
    std::cout << "Members of class Person:\n";
    meta::doForAllMembers<Person>(
        [](const auto& member)
    {
        std::cout << "* " << member.getName() << '\n';
    }
    );

    std::cout << "Members of class MovieInfo:\n";
    meta::doForAllMembers<MovieInfo>(
        [](const auto& member)
    {
        std::cout << "* " << member.getName() << '\n';
    }
    );

    printSeparator();

    // checking if classes are registered
    if (meta::isRegistered<Person>()) {
        std::cout << "Person class is registered\n";
		std::cout << "It has " << meta::getMemberCount<Person>() << " members registered.\n";
    }

    // meta::isRegistered is constexpr, so can be used in enable_if and static_assert!
    static_assert(meta::isRegistered<Person>(), "Person class is not registered!");
	static_assert(meta::getMemberCount<Person>() == 4, "Person does not have 4 members registered?");

    if (!meta::isRegistered<Unregistered>()) {
        std::cout << "Unregistered class is unregistered\n";
		std::cout << "It has " << meta::getMemberCount<Unregistered>() << " members registered.\n";
    }

    // checking if class has a member
    if (meta::hasMember<Person>("age")) {
        std::cout << "Person has member named 'age'\n";
    }

    // getting setting member values
    auto name = meta::getMemberValue<std::string>(person, "name");
    std::cout << "Got person's name: " << name << '\n';

    meta::setMemberValue<std::string>(person, "name", "Ron Burgundy");
    name = meta::getMemberValue<std::string>(person, "name");
    std::cout << "Changed person's name to " << name << '\n';

    printSeparator();

    // And here's how you can serialize/deserialize
    // (if you write a function for your type)
    std::cout << "Serializing person:" << '\n';
    json root = person;
    std::cout << std::setw(4) << root << std::endl;

    //Unregistered y;
    //json root2 = y; // this will fail at compile time

    printSeparator();

    std::cout << "Serializing Person 2 from JSON:\n";

    auto person2 = root.get<Person>();
    std::cout << "Person 2 name is " << person2.getName() << " too!" << '\n';

#ifdef _WIN32 // okay, this is not cool code, sorry :D
    system("pause");
#endif
}
