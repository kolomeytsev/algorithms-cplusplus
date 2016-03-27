#include <iostream>
#include <vector>

using namespace std;

enum Colour { red, black };

template <class T>
struct Node {
	T value;
	Colour color;
	Node* parent;
	Node* left;
	Node* right;
};

template <class T>
class RBT {
	Node<T>* root;
	Node<T>* nil;
public:
	RBT();
	~RBT();
	void kill_em_all(Node<T>* t);
	void insert(T elem);
	void print();
	void print2();
	void go(Node<T>* t, vector<T> & v);
	void go2(Node<T>* t);
	T find_min();
	T find_max();
	T next(T elem);
	T prev(T elem);
	Node<T>* find(T elem); // or returns T* elem
	void erase(T elem);
	void complex_erase(T elem, Node<T>* tmp);
	void erase_no_child(T elem, Node<T>* tmp);
	void erase_left(T elem, Node<T>* tmp);	// left child exists
	void erase_right(T elem, Node<T>* tmp);	// right child exists

	// for fix_up_ins
	bool parent_is_left(Node<T>* t);
	bool uncle_red(Node<T>* t);
	bool uncle_red2(Node<T>* t);
	bool is_right_child(Node<T>* t);
	bool is_left_child(Node<T>* t);

	void fix_up_ins(Node<T>* t);	// fix ups
	void fix_up_del(Node<T>* t);

	// for fix_up_del
	bool brother_red(Node<T>* t);
	bool nephews_black(Node<T>* t);
	bool right_nephew_black(Node<T>* t);
	bool brother_red2(Node<T>* t);
	bool nephews_black2(Node<T>* t);
	bool left_nephew_black(Node<T>* t);

	void rotate_left(Node<T>* t);
	void rotate_right(Node<T>* t);

	void delete_node(T elem);
	
	void root_color();
};

template <class T>
RBT<T>::RBT() {
	root = 0;
	nil = new Node<T>;
	nil->value = 0;
	nil->color = black;
	nil->right = 0;
	nil->left = 0;
}

template <class T>
RBT<T>::~RBT() {
	kill_em_all(root);
}

template <class T>
void RBT<T>::kill_em_all(Node<T>* t) {
	if (t != nil) {
		kill_em_all(t->left);
		kill_em_all(t->right);
		delete t;
	}
}

