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
#include <algorithm>
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

class C {
public:
    static void memfunc(int x, int y)
    {
        cout << x << " " << y << endl;
    }
};

#include "MyStd.h"
int main()
{
    int var_i = 0;
    add_const<int>::type const_i = var_i;
    add_lvalue_reference<int>::type lvalref_i = var_i;
    add_rvalue_reference<int>::type rvalref_i = int(0);
    add_pointer<int>::type pointer_i = &var_i;
    remove_reference<decltype(rvalref_i)>::type var_i2;
    typedef int T[1][2][3][4];
    int a = extent<T>::value;
    a = extent<T, 1>::value;
    a = extent<T, 2>::value;
    a = extent<T, 3>::value;
    vector<function<void(int, int)>> tasks;

    int m1 = 5, m2 = 3, m3 = 4, m4 = 1;
    function<bool(int*, int*)> fun = [](int* a, int* b) { return *a < *b; };
    pair<int*, int*> mm = minmax({ &m1,&m2,&m3,&m4 }, fun);
    
    MyStd::swap(m1, m2);
    return 0;
}