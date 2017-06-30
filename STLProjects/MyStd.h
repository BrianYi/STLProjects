#pragma once

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

    template <typename T>
    class shared_ptr
    {
    public:
        typedef T element_type;
    };

    template <typename T>
    class weak_ptr
    {
    public:
        typedef T element_type;
    };
}

