#include <iostream>
#include <vector>
#include <algorithm>

#ifndef MAP_H
#define MAP_H

enum Colour { red, black };

namespace my {
    template <class T, class Mapped, class Cmp>
    class map;
}

template <class T, class Mapped, class Cmp = std::less<T> >
class my::map {
public:
    typedef std::pair<const T, Mapped> value_type;
protected:
    struct Node;
private:
    Node* root;
    Node* nil;
    int size;
    Cmp compare;

    void kill_em_all(Node* t);
    void go_copy(Node* t, Node* tmp, Node* t_nil);
    void go(Node* t);
    bool parent_is_left(Node* t);
    bool uncle_red(Node* t);
    bool uncle_red2(Node* t);
    bool is_right_child(Node* t);
    bool is_left_child(Node* t);
    void fix_up_ins(Node* t);
    void rotate_left(Node* t);
    void rotate_right(Node* t);
public:
    map(Cmp const & c = Cmp()): compare(c) {
        root = 0;
        size = 0;
        nil = new Node(black);
    }
    map(const map& m);
    ~map();
    void print();
    Node* find2(T elem);
    Mapped& operator[](T elem);
    Mapped const & operator[](T elem) const;
    void insert(T elem);
    class iterator;
    iterator begin();
    iterator end();

    iterator find(T elem);
    typedef std::pair<bool, iterator> Int_pair;
    Int_pair insert2(const value_type& elem);

    void erase(iterator it);
    //void delete_node(T elem);
    void fix_up_del(Node* t);
    // for fix_up_del
    bool brother_red(Node* t);
    bool nephews_black(Node* t);
    bool right_nephew_black(Node* t);
    bool brother_red2(Node* t);
    bool nephews_black2(Node* t);
    bool left_nephew_black(Node* t);

    iterator min();
    iterator max();

    int wsize() {
        return size;
    }
};

template <class T, class Mapped, class Cmp>
struct my::map<T, Mapped, Cmp>::Node {
    value_type value;
    Colour color;
    Node* parent;
    Node* left;
    Node* right;
    Node() {}
    Node(T elem): value(elem, Mapped()) {}
    Node(value_type v, Colour c): value(v) {
        color = c;
    }
    Node(Colour c): color(c) {  // for init nil
        right = 0;
        left = 0;
    }
};

template <class T, class Mapped, class Cmp>
class my::map<T, Mapped, Cmp>::iterator {
    Node* p;
    Node* nil;
public:
    friend map<T, Mapped, Cmp>;
    iterator(Node* ptr = 0);
    iterator(Node* ptr, Node* n);
    iterator(iterator const & it);
    value_type* operator->();
    value_type& operator*();
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    iterator& operator=(iterator const & it);
    bool operator==(iterator it2);
    bool operator!=(iterator it2);
};

#include "map.cpp"
#include "iterator.cpp"
#include "utility.cpp"
#endif // MAP_H
