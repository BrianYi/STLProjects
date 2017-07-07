#include <iostream>
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
#include <ratio>
#include <chrono>
#include <iomanip>
#include <list>
#include <forward_list>
#include <array>
#include <vector>
#include <map>
#include <set>
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

template <typename C>
void printClockData()
{
    using namespace std;
    cout << "- precision: ";

    //typedef typename C::period P;
    if (ratio_less_equal<typename C::period,milli>::value)
    {
        typedef typename ratio_multiply<typename C::period, kilo>::type TT;
        cout << fixed << double(TT::num) / TT::den << " milliseconds" << endl;
    }
    else 
    {
        cout << fixed << double(C::period::num) / C::period::den << " seconds" << endl;
    }
    cout << "- is_steady: " << boolalpha << C::is_steady << endl;
}

template <typename T, unsigned N>
int maxVal(const T (&a)[N])
{
    cout << N << endl;
    return 0;
}


int main()
{
    multimap<int, string> coll;
    coll = {
        {5,"tagged"}, {2,"a"}, {1, "this"}, {4, "of"}, {6, "strings"}, {1, "is"}, {3, "multimap"}
    };
    
    for (const auto &elem : coll) 
    {
        cout << elem.first << " : " << elem.second << endl;
    }
    cout << endl;
    return 0;
}