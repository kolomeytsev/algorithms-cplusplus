#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct Node {
    T value;
    Node* parent;
    Node* left;
    Node* right;
};

template <class T>
class BST {
    Node<T>* root;
public:
    BST();
    ~BST();
    void kill_em_all(Node<T>* t);
    void insert(T elem);
    void print();
    void go(Node<T>* t, vector<T> & v);
    T find_min();
    T find_max();
    T next(T elem);
    T prev(T elem);
    Node<T>* find(T elem); // or returns T* elem
    void erase(T elem);
    void complex_erase(T elem, Node<T>* tmp);
    void erase_no_child(T elem, Node<T>* tmp);
    void erase_left(T elem, Node<T>* tmp);  // left child exists
    void erase_right(T elem, Node<T>* tmp); // right child exists
};

template <class T>
BST<T>::BST() {
    root = 0;
}

template <class T>
BST<T>::~BST() {
    kill_em_all(root);
}

template <class T>
void BST<T>::kill_em_all(Node<T>* t) {
    if (t != 0) {
        kill_em_all(t->left);
        kill_em_all(t->right);
        delete t;
    }
}

template <class T>
void BST<T>::insert(T elem) {
    Node<T>* tmp;
    Node<T>* tmp2;
    Node<T>* tmp_prev;
    tmp = new Node<T>;
    tmp->left = 0;
    tmp->right = 0;
    tmp->parent = 0;
    tmp->value = elem;
    if (root == 0) {
        root = tmp;
    } else {
        tmp2 = root;
        for(;;) {
            if (tmp2->value > elem) {
                tmp_prev = tmp2;
                tmp2 = tmp2->left;
                if (tmp2 == 0) {
                    tmp_prev->left = tmp;
                    tmp->parent = tmp_prev;
                    break;
                }
            } else {
                tmp_prev = tmp2;
                tmp2 = tmp2->right;
                if (tmp2 == 0) {
                    tmp_prev->right = tmp;
                    tmp->parent = tmp_prev;
                    break;
                }
            }
        }
    }
}

template <class T>
void BST<T>::go(Node<T>* t, vector<T> & v) {
    if (t != 0) {
        go(t->left, v);
        v.push_back(t->value);
        go(t->right, v);
    }
}

template <class T>
void BST<T>::print() {
    vector<T> vect;
    vector<T>::iterator it;
    vector<T>::iterator it_end;
    go(root, vect);
    it_end = vect.end();
    for(it = vect.begin(); it != it_end; it++)
        cout << *it << " ";
    cout << endl;
}

template <class T>
T BST<T>::find_min() {
    Node<T>* tmp = root;
    while (tmp->left != 0)
        tmp = tmp->left;
    return tmp->value;
}

template <class T>
T BST<T>::find_max() {
    Node<T>* tmp = root;
    while (tmp->right != 0)
        tmp = tmp->right;
    return tmp->value;
}

template <class T>
T BST<T>::next(T elem) {
    Node<T>* tmp;
    Node<T>* tmp_prev;
    Node<T>* tmp_par;
    tmp = find(elem);
    if (tmp->right != 0) {
        tmp = tmp->right;
        while(tmp->left != 0)
            tmp = tmp->left;
        return tmp->value;
    }
    tmp_par = tmp->parent;
    tmp_prev = tmp;

    for(;;) {
        if (tmp_par == 0) {     // tmp_prev == root
            return elem;
        }
        if (tmp_par->left == tmp_prev)
            return tmp_par->value;
        tmp_prev = tmp_par;
        tmp_par = tmp_par->parent;
    }
}

template <class T>
T BST<T>::prev(T elem) {
    Node<T>* tmp;
    Node<T>* tmp_prev;
    Node<T>* tmp_par;
    tmp = find(elem);
    if (tmp->left != 0) {
        tmp = tmp->left;
        while(tmp->right != 0)
            tmp = tmp->right;
        return tmp->value;
    }
    tmp_par = tmp->parent;
    tmp_prev = tmp;

    for(;;) {
        if (tmp_par == 0) {     // tmp_prev == root
            return elem;
        }
        if (tmp_par->right == tmp_prev)
            return tmp_par->value;
        tmp_prev = tmp_par;
        tmp_par = tmp_par->parent;
    }
}

