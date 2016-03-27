#include "map.h"

#ifndef UTILITY_CPP
#define UTILITY_CPP

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::Node* my::map<T, Mapped, Cmp>::find2(T elem) {
    Node* tmp = root;
    Node* tmp_prev;
    Node* tmp_par;
    if (tmp == 0)
        return 0;
    for(;;) {
        if (compare(elem, tmp->value.first)) {  // tmp->value.first > elem
            tmp_prev = tmp;
            tmp = tmp->left;
        } else
        if (compare(tmp->value.first, elem)) {  // tmp->value.first < elem
            tmp_prev = tmp;
            tmp = tmp->right;
        } else
        if ((compare(elem, tmp->value.first) == 0)&&(compare(tmp->value.first, elem) == 0)) {   // elem == tmp->value.first 
            return tmp;     // tmp points on elem
        }
        if (tmp == nil) // element not found
            return 0;
    }
}

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::iterator my::map<T, Mapped, Cmp>::find(T elem) {
    Node* tmp = root;
    Node* tmp_prev;
    Node* tmp_par;
    if (tmp == 0)
        return 0;
    for(;;) {
        if (compare(elem, tmp->value.first)) {  // tmp->value.first > elem
            tmp_prev = tmp;
            tmp = tmp->left;
        } else
        if (compare(tmp->value.first, elem)) {  // tmp->value.first < elem
            tmp_prev = tmp;
            tmp = tmp->right;
        } else
        if ((compare(elem, tmp->value.first) == 0)&&(compare(tmp->value.first, elem) == 0)) {   // elem == tmp->value.first 
            iterator it(tmp, nil);
            return it;      // tmp points on elem
        }
        if (tmp == nil) { // element not found return it(nil)
            iterator it(nil, nil);
            return it;
        }
    }
}

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::iterator my::map<T, Mapped, Cmp>::min() {
    Node* tmp = root;
    if (tmp == 0) {
        iterator it(nil, nil);
        return it;
    }
    while (tmp->left != nil)
        tmp = tmp->left;
    iterator it(tmp, nil);
    return it;
}

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::iterator my::map<T, Mapped, Cmp>::max() {
    Node* tmp = root;
    if (tmp == 0) {
        iterator it(nil, nil);
        return it;
    }
    while (tmp->right != nil)
        tmp = tmp->right;
    iterator it(tmp, nil);
    return it;
}

template <class T, class Mapped, class Cmp>
Mapped& my::map<T, Mapped, Cmp>::operator[](T elem) {
    Node* tmp;
    tmp = find2(elem);
    if (tmp == 0) {
        insert(elem);
        tmp = find2(elem);
        Mapped& obj = tmp->value.second;
        return obj;
    } else {
        Mapped& obj = tmp->value.second;
        return obj;
    }
}

template <class T, class Mapped, class Cmp>
Mapped const & my::map<T, Mapped, Cmp>::operator[](T elem) const {
    Node* tmp;
    tmp = find(elem);
    if (tmp == 0) {     // no such elem
        throw "No such elem!!!";
    } else {
        Mapped& obj = tmp->value.second;
        return obj;
    }
}

template <class T, class Mapped, class Cmp>
void my::map<T, Mapped, Cmp>::insert(T elem) {
    Node* tmp;
    Node* tmp2;
    Node* tmp_prev;
    tmp = new Node(elem);
    tmp->left = nil;
    tmp->right = nil;
    tmp->color = red;
    tmp->parent = 0;
    size++;
    if (root == 0) {
        root = tmp;
        root->parent = nil;
    } else {
        tmp2 = root;
        for(;;) {
            if (compare(elem, tmp2->value.first)) { // tmp2->value.first > elem
                tmp_prev = tmp2;
                tmp2 = tmp2->left;
                if (tmp2 == nil) {
                    tmp_prev->left = tmp;
                    tmp->parent = tmp_prev;
                    break;
                }
            } else {
                tmp_prev = tmp2;
                tmp2 = tmp2->right;
                if (tmp2 == nil) {
                    tmp_prev->right = tmp;
                    tmp->parent = tmp_prev;
                    break;
                }
            }
        }
    }
    fix_up_ins(tmp);
}

