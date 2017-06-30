#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>
#include <complex>
#include <memory>
#include <fstream>
#include <cstdio>
#include <fcntl.h>
using namespace std;

class Person : public std::enable_shared_from_this<Person>
{
public:
    string name;
    shared_ptr<Person> mother;
    shared_ptr<Person> father;
    vector<weak_ptr<Person>> kids;

    Person() : name("") {}

    Person(const string& n, shared_ptr<Person> m = nullptr, shared_ptr<Person> f = nullptr)
        : name(n), mother(m), father(f)
    {}

    ~Person()
    {
        cout << "delete " << name << endl;
    }

    void SetParentAndTheirKids(shared_ptr<Person> m = nullptr, shared_ptr<Person> f = nullptr)
    {
        mother = m;
        father = f;
        if (m != nullptr) 
        {
            m->kids.push_back(shared_from_this());
        }
        if (f != nullptr) 
        {
            f->kids.push_back(shared_from_this());
        }
    }
};

shared_ptr<Person> initFamily(const string& name)
{
    shared_ptr<Person> mom(new Person(name + "'s mom")); // 2
    shared_ptr<Person> dad(new Person(name + "'s dad")); // 2
    shared_ptr<Person> kid(new Person(name)); // 1
    kid->SetParentAndTheirKids(mom, dad);
    return kid;
}

// use for delete object automatically
void sink(unique_ptr<Person> up)
{

}

// use for generate object automatically
unique_ptr<Person> source()
{
    unique_ptr<Person> ptr(new Person());
    return ptr;
}

int main()
{
    unique_ptr<Person> up;
    up = source();

    unique_ptr<Person> up1(new Person("UP1"));
    unique_ptr<Person> up2(new Person("UP2"));
    sink(move(up1));
    return 0;
}