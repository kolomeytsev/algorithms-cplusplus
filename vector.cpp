#include <iostream>
#include <fstream>

namespace my {
    template <class T>
    class vector;
}

template <class T> 
class my::vector {
    char* storage;
    unsigned size;
    unsigned capacity;
    void grow();
public:
    explicit vector();
    explicit vector(unsigned n);
    explicit vector(vector const & v);
    ~vector();
    T& operator[](unsigned i);
    T const & operator[](unsigned i) const;
    T& at(unsigned i);
    T const & at(unsigned i) const;
    unsigned get_size();
    unsigned get_capacity();
    void resize(unsigned n);
    void push_back(T const & x);
    void pop_back(T & t);
    T& back();
    T const & back() const;
    class iterator;
    iterator begin();
    iterator end();
};

template <class T>
class my::vector<T>::iterator {
    T* p;
public:
    iterator(T* ptr = 0);
    iterator(iterator const & tmp);
    T* operator->();
    T& operator*();
    iterator operator++();
    iterator operator++(int);
    iterator operator--();
    iterator operator--(int);
    void operator=(iterator it);
    iterator operator+(iterator it2);
    iterator operator-(iterator it2);
    bool operator==(iterator it2);
    bool operator!=(iterator it2);
};

struct Str {
    int a;
    int b;
};

template <class T>
my::vector<T>::vector(): size(MIN_SIZE), capacity(MIN_SIZE*sizeof(T)) {
    storage = new char[capacity];
}

template <class T>
my::vector<T>::vector(unsigned n): size(n), 
            capacity(n > MIN_SIZE ? sizeof(T)*n : sizeof(T)*MIN_SIZE) {
    T* ptr;
    unsigned i;
    storage = new char[capacity];
    ptr = (T*)storage;
    for(i = 0; i < n; i++) {
        new (ptr) T(); // placement new (calling constructors)
        ptr++;
    }
}

template <class T>
my::vector<T>::vector(vector const & v): size(v.size), capacity(v.capacity) {
    unsigned i;
    storage = new char[capacity];
    for(i = 0; i < v.size; i++)
        new ((T*)storage + i) T(v[i]);
}

template <class T>
my::vector<T>::~vector() {
    unsigned i;
    for(i = 0; i < size; i++)
        ((T*)storage + i)->~T();
    if (capacity > 0)
        delete[] storage;
}

template <class T>
T& my::vector<T>::operator[](unsigned i) {
    T& obj = *((T*)storage + i);
    return obj;
}

template <class T>
T const & my::vector<T>::operator[](unsigned i) const {
    T const & obj = *((T*)storage + i);
    return obj;
}

template <class T>
T& my::vector<T>::at(unsigned i) {
    if (i >= size) {
        throw "false index";
    }
    T& obj = *((T*)storage + i);
    return obj;
}

template <class T>
T const & my::vector<T>::at(unsigned i) const {
    if (i >= size)
        throw "false index";
    T const & obj = *((T*)storage + i);
    return obj;
}

template <class T>
unsigned my::vector<T>::get_size() {
    return size;
}

template <class T>
unsigned my::vector<T>::get_capacity() {
    return capacity;
}

template <class T>
void my::vector<T>::grow() {
    char* p;
    unsigned i;
    capacity = capacity*2;
    p = new char[capacity];
    for(i = 0; i < size; i++)
        new ((T*)p + i) T(storage[i]);
    for(i = 0; i < size; i++)
        ((T*)storage + i)->~T();
    if (size != 0)
        delete storage;
    storage = p;
}

template <class T>
void my::vector<T>::resize(unsigned n) {
    unsigned i, amount;
    T* ptr;
    if (n > size) {
        while (n*sizeof(T) > capacity) {
            grow();
        }
        ptr = (T*)storage + size;
        //amount = (capacity - size*sizeof(T))/sizeof(T); // free space
        for(i = 0; i < n; i++) {
            new (ptr) T(); // placement new (calling constructors)
            ptr++;
        }
        size = n;
    } else {
        for(i = n; i < size; i++)
            ((T*)(storage+i))->~T();
        size = n;
    }
}

