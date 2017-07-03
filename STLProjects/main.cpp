#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>
#include <complex>
#include <memory>
#include <fstream>
#include <cstdio>
#include <functional>
#include <type_traits>
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

class PersonDeleter
{
public:
    void operator() (Person *p)
    {
        cout << "call delete for Person object" << endl;
        delete p;
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


template <typename T>
using uniquePtr = unique_ptr<T, void(*)(T*)>;

template <typename T>
void foo_impl(const T& val, true_type t)
{
    if (is_integral<T>())
        cout << "integral pointer!\n";
    else if (is_floating_point<T>())
        cout << "floating pointer!\n";
    else
        cout << "other pointer!\n";
}

template <typename T>
void foo_impl(const T& val, false_type f)
{
    if (is_integral<T>())
        cout << "integral!\n";
    else if (is_floating_point<T>())
        cout << "floating!\n";
    else
        cout << "other!\n";
}

template <typename T>
void foo(const T& val)
{
    foo_impl(val, is_pointer<T>());
}

template <typename T1, typename T2>
typename common_type<T1, T2>::type min(const T1& x, const T2& y)
{
    return x < y ? x : y;
}

int main()
{
    decltype(1) a;
    decltype(declval<int>()) b;
    //unique_ptr<Person, PersonDeleter> up(new Person("li"));
//     auto l = [](Person *person) { delete[] person; };
//     unique_ptr<Person[], decltype(l)> up1(new Person[2]{ Person("li"), Person("ming") }, l);
//     unique_ptr<Person[], decltype(l)> up2(move(up1));
//     unique_ptr<int, function<void(int*)>> up3(new int[10], [](int* p) {
//         delete[] p;
//     });
//     
//     uniquePtr<int> up(new int[10], [](int* p) {
//         delete[]p;
//     });
    
    //shared_ptr<Person> a(new Person[2]{ Person("m1"), Person("m2") }, default_delete<Person[]>());
   // unique_ptr<Person[]> b(new Person[2]{ Person("l1"), Person("l2") });
    
    return 0;
}