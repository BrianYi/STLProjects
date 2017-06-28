#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>
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
};

void f(MyStd::pair<int, const char*> p)
{
	return;
}

void g(MyStd::pair<const int, const char*> p)
{
	return;
}

int main()
{
	MyStd::pair<int, const char*> p(42, "hello");
	f(p);
	g(p);
	return 0;
}