template <class T>
void my::vector<T>::push_back(T const & x) {
    if (capacity >= sizeof(T)*(size+1))
        *((T*)storage + size) = x;
    else {
        grow();
        *((T*)storage + size) = x;
    }
    size++;
}

template <class T>
T& my::vector<T>::back() {
    T& obj = *((T*)storage + size - 1);
    return obj;
}

template <class T>
T const & my::vector<T>::back() const {
    T const & obj = *((T*)storage + size - 1);
    return obj;
}

template <class T>
void my::vector<T>::pop_back(T& t) {
    if (size == 0)
        throw "vector underflow";
    t = *((T*)storage + size - 1);
    ((T*)storage + size - 1)->~T();
    size = size - 1;
}

//iterator:
template <class T>
typename my::vector<T>::iterator my::vector<T>::begin() {
    T* obj = (T*)storage;
    iterator it(obj);
    return it;
}

template <class T>
typename my::vector<T>::iterator my::vector<T>::end() {
    T* obj = (T*)storage + size;
    iterator it(obj);
    return it;
}

template <class T>
my::vector<T>::iterator::iterator(T* ptr = 0) {
    p = ptr;
}

template <class T>
my::vector<T>::iterator::iterator(iterator const & it) {
    p = it.p;
}

template <class T>
void my::vector<T>::iterator::operator=(iterator it) {
    p = it.p;
}

template <class T>
T& my::vector<T>::iterator::operator*() {
    return *p;
}

template <class T>
T* my::vector<T>::iterator::operator->() {
    return p;
}

template <class T>
typename my::vector<T>::iterator my::vector<T>::iterator::operator++() {
    p++;
    return *this;
}

template <class T>
typename my::vector<T>::iterator my::vector<T>::iterator::operator++(int) {
    iterator tmp(p);
    p++;
    return tmp;
}

template <class T>
typename my::vector<T>::iterator my::vector<T>::iterator::operator--() {
    iterator(p--);
    return tmp;
}

template <class T>
typename my::vector<T>::iterator my::vector<T>::iterator::operator--(int) {
    iterator tmp(p);
    p--;
    return tmp;
}

template <class T>
typename my::vector<T>::iterator my::vector<T>::iterator::operator+(iterator it2) {
    iterator it(p + it2.p);
    return it;
}

template <class T>
typename my::vector<T>::iterator my::vector<T>::iterator::operator-(iterator it2) {
    iterator it(p - it2.p);
    return it;
}

template <class T>
bool my::vector<T>::iterator::operator==(iterator it2) {
    return (p == it2.p);
}

template <class T>
bool my::vector<T>::iterator::operator!=(iterator it2) {
    return !(p == it2.p);
}

using namespace std;

int main()
{
    int i, n, pi, x;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    cout << "enter n:"<< endl;
    cin >> n;
    my::vector<int> a(n);
    cout << "unitiallized: " << endl;
    for(i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl << endl << "enter vector: " << endl;
    for(i = 0; i < n; i++)
        cin >> a[i];
    cout << "vector a: ";
    for(i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl << endl << "size of a = " << a.get_size() << endl;
    cout << "capacity of a = " << a.get_capacity() << endl << endl;
    my::vector<int> b(a);
    cout << "vector b(a): ";
    for(i = 0; i < n; i++)
        cout << b[i] << " ";
    cout << endl << endl;
    // test 2
    cout << "test 2:" << endl;
    my::vector<Str> s(5);
    my::vector<Str>::iterator it = s.begin();
    it->a = 1;
    it->b = it->a + 6;
    cout << "a = " << it->a << "b = " << it->b << endl;
    // test 1
    my::vector<int>::iterator ita = a.begin();
    my::vector<int>::iterator end = a.end();
    cout << "test1: ";
    for(; ita != end; ita++)
        cout << *ita << " ";
    cout << endl;

    ita = a.begin();
    cout << "test3:" << endl;
    cout << "++: " << *(ita++) << endl;
    cout << "++: " << *(++ita) << endl;

    cin >> n;
    return 0;
}