#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <map>
#include <vector>
#include <string>
#include <list>
#include <array>
#include <numeric>
using namespace std;
using namespace std::placeholders;

/*
 -- Callable object
    1. function object
    2. pointer to function
    3. reference to function
    4. pointer to member function
    5. pointer to data member
*/

// 1. function object
struct FunctionObject
{
    void operator()() { cout << "FunctionObject" << endl; }
};

// 2. pointer to function
void(*PointerToFunction)(void) = []()->void { cout << "PointerToFunction" << endl; };

// 3. reference to function
auto Function(void)->void { cout << "ReferenceToFunction" << endl; }
void(&ReferenceToFunction)(void) = Function;

// 4. pointer to member function
class A
{
public:
    void MemberFunction(void) { cout << "PointerToMemFunction" << endl; }
    void(A::*PointerToMemFunction)(void);
};

// 5. pointer to data member
class B
{
public:
    B() { DataMember = "PointerToDataMember"; }
    string DataMember;
};


int main() 
{
    bind(FunctionObject())();
    bind(PointerToFunction)();
    bind(ReferenceToFunction)();
    A ptmf;
    ptmf.PointerToMemFunction = &A::MemberFunction;
    bind(ptmf.PointerToMemFunction, ptmf)();
    B ptdm;
    cout << bind(&B::DataMember, ptdm)() << endl;
    return 0;
}