template <class T>
void RBT<T>::insert(T elem) {
	Node<T>* tmp;
	Node<T>* tmp2;
	Node<T>* tmp_prev;
	tmp = new Node<T>;
	tmp->left = nil;
	tmp->right = nil;
	tmp->parent = 0;
	tmp->value = elem;
	tmp->color = red;
	if (root == 0) {
		root = tmp;
		root->parent = nil;
	} else {
		tmp2 = root;
		for(;;) {
			if (tmp2->value > elem) {
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

template <class T>
bool RBT<T>::parent_is_left(Node<T>* t) {
	Node<T>* par;
	Node<T>* dad;
	par = t->parent;
	dad = par->parent;
	if (dad->left == par)
		return true;
	else
		return false;
}

template <class T>
bool RBT<T>::uncle_red(Node<T>* t) {
	Node<T>* par;
	Node<T>* dad;
	par = t->parent;
	dad = par->parent;
	if (dad->right->color == red)
		return true;
	else
		return false;
}

template <class T>
bool RBT<T>::uncle_red2(Node<T>* t) {
	Node<T>* par;
	Node<T>* dad;
	par = t->parent;
	dad = par->parent;
	if (dad->left->color == red)
		return true;
	else
		return false;
}

template <class T>
bool RBT<T>::is_right_child(Node<T>* t) {
	Node<T>* par;
	par = t->parent;
	if (par->right == t)
		return true;
	else
		return false;
}

template <class T>
bool RBT<T>::is_left_child(Node<T>* t) {
	Node<T>* par;
	par = t->parent;
	if (par->left == t)
		return true;
	else
		return false;
}

template <class T>
void RBT<T>::rotate_left(Node<T>* t) {
	//cout << "rotating left" << endl;
	Node<T>* par;
	Node<T>* child_right;
	Node<T>* alfa;
	child_right = t->right;
	alfa = child_right->left;
	par = t->parent;
	if (par != nil) {
		if (par->left == t)		// t is left child
			par->left = child_right;
		else					// t is right child
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

template <class T>
void RBT<T>::rotate_right(Node<T>* t) {
	//cout << "rotating right" << endl;
	Node<T>* par;
	Node<T>* child_left;
	Node<T>* alfa;
	child_left = t->left;
	alfa = child_left->right;
	par = t->parent;
	if (par != nil) {
		if (par->left == t)		// t is left child
			par->left = child_left;
		else					// t is right child
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

template <class T>
void RBT<T>::fix_up_ins(Node<T>* t) {
	Node<T>* x;
	Node<T>* par;
	Node<T>* dad;
	x = t;
	while ((x->color == red)&&(x->parent->color == red)) {
		if (parent_is_left(x)) {
			//cout << "parent is left child of grandparent" << endl;
			if (uncle_red(x)) {
				//cout << "uncle is red" << endl;
				//step 1
				par = x->parent;
				dad = par->parent;
				dad->color = red;
				dad->right->color = black;	// paint uncle in black
				par->color = black;
				x = dad;	// do next fix of dad
			} else {
				if (is_right_child(x)) {
					//cout << "x is a right child" << endl;
					// step 2.1
					rotate_left(x->parent);
					x = x->left;
				}
				// step 2
				par = x->parent;
				dad = par->parent;
				dad->color = red;
				par->color = black;
				rotate_right(dad);
			}
		} else {
			//cout << "parent is right child of grandparent" << endl;
			if (uncle_red2(x)) {
				//cout << "uncle is red" << endl;
				//step 1
				par = x->parent;
				dad = par->parent;
				dad->color = red;
				dad->left->color = black;	// paint uncle in black
				par->color = black;
				x = dad;	// do next fix of dad
			} else {
				if (is_left_child(x)) {
					//cout << "x is a left child" << endl;
					// step 2.1
					rotate_right(x->parent);
					x = x->right;
				}
				// step 2
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

template <class T>
void RBT<T>::go(Node<T>* t, vector<T> & v) {
	if (t != nil) {
		go(t->left, v);
		v.push_back(t->value);
		if (t->color == red)
			cout << "R" << " ";
		else
			cout << "B" << " ";
		go(t->right, v);
	}
}

template <class T>
void RBT<T>::print() {
	vector<T> vect;
	vector<T>::iterator it;
	vector<T>::iterator it_end;
	go(root, vect);
	cout << endl;
	it_end = vect.end();
	for(it = vect.begin(); it != it_end; it++)
		cout << *it << " ";
	cout << endl;
}

template <class T>
void RBT<T>::print2() {
	cout << endl;
	cout << "root = " << root->value << endl;
	go2(root);
	cout << endl;
}

template <class T>
void RBT<T>::go2(Node<T>* t) {
	if (t != nil) {
		go2(t->left);
		if (t->color == red)
			cout << "R" << " ";
		else
			cout << "B" << " ";
		cout << t->value << ": ";
		if (t->left != nil)
			cout << "left = " << t->left->value << " " << t->left->color << " ";
		else
			cout << "left = nil ";
		if (t->right != nil)
			cout << "right = " << t->right->value << " " << t->right->color << " ";
		else
			cout << "right = nil ";
		cout << endl;
		go2(t->right);
	}
}

template <class T>
T RBT<T>::find_min() {
	Node<T>* tmp = root;
	//if (tmp = 0)
		//throw "tree is null";
	while (tmp->left != nil)
		tmp = tmp->left;
	return tmp->value;
}

template <class T>
T RBT<T>::find_max() {
	Node<T>* tmp = root;
	//if (tmp = 0)
		//throw "tree is null";
	while (tmp->right != nil)
		tmp = tmp->right;
	return tmp->value;
}

template <class T>
T RBT<T>::next(T elem) {
	Node<T>* tmp;
	Node<T>* tmp_prev;
	Node<T>* tmp_par;
	tmp = find(elem);
	if (tmp->right != nil) {
		tmp = tmp->right;
		while(tmp->left != nil)
			tmp = tmp->left;
		return tmp->value;
	}
	tmp_par = tmp->parent;
	tmp_prev = tmp;

	for(;;) {
		if (tmp_par == nil) {		// tmp_prev == root
			return elem;
		}
		if (tmp_par->left == tmp_prev)
			return tmp_par->value;
		tmp_prev = tmp_par;
		tmp_par = tmp_par->parent;
	}
}

template <class T>
T RBT<T>::prev(T elem) {
	Node<T>* tmp;
	Node<T>* tmp_prev;
	Node<T>* tmp_par;
	tmp = find(elem);
	if (tmp->left != nil) {
		tmp = tmp->left;
		while(tmp->right != nil)
			tmp = tmp->right;
		return tmp->value;
	}
	tmp_par = tmp->parent;
	tmp_prev = tmp;

	for(;;) {
		if (tmp_par == nil) {		// tmp_prev == root
			return elem;
		}
		if (tmp_par->right == tmp_prev)
			return tmp_par->value;
		tmp_prev = tmp_par;
		tmp_par = tmp_par->parent;
	}
}

template <class T>
Node<T>* RBT<T>::find(T elem) {
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
			return tmp;		// tmp points on elem
		}
		if (tmp == nil)
			return 0;
	}
}

template <class T>
void RBT<T>::erase(T elem) {
	Node<T>* tmp;
	Node<T>* tmp_prev;
	Node<T>* tmp_par;
	tmp = find(elem);
	if ((tmp->left == 0)&&(tmp->right == 0)) {		// no children
		erase_no_child(elem, tmp);
		return ;
	}
	if ((tmp->left == 0)&&(tmp->right != 0)) {		// has only right child
		erase_right(elem, tmp);
		return ;
	}
	if ((tmp->left != 0)&&(tmp->right == 0)) {		// has only left child
		erase_left(elem, tmp);
		return ;
	}
	if ((tmp->left != 0)&&(tmp->right != 0)) {		// has left and right children
		complex_erase(elem, tmp);
		return ;
	}
}

template <class T>
void RBT<T>::complex_erase(T elem, Node<T>* tmp) {
	T el_next;
	el_next = next(elem);
	erase(el_next);
	tmp->value = el_next;
}

template <class T>
void RBT<T>::erase_no_child(T elem, Node<T>* tmp) {
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
void RBT<T>::erase_left(T elem, Node<T>* tmp) {
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
void RBT<T>::erase_right(T elem, Node<T>* tmp) {
	//cout << "deleting right " << elem << endl;
	Node<T>* tmp_par;
	tmp_par = tmp->parent;
	if (tmp_par == 0) {		// parent is root
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

template <class T>
void RBT<T>::delete_node(T elem) {
	Node<T>* x;
	Node<T>* y;
	Node<T>* z;
	T t;
	z = find(elem);
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
		if (y == y->parent->left)	// y is a left child
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	if (y != z)
		z->value = y->value;
	if (y->color == black)	// x and y - black
		fix_up_del(x);
	delete y;
}

template <class T>
bool RBT<T>::brother_red(Node<T>* t) {
	Node<T>* par;
	par = t->parent;
	if (par->right->color == red)
		return true;
	else
		return false;
}

template <class T>
bool RBT<T>::brother_red2(Node<T>* t) {
	// if t is a right child
	Node<T>* par;
	par = t->parent;
	if (par->left->color == red)
		return true;
	else
		return false;
}

template <class T>
bool RBT<T>::nephews_black(Node<T>* t) {
	Node<T>* par;
	Node<T>* brother;
	par = t->parent;
	brother = par->right;
	if (brother == nil)
		cout << "NIL!!!" << endl;
	if ((brother->left->color == black)&&(brother->right->color == black))
		return true;
	else
		return false;
}

template <class T>
bool RBT<T>::nephews_black2(Node<T>* t) {
	// if t is a right child
	Node<T>* par;
	Node<T>* brother;
	par = t->parent;
	brother = par->left;
	if ((brother->left->color == black)&&(brother->right->color == black))
		return true;
	else
		return false;
}

template <class T>
bool RBT<T>::right_nephew_black(Node<T>* t) {
	Node<T>* par;
	Node<T>* brother;
	par = t->parent;
	brother = par->right;
	if (brother->right->color == black)
		return true;
	else
		return false;
}

template <class T>
bool RBT<T>::left_nephew_black(Node<T>* t) {
	// if t is right child
	Node<T>* par;
	Node<T>* brother;
	par = t->parent;
	brother = par->left;
	if (brother->left->color == black)
		return true;
	else
		return false;
}

template <class T>
void RBT<T>::fix_up_del(Node<T>* t) {
	Node<T>* x;
	Node<T>* bro;
	x = t;
	while ((x != root)&&(x->color == black)) {
		if (x->parent->left == x) {
			cout << "x is a left child" << endl;
			if (brother_red(x)) {			// step 4
				cout << "brother is red" << endl;
				x->parent->color = red;
				bro = x->parent->right;
				bro->color = black;
				rotate_left(x->parent);
			}
			if (nephews_black(x)) {			// step 1
				cout << "nephews are black" << endl;
				bro = x->parent->right;
				bro->color = red;
				x = x->parent;
			} else {
				if (right_nephew_black(x)) {	// step 3 (-> 2)
					cout << "right nephew is black" << endl;
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
			cout << "x is a right child" << endl;
			if (brother_red2(x)) {			// step 4
				cout << "brother2 is red" << endl;
				x->parent->color = red;
				bro = x->parent->left;
				bro->color = black;
				rotate_right(x->parent);
				//cout << "after rotating" << endl;
				//print2();
			}
			if (nephews_black2(x)) {			// step 1
				cout << "nephews2 are black" << endl;
				bro = x->parent->left;
				bro->color = red;
				x = x->parent;
			} else {
				if (left_nephew_black(x)) {	// step 3 (-> 2)
					cout << "left nephew is black" << endl;
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

template <class T>
void RBT<T>::root_color() {
	if (root->color == red)
		cout << root->value << " red" << endl;
	else
		cout << root->value << " black" << endl;
}

int main()
{
	int i;
	Node<int>* t;
	RBT<int> tree;

	tree.insert(5);
	tree.insert(4);
	tree.insert(6);
	tree.insert(2);
	tree.insert(1);
	tree.insert(3);
	tree.insert(9);
	tree.insert(7);
	tree.insert(8);
	tree.insert(10);

	tree.print();

	tree.print2();

	cout << "max = " << tree.find_max() << endl;
	cout << "min = " << tree.find_min() << endl;
	for(i = 1; i < 11; i++)
		cout << "next(" << i << ") = " << tree.next(i) << endl;
	cout << endl;
	for(i = 1; i < 11; i++)
		cout << "prev(" << i << ") = " << tree.prev(i) << endl;
	t = tree.find(5);
	cout << endl << t->value << endl;
	t = tree.find(100);
	if (t)
		cout << t->value << endl;
	else
		cout << "no such elem" << endl;

	tree.delete_node(10);
	tree.delete_node(8);
	tree.delete_node(9);
	tree.delete_node(7);
	tree.delete_node(6);
	tree.delete_node(2);
	tree.print2();
	tree.print();

	RBT<int> tree2;
	for(i = 1; i < 11; i++)
		tree2.insert(i);
	tree2.delete_node(9);
	tree2.delete_node(10);
	tree2.delete_node(4);
	tree2.print2();
	tree2.print();

	int x;
	cin >> x;
	return 0;
}