template <class T, class Mapped, class Cmp>
typename my::map<T, Mapped, Cmp>::Int_pair 
                        my::map<T, Mapped, Cmp>::insert2(const value_type& elem) {
    // insert #2
    Node* tmp;
    Node* tmp2;
    Node* tmp_prev;
    tmp = find2(elem.first);
    if (tmp != 0) {
        iterator it(nil, nil);
        Int_pair pr(false, it);
        return pr;
    }
    size++;
    //std::cout << "inserting" << elem.first << std::endl;
    tmp = new Node(elem, red); // elem - value_type
    tmp->left = nil;
    tmp->right = nil;
    //tmp->color = red;
    tmp->parent = 0;
    if (root == 0) {
        root = tmp;
        root->parent = nil;
    } else {
        tmp2 = root;
        for(;;) {
            if (compare(elem.first, tmp2->value.first)) {   // tmp2->value.first > elem
                tmp_prev = tmp2;
                tmp2 = tmp2->left;
                if (tmp2 == nil) {
                    tmp_prev->left = tmp;
                    tmp->parent = tmp_prev;
                    break;
                }
            } else {
                tmp_prev = tmp2;
                tmp2 = tmp2->right;
                if (tmp2 == nil) {
                    tmp_prev->right = tmp;
                    tmp->parent = tmp_prev;
                    break;
                }
            }
        }
    }
    fix_up_ins(tmp);
    iterator it(tmp, nil);
    Int_pair pr(true, it);
    return pr;
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::parent_is_left(Node* t) {
    Node* par;
    Node* dad;
    par = t->parent;
    dad = par->parent;
    if (dad->left == par)
        return true;
    else
        return false;
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::uncle_red(Node* t) {
    Node* par;
    Node* dad;
    par = t->parent;
    dad = par->parent;
    if (dad->right->color == red)
        return true;
    else
        return false;
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::uncle_red2(Node* t) {
    Node* par;
    Node* dad;
    par = t->parent;
    dad = par->parent;
    if (dad->left->color == red)
        return true;
    else
        return false;
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::is_right_child(Node* t) {
    Node* par;
    par = t->parent;
    if (par->right == t)
        return true;
    else
        return false;
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::is_left_child(Node* t) {
    Node* par;
    par = t->parent;
    if (par->left == t)
        return true;
    else
        return false;
}

template <class T, class Mapped, class Cmp>
void my::map<T, Mapped, Cmp>::rotate_left(Node* t) {
    Node* par;
    Node* child_right;
    Node* alfa;
    child_right = t->right;
    alfa = child_right->left;
    par = t->parent;
    if (par != nil) {
        if (par->left == t)     // t is left child
            par->left = child_right;
        else                    // t is right child
            par->right = child_right;
        child_right->parent = par;
        child_right->left = t;
        t->parent = child_right;
        t->right = alfa;
    } else {
        // t is root
        root = child_right;
        root->parent = nil;
        root->left = t;
        t->parent = root;
        t->right = alfa;
    }
}

template <class T, class Mapped, class Cmp>
void my::map<T, Mapped, Cmp>::rotate_right(Node* t) {
    Node* par;
    Node* child_left;
    Node* alfa;
    child_left = t->left;
    alfa = child_left->right;
    par = t->parent;
    if (par != nil) {
        if (par->left == t)     // t is left child
            par->left = child_left;
        else                    // t is right child
            par->right = child_left;
        child_left->parent = par;
        child_left->right = t;
        t->parent = child_left;
        t->left = alfa;
    } else {
        // t is root
        root = child_left;
        root->parent = nil;
        root->right = t;
        t->parent = root;
        t->left = alfa;
    }
}

template <class T, class Mapped, class Cmp>
void my::map<T, Mapped, Cmp>::fix_up_ins(Node* t) {
    Node* x;
    Node* par;
    Node* dad;
    x = t;
    while ((x->color == red)&&(x->parent->color == red)) {
        if (parent_is_left(x)) {
            if (uncle_red(x)) {
                par = x->parent;
                dad = par->parent;
                dad->color = red;
                dad->right->color = black;  // paint uncle in black
                par->color = black;
                x = dad;    // do next fix of dad
            } else {
                if (is_right_child(x)) {
                    rotate_left(x->parent);
                    x = x->left;
                }
                par = x->parent;
                dad = par->parent;
                dad->color = red;
                par->color = black;
                rotate_right(dad);
            }
        } else {
            if (uncle_red2(x)) {
                par = x->parent;
                dad = par->parent;
                dad->color = red;
                dad->left->color = black;   // paint uncle in black
                par->color = black;
                x = dad;    // do next fix of dad
            } else {
                if (is_left_child(x)) {
                    rotate_right(x->parent);
                    x = x->right;
                }
                par = x->parent;
                dad = par->parent;
                dad->color = red;
                par->color = black;
                rotate_left(dad);
            }
        }
    }
    root->color = black;
}

////////////////////////////////////////ERASE//////////////////////////////////

template <class T, class Mapped, class Cmp>
void my::map<T, Mapped, Cmp>::erase(iterator it) {
    Node* x;
    Node* y;
    Node* z;
    Colour clr;
    //T t;
    z = it.p;   // Node* find2(T elem); it->first == T, it->sec == Mapped
    if ((z->left == nil)||(z->right == nil))
        y = z;
    else {
        ++it;
        y = it.p;
    }
    if (y->left != nil)
        x = y->left;
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent == nil)
        root = x;
    else {
        if (y == y->parent->left)   // y is a left child
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    if (y != z) {
        //z->value = y->value;
        y->parent = z->parent;
        y->left = z->left;
        y->right = z->right;
        clr = z->color;
        z->color = y->color;
        y->color = clr;
    }
    if (z->color == black)  // x and y - black
        fix_up_del(x);
    delete z;
    size--;
}

template <class T, class Mapped, class Cmp>
void my::map<T, Mapped, Cmp>::delete_node(T elem) {
    Node* x;
    Node* y;
    Node* z;
    T t;
    z = find2(elem);        // Node* find2(T elem);
    if ((z->left == nil)||(z->right == nil))
        y = z;
    else {
        t = next(elem);
        y = find(t);
    }
    if (y->left != nil)
        x = y->left;
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent == nil)
        root = x;
    else {
        if (y == y->parent->left)   // y is a left child
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    if (y != z)
        z->value = y->value;
    if (y->color == black)  // x and y - black
        fix_up_del(x);
    delete y;
}


template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::brother_red(Node* t) {
    Node* par;
    par = t->parent;
    if (par->right->color == red)
        return true;
    else
        return false;
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::brother_red2(Node* t) {
    // if t is a right child
    Node* par;
    par = t->parent;
    if (par->left->color == red)
        return true;
    else
        return false;
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::nephews_black(Node* t) {
    Node* par;
    Node* brother;
    par = t->parent;
    brother = par->right;
    if (brother == nil)
        std::cout << "NIL!!!" << std::endl;
    if ((brother->left->color == black)&&(brother->right->color == black))
        return true;
    else
        return false;
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::nephews_black2(Node* t) {
    // if t is a right child
    Node* par;
    Node* brother;
    par = t->parent;
    brother = par->left;
    if ((brother->left->color == black)&&(brother->right->color == black))
        return true;
    else
        return false;
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::right_nephew_black(Node* t) {
    Node* par;
    Node* brother;
    par = t->parent;
    brother = par->right;
    if (brother->right->color == black)
        return true;
    else
        return false;
}

template <class T, class Mapped, class Cmp>
bool my::map<T, Mapped, Cmp>::left_nephew_black(Node* t) {
    // if t is right child
    Node* par;
    Node* brother;
    par = t->parent;
    brother = par->left;
    if (brother->left->color == black)
        return true;
    else
        return false;
}

template <class T, class Mapped, class Cmp>
void my::map<T, Mapped, Cmp>::fix_up_del(Node* t) {
    Node* x;
    Node* bro;
    x = t;
    while ((x != root)&&(x->color == black)) {
        if (x->parent->left == x) {
            //cout << "x is a left child" << endl;
            if (brother_red(x)) {           // step 4
                //cout << "brother is red" << endl;
                x->parent->color = red;
                bro = x->parent->right;
                bro->color = black;
                rotate_left(x->parent);
            }
            if (nephews_black(x)) {         // step 1
                //cout << "nephews are black" << endl;
                bro = x->parent->right;
                bro->color = red;
                x = x->parent;
            } else {
                if (right_nephew_black(x)) {    // step 3 (-> 2)
                    //cout << "right nephew is black" << endl;
                    bro = x->parent->right;
                    bro->color = red;
                    bro->left->color = black;
                    rotate_right(bro);
                }
                // step 2
                bro = x->parent->right;
                bro->color = x->parent->color;
                x->parent->color = black;
                bro->right->color = black;
                rotate_left(x->parent);
                x = root;
            }
        } else {
            //cout << "x is a right child" << endl;
            if (brother_red2(x)) {          // step 4
                //cout << "brother2 is red" << endl;
                x->parent->color = red;
                bro = x->parent->left;
                bro->color = black;
                rotate_right(x->parent);
                //cout << "after rotating" << endl;
                //print2();
            }
            if (nephews_black2(x)) {            // step 1
                //cout << "nephews2 are black" << endl;
                bro = x->parent->left;
                bro->color = red;
                x = x->parent;
            } else {
                if (left_nephew_black(x)) { // step 3 (-> 2)
                    //cout << "left nephew is black" << endl;
                    bro = x->parent->left;
                    bro->color = red;
                    bro->right->color = black;
                    rotate_left(bro);
                }
                // step 2
                bro = x->parent->left;
                bro->color = x->parent->color;
                x->parent->color = black;
                bro->left->color = black;
                rotate_right(x->parent);
                x = root;
            }
        }
    }
    x->color = black;
}

#endif // UTILITY_CPP
