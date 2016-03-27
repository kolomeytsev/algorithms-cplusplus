#include "map.h"

#ifndef ITERATOR_CPP
#define ITERATOR_CPP

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::iterator my::map<T, Mapped, Cmp>::begin() {
    //T* obj = (T*)storage;
    //iterator it(obj);
    //return it;
    Node* tmp = root;
    if (tmp == 0) {
        iterator it;
        return it;
    }
    while (tmp->left != nil)
        tmp = tmp->left;
    iterator it(tmp, nil);
    //std::cout << "nil color: " << nil->color << std::endl;
    return it;
}

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::iterator my::map<T, Mapped, Cmp>::end() {
    iterator it(nil, nil);
    return it;
}

template <class T, class Mapped, class Cmp>
my::map<T, Mapped, Cmp>::iterator::iterator(Node* ptr = 0): p(ptr) {}

template <class T, class Mapped, class Cmp>
my::map<T, Mapped, Cmp>::iterator::iterator(Node* ptr, Node* n): p(ptr), nil(n) {}

template <class T, class Mapped, class Cmp>
my::map<T, Mapped, Cmp>::iterator::iterator(iterator const & it): p(it.p), nil(it.nil) {}

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::iterator& 
                    my::map<T, Mapped, Cmp>::iterator::operator=(iterator const & it) {
    p = it.p;
    nil = it.nil;
    return *this;
}

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::value_type& 
                            my::map<T, Mapped, Cmp>::iterator::operator*() {
    return p->value;
}

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::value_type* 
                            my::map<T, Mapped, Cmp>::iterator::operator->() {
    return &(p->value);
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::iterator::operator==(iterator it2) {
    return (p == it2.p);
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::iterator::operator!=(iterator it2) {
    return !(p == it2.p);
}
//
template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::iterator& 
                            my::map<T, Mapped, Cmp>::iterator::operator++() {
    Node* tmp;
    Node* tmp_prev;
    Node* tmp_par;
    tmp = p;
    if (tmp->right != nil) {
        tmp = tmp->right;
        while(tmp->left != nil) {
            tmp = tmp->left;
        }
        p = tmp;
        return *this;
    }
    tmp_par = tmp->parent;
    tmp_prev = tmp;
    for(;;) {
        if (tmp_par == nil) {       // tmp_prev == root
            p = nil;
            return *this;
        }
        if (tmp_par->left == tmp_prev) {
            p = tmp_par;
            return *this;
        }
        tmp_prev = tmp_par;
        tmp_par = tmp_par->parent;
    }
}

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::iterator& 
                            my::map<T, Mapped, Cmp>::iterator::operator--() {
    Node* tmp;
    Node* tmp_prev;
    Node* tmp_par;
    tmp = p;
    if (tmp->left != nil) {
        tmp = tmp->left;
        while(tmp->right != nil)
            tmp = tmp->right;
        p = tmp;
        return *this;
    }
    tmp_par = tmp->parent;
    tmp_prev = tmp;

    for(;;) {
        if (tmp_par == nil) {       // tmp_prev == root
            p = nil;
            return *this;
        }
        if (tmp_par->right == tmp_prev) {
            p = tmp_par;
            return *this;
        }
        tmp_prev = tmp_par;
        tmp_par = tmp_par->parent;
    }
}

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::iterator 
                            my::map<T, Mapped, Cmp>::iterator::operator++(int) {
    iterator tmp(p);
    //next p;
    return tmp;
}

#endif // ITERATOR_CPP
