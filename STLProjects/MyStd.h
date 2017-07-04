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

    template <typename T, typename D = default_delete<T>>
    class unique_ptr
    {
    public:
        typedef T element_type;
        typedef D deleter_type;
        T& operator*() const;
        T* operator->() const noexcept;
    };

    template <typename T, typename D>
    class unique_ptr<T[], D>
    {
    public:
        typedef T element_type;
        typedef D deleter_type;
        T& operator[](size_t i) const;
    };

    template <typename T>
    class default_delete 
    {
    public:
        void operator()(T* p) const
        {
            delete p;
        }
    };

    template <typename T>
    class default_delete<T[]>
    {
    public:
        void operator()(T* p) const
        {
            delete[] p;
        }
    };

    template <typename T>
    class numeric_limits
    {
    public:
        static constexpr bool is_specialized = false;
    };

    template<>
    class numeric_limits<int>
    {
    public:
        static constexpr bool is_specialized = true;

        static constexpr int min() noexcept
        {
            return -2147483647;
        }
        static constexpr int max() noexcept
        {
            return 2147483648;
        }
        static constexpr int digits = 31;
    };

//     template <typename T1, typename T2>
//     struct common_type<T1, T2>
//     {
//         typedef decltype(true ? declval<T1>() : declval<T2>()) type;
//     };

    template <typename T, T val>
    struct integral_constant
    {
        static constexpr T value = val;
        typedef T value_type;
        typedef integral_constant<T, val> type;
//         constexpr operator value_type()
//         {
//             return value;
//         }
    };
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template <typename T>
    const T& min(const T& a, const T& b)
    {
        return a < b ? a : b;
    }
    template <typename T>
    T min(initializer_list<T> initlist)
    {
        return nullptr;
    }

    template <typename T, typename Compare>
    const T& min(const T& a, const T& b, Compare cmp)
    {
        return cmp(a, b);
    }
    template <typename T, typename Compare>
    T min(initializer_list<T> initlist, Compare cmp)
    {
        return nullptr;
    }

    template <typename T>
    inline void swap(T& a, T& b)
    {
        T tmp(std::move(a));
        a = std::move(b);
        b = std::move(tmp);
    }

    template <typename T, size_t N>
    void swap(T(&a)[N], T(&b)[N]) noexcept(noexcept(swap(*a, *b)))
    {

    }
}