template <class T>
Node<T>* BST<T>::find(T elem) {
    Node<T>* tmp = root;
    Node<T>* tmp_prev;
    Node<T>* tmp_par;
    for(;;) {
        if (tmp->value > elem) {
            tmp_prev = tmp;
            tmp = tmp->left;
        } else
        if (tmp->value < elem) {
            tmp_prev = tmp;
            tmp = tmp->right;
        } else
        if (tmp->value == elem) {
            return tmp;     // tmp points on elem
        }
        if (tmp == 0)
            return 0;
    }
}

template <class T>
void BST<T>::erase(T elem) {
    Node<T>* tmp;
    Node<T>* tmp_prev;
    Node<T>* tmp_par;
    tmp = find(elem);
    if ((tmp->left == 0)&&(tmp->right == 0)) {      // no children
        erase_no_child(elem, tmp);
        return ;
    }
    if ((tmp->left == 0)&&(tmp->right != 0)) {      // has only right child
        erase_right(elem, tmp);
        return ;
    }
    if ((tmp->left != 0)&&(tmp->right == 0)) {      // has only left child
        erase_left(elem, tmp);
        return ;
    }
    if ((tmp->left != 0)&&(tmp->right != 0)) {      // has left and right children
        complex_erase(elem, tmp);
        return ;
    }
}

template <class T>
void BST<T>::complex_erase(T elem, Node<T>* tmp) {
    T el_next;
    el_next = next(elem);
    erase(el_next);
    tmp->value = el_next;
}

template <class T>
void BST<T>::erase_no_child(T elem, Node<T>* tmp) {
    Node<T>* tmp_par;
    tmp_par = tmp->parent;
    if (tmp_par == 0) {
        delete tmp;
        root = 0;
    } else {
        if (tmp_par->left != 0) {
            if (tmp_par->left->value == elem) {
                delete tmp_par->left;
                tmp_par->left = 0;
            } else {
                delete tmp_par->right;
                tmp_par->right = 0;
            }
        }
        else {
            delete tmp_par->right;
            tmp_par->right = 0;
        }
    }
}

template <class T>
void BST<T>::erase_left(T elem, Node<T>* tmp) {
    //cout << "deleting left " << elem << endl;
    Node<T>* tmp_par;
    tmp_par = tmp->parent;
    if (tmp_par == 0) {
        root = tmp->right;
        delete tmp;
    } else {
        if (tmp_par->left != 0) {
            if (tmp_par->left->value == elem) {
                tmp_par->left = tmp->left;
                tmp->left->parent = tmp_par;
                delete tmp;
            } else {
                tmp_par->right = tmp->left;
                tmp->left->parent = tmp_par;
                delete tmp;
            }
        } else {
            tmp_par->right = tmp->left;
            tmp->left->parent = tmp_par;
            delete tmp;
        }
    }
}

template <class T>
void BST<T>::erase_right(T elem, Node<T>* tmp) {
    //cout << "deleting right " << elem << endl;
    Node<T>* tmp_par;
    tmp_par = tmp->parent;
    if (tmp_par == 0) {     // parent is root
        root = tmp->right;
        root->parent = 0;
        delete tmp;
    } else {
        if (tmp_par->left != 0) {
            if (tmp_par->left->value == elem) {
                tmp_par->left = tmp->right;
                tmp->right->parent = tmp_par;
                delete tmp;
            } else {
                tmp_par->right = tmp->right;
                tmp->right->parent = tmp_par;
                delete tmp;
            }
        } else {
            tmp_par->right = tmp->right;
            tmp->right->parent = tmp_par;
            delete tmp;
        }
    }
}

int main()
{
    int i;
    BST<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(6);
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(7);
    tree.insert(9);
    tree.insert(8);
    tree.insert(10);

    cout << "max = " << tree.find_max() << endl;
    cout << "min = " << tree.find_min() << endl;
    for(i = 1; i < 11; i++)
        cout << "next(" << i << ") = " << tree.next(i) << endl;
    cout << endl;
    for(i = 1; i < 11; i++)
        cout << "prev(" << i << ") = " << tree.prev(i) << endl;
    
    cout << "erasing:" << endl;
    for(i = 1; i < 11; i++) {
        tree.erase(i);
        tree.print();
    }
    int x;
    cin >> x;
    return 0;
}