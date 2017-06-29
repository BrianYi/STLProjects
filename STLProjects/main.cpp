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

namespace MyStd
{
	template<typename T1, typename T2>
	struct pair
	{
		template<typename U1, typename U2>
		pair(U1 u1, U2 u2)
		{
			first = u1;
			second = u2;
		}
		template<typename U1, typename U2>
		pair(const pair<U1, U2>& p)
		{
			*this = p;
		}
		pair(const pair& p)
		{
			*this = p;
		}
		T1 first;
		T2 second;
	};

    template <typename T1, typename T2>
    pair<T1, T2> make_pair(const T1& x, const T2& y)
    {
        return pair<T1, T2>(x, y);
    }

    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1&& x, T2&& y)
    {
        return pair<T1, T2>(x, y);
    }

    template<typename T1, typename T2>
    bool operator== (const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first == y.first && x.second == y.second;
    }

    template<typename T1, typename T2>
    bool operator< (const pair<T1, T2>& x, const pair<T1, T2>& y)
    {
        return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
    }

    template <typename... Types>
    class tuple
    {
    public:
        explicit tuple(const Types&...)
        {

        }
        template <typename... UTypes>
        explicit tuple(UTypes&&...)
        {

        }
    };
}

template <typename... Args>
void foo(const MyStd::tuple<Args...> t)
{
    
}

std::tuple<int, int, int> foo()
{
    return{ 1,2,3 };
}

// tuple_size<tupletype>::value
// tuple_element<idx, tupletype>::type
// tuple_cat()

template<int IDX, int MAX, typename... Args>
struct PRINT_TUPLE
{
    static void print(std::ostream& strm, const std::tuple<Args...>& t)
    {
        strm << std::get<IDX>(t) << (IDX+1 == MAX ? "" : ",");
        PRINT_TUPLE<IDX + 1, MAX, Args...>::print(strm, t);
    }
};

template<int MAX, typename... Args>
struct PRINT_TUPLE<MAX,MAX,Args...>
{
    static void print(std::ostream& strm, const std::tuple<Args...>& t)
    {
    }
};

template<typename... Args>
std::ostream& operator<<(std::ostream& strm, const std::tuple<Args...>& t)
{
    strm << "[";
    PRINT_TUPLE<0, sizeof...(Args), Args...>::print(strm, t);
    strm << "]";
    return strm;
}

class Person 
{
public:
    string name;
    shared_ptr<Person> mother;
    shared_ptr<Person> father;
    vector<shared_ptr<Person>> kids;

    Person(const string& n, shared_ptr<Person> m = nullptr, shared_ptr<Person> f = nullptr)
        : name(n), mother(m), father(f)
    {}

    ~Person()
    {
        cout << "delete " << name << endl;
    }
};

shared_ptr<Person> initFamily(const string& name)
{
    shared_ptr<Person> mom(new Person(name + "'s mom")); // 2
    shared_ptr<Person> dad(new Person(name + "'s dad")); // 2
    shared_ptr<Person> kid(new Person(name, mom, dad)); // 1
    mom->kids.push_back(kid); // 2
    dad->kids.push_back(kid); // 3
    return kid;
    // mom 1
    // dad 1
    // kid 2
}

int main()
{
    shared_ptr<Person> p = initFamily("nico");
    // kid 3 <==> p 3
    // mom 1
    // dad 1
    cout << "nico's family exists" << endl;
    cout << "- nico is shared " << p.use_count() << " times" << endl;
    cout << "- name of 1st kid of nico's mom: " << p->mother->kids[0]->name << endl;
    
    p = initFamily("jim");
    cout << "jim's family exists" << endl;
	return 0;
}