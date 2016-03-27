#include "map.h"

#ifndef MAP_CPP
#define MAP_CPP

template <class T, class Mapped, class Cmp>
my::map<T, Mapped, Cmp>::map(const map& m): compare(m.compare) {
    Node* tmp;
    if (m.root != 0) {
        root = new Node(m.root->value, m.root->color);
        nil = new Node(black); //
        go_copy(m.root, root, m.nil);
        root->parent = nil;
    }
}

template <class T, class Mapped, class Cmp>
void my::map<T, Mapped, Cmp>::go_copy(Node* t, Node* tmp, Node* t_nil) {
    if (t != t_nil) {
        if (t->right != t_nil) {
            tmp->right = new Node(t->right->value, t->right->color);
            tmp->right->parent = tmp;
        } else
            tmp->right = nil;
        if (t->left != t_nil) {
            tmp->left = new Node(t->left->value, t->left->color);
            tmp->left->parent = tmp;
        } else
            tmp->left = nil;
        go_copy(t->right, tmp->right, t_nil);
        go_copy(t->left, tmp->left, t_nil);
    }
}

template <class T, class Mapped, class Cmp>
my::map<T, Mapped, Cmp>::~map() {
    if (root != 0)
        kill_em_all(root);
    if (nil != 0)
        delete nil;
}

template <class T, class Mapped, class Cmp>
void my::map<T, Mapped, Cmp>::kill_em_all(Node* t) {
    if (t != nil) {
        kill_em_all(t->left);
        kill_em_all(t->right);
        delete t;
    }
}

template <class T, class Mapped, class Cmp>
void my::map<T, Mapped, Cmp>::print() {
    if ((root != nil)&&(root != 0)) {
        std::cout << std::endl;
        std::cout << "root = " << root->value.first << std::endl;
        go(root);
        std::cout << std::endl;
    }
}

template <class T, class Mapped, class Cmp>
void my::map<T, Mapped, Cmp>::go(Node* t) {
    if (t != nil) {
        go(t->left);
        if (t->color == red)
            std::cout << "R" << " ";
        else
            std::cout << "B" << " ";
        std::cout << t->value.first << ": ";
        if (t->left != nil)
            std::cout << "left = " << t->left->value.first << " " << t->left->value.second << " " << t->left->color << " ";
        else
            std::cout << "left = nil ";
        if (t->right != nil)
            std::cout << "right = " << t->right->value.first << " " << t->right->value.second << " " << t->right->color << " ";
        else
        std::cout << "right = nil ";
        std::cout << std::endl;
        go(t->right);
    }
}

#endif // MAP_CPP
