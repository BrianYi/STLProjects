#include <iostream>
using namespace std;

template <class Iterator, class T>
Iterator find(Iterator first, Iterator last, const T& value)
{
    while (first != last && *first != value)
        ++first;
    return first;
}

struct int_node
{
    int val;
    int_node* next;
};

template <class Node>
struct node_wrap
{
    typedef Node value_type;
    Node*   ptr;
    node_wrap(Node* p = 0) : ptr(p) {}
    Node& operator*() const { return *ptr; }
    Node* operator->() const { return ptr; }
    
    node_wrap& operator++() { ptr = ptr->next; return *this; }
    node_wrap operator++(int) { node_wrap tmp = *this; ++*this; return tmp; }

    bool operator==(const node_wrap& i) const { return ptr == i.ptr; }
    bool operator!=(const node_wrap& i) const { return ptr != i.ptr; }
};

int_node* CreateLinkList()
{
    int_node *head = new int_node;
    int_node *p = head;
    int_node *s = nullptr;
    int c;
    while (cin >> c, c != -1)
    {
        s = new int_node;
        s->val = c;
        s->next = nullptr;
        p->next = s;
        p = p->next;
    }
    return head;
}

template <class Iterator>
void printLinkList(Iterator head)
{
    Iterator start = ++head;
    while (start != nullptr)
    {
        cout << start->val << " ";
        start++;
    }
    cout << endl;
}

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

template <class T> class ostream_iterator
{
private:
    ostream* os;
    const char* string;
public:
    ostream_iterator(ostream& s, const char* c = 0) :os(&s), string(c) {}
    ostream_iterator(const ostream_iterator& i) :os(i.os), string(i.string) {}
    ostream_iterator& operator=(const ostream_iterator& i)
    {
        os = i.os;
        string = i.string;
        return *this;
    }
    ostream_iterator<T>& operator=(const T& value)
    {
        *os << value;
        if (string) *os << string;
        return *this;
    }

    ostream_iterator<T>& operator*() { return *this; }
    ostream_iterator<T>& operator++() { return *this; }
    ostream_iterator<T>& operator++(int) { return *this; }
};

template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
{
    for (; first != last; ++first)
        if (*first == old_value)
            *first = new_value;
}

template <class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
{
    if (first == last)
        return last;
    ForwardIterator next = first;
    while (++next != last)
    {
        if (*first == *next)
            return first;
        first = next;
    }
    return last;
}

template <class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result)
{
    while (first != last)
    {
        --last;
        *result = *last;
        ++result;
    }
    return result;
}

struct Iterator
{ 
    // operator*()
    // operator++()
};

struct InputIterator : public Iterator
{ 
    // operator!=()
    // operator->()
    // operator++(int)
};

struct OutputIterator : public Iterator
{ 
    // operator=()
    // operator++(int)
};

struct ForwardIterator : public InputIterator
{ 

};

struct BidirectionalIterator : public ForwardIterator
{
    // operator--()
    // operator--(int)
};

struct RandomAccessIterator : public BidirectionalIterator
{
    // operator+=()
    // operator-=()
    // operator+()
    // operator-()
    // operator[](int)
    // operator<()
    // operator>()
    // operator<=()
    // operator>=()
};

template <class Iterator>
struct _iterator_traits
{
    typedef typename Iterator::iterator_category    _iterator_category;
    typedef typename Iterator::value_type           _value_type;
    typedef typename Iterator::difference_type      _difference_type;
    typedef typename Iterator::pointer              _pointer;
    typedef typename Iterator::reference            _reference;
};

template <class T>
struct _iterator_traits<T*>
{
    typedef random_access_iterator_tag  _iterator_category;
    typedef T                           _value_type;
    typedef ptrdiff_t                   _difference_type;
    typedef T*                          _pointer;
    typedef T&                          _reference;
};

template <class T>
struct _iterator_traits<const T*>
{
    typedef random_access_iterator_tag  _iterator_category;
    typedef T                           _value_type;
    typedef ptrdiff_t                   _difference_type;
    typedef const T*                    _pointer;
    typedef const T&                    _reference;
};

template <class InputIterator>
typename iterator_traits<InputIterator>::value_type 
sum_nonempty(InputIterator first, InputIterator last)
{
    typename iterator_traits<InputIterator>::value_type result = *first++;
    for (; first != last; ++first)
        result += *first;
    return result;
}

template <class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& x)
{
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for (; first != last; ++first)
        ++n;
    return n;
}

struct _input_iterator_tag {};
struct _output_iterator_tag {};
struct _forward_iterator_tag:public _input_iterator_tag {};
struct _bidirectional_iterator_tag:public _forward_iterator_tag {};
struct _random_access_iterator_tag:public _bidirectional_iterator_tag {};

template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n, _input_iterator_tag)
{
    for (; n > 0; --n, ++i) {}
}

template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n, _forward_iterator_tag)
{
    advance(i, n, input_iterator_tag());
}

template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n, _bidirectional_iterator_tag)
{
    if (n >= 0)
        for (; n > 0; --n, ++i) {}
    else
        for (; n < 0; ++n, --i) {}
}

template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n, _random_access_iterator_tag)
{
    i += n;
}

template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n)
{
    advance(i, n, typename iterator_traits<i>::iterator_category());
}

int main() 
{
    int *a = new int(2);

//     int_node* head = CreateLinkList();
//     node_wrap<int_node> iter(head);
//     printLinkList(iter);
}