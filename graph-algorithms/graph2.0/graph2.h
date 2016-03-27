#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include <climits>
#include <queue>
#include <algorithm>

#ifndef GRAPH_H 
#define GRAPH_H

using namespace std;

template < class V, class E >
struct Elem {
    V vert;
    E edge;
};

struct Elem2 {
    int vert1;
    int vert2;
    int edge;
};

class Compare {
public:
    bool operator()(Elem2 a, Elem2 b) {
        if (a.edge < b.edge)
            return true;
        else
            return false;
    }
};

template < class V, class E >
class Graph {
public:
    typedef map< V, list< Elem < V, E > > > data_t;
    typedef list< Elem< V, E > > list_t;
    typedef map< V, int > data_color;
private:
    data_t g;
    data_color color_map;
    int nv;
    int ne;
    
    V give_me_white();
    bool is_white(V vert);
    bool white_exists();
public:
    Graph();
    int operator()(V vert1, V vert2, E* edge);
    bool insert_vert(V vert);
    bool insert_edge(V vert1, V vert2, E edge);
    bool erase_vert(V vert);
    bool erase_edge(V vert1, V vert2);
    int get_nv();
    int get_ne();
    void invert();
    data_t & get_map();

    void print_graph();
    void print_color_map();

    inline void paint_grey(V vert);
    inline void paint_black(V vert);

    void set_colors();
    void print_colors();
    void dfs_stack();
    void dfs_stack_reverse(vector<V> vect);
    vector<V> dfs_stack_vect_return();
    vector< vector<V> > dfs_stack_3(vector<V> vect);

    class pseudo_iterator;
    friend class pseudo_iterator;
    class iterator_dfs;

    pseudo_iterator begin_pseudo();
    pseudo_iterator end_pseudo();
    iterator_dfs begin();
    iterator_dfs end();

    map<V, int> bfs(V vert);
    vector<Elem2> give_edges();
};

template <class V, class E>
class Graph<V, E>::pseudo_iterator {
public:
    typedef map< V, list< Elem < V, E > > > data_t;
    typedef list< Elem< V, E > > list_t;
    typedef map< V, int > data_color;
private:
    data_color color_map_it;
    typename data_t::iterator cur_it;
    stack<V> stack_it;
    Graph<V, E>* G;
public:
    pseudo_iterator() {
        G = 0;
    }
    pseudo_iterator(typename data_t::iterator ptr_it, Graph<V, E>* pgraph);
    pseudo_iterator(pseudo_iterator const & tmp);
    void dfs_initiallize(V vert);
    V* operator->();
    V operator*();
    void operator=(pseudo_iterator it);
    pseudo_iterator & operator++();
    pseudo_iterator operator++(int);
    bool operator==(pseudo_iterator it2);
    bool operator!=(pseudo_iterator it2);
    inline void paint_it_grey(V vert);
    inline void paint_it_black(V vert);
    bool is_it_white(V vert);
    bool white_exists_it();
    V give_it_white();

    pseudo_iterator give_me_end();
};

template <class V, class E>
class Graph<V, E>::iterator_dfs {
private:
    typename Graph<V, E>::pseudo_iterator ps_it;
    map<V, int> map_counter;
public:
    iterator_dfs() {}
    iterator_dfs(typename data_t::iterator ptr_it, Graph<V, E>* pgraph) : ps_it(ptr_it, pgraph) {}
    void dfs_init(V vert, map<V, int> map_count);
    iterator_dfs(iterator_dfs const & tmp);
    V* operator->();
    V operator*();
    void operator=(iterator_dfs it);
    iterator_dfs & operator++();
    iterator_dfs operator++(int);
    bool operator==(iterator_dfs it2);
    bool operator!=(iterator_dfs it2);
};

template <class V, class E>
void algorithm_kosaraiu(Graph<V, E> graph);

template <class V, class E>
map<V, int> algorithm_deikstra(Graph<V, E> graph, V vert);

template <class V, class E>
bool unvisited_exists(map<V, int> dm, map<V, int>  visit_m, V* pv);

template <class V, class E>
Graph<V, E> algorithm_kruskal(Graph<V, E> graph);

//void print_edges(vector<Elem2> v);

struct Str {
    int a;
    int b;
    bool operator==(Str s) {
        if ((a == s.a)&&(b == s.b))
            return true;
        else
            return false;
    }
    bool operator<(Str s) {
        if ((a < s.a)&&(b < s.b))
            return true;
        else
            return false;
    }
};

class Sets {
    vector<int> relation;
    vector<int> rank;
public:
    Sets() {}
    Sets(vector<int> vect) {
        relation = vect;
    }
    Sets(Sets const & s) {
        relation = s.relation;
        rank = s.rank;
    }
    void make() {
        int s;
        s = relation.size();
        s++;
        relation.push_back(s);
        rank.push_back(0);
    }
    int find(int a) {
        vector<int>::iterator it;
        it = relation.begin();
        if (a == *(it + a - 1))
            return a;
        else {
            relation[a-1] = find(*(it + a - 1));
            return find(*(it + a - 1));
        }
    }
    void unite(int a, int b) {
        int pa, pb;
        pa = find(a);
        pb = find(b);
        if (rank[pa-1] >= rank[pb-1])   //connect b to a
            relation[pb-1] = pa;
        else
            relation[pa-1] = pb;
        if (rank[pa-1] == rank[pb-1])
            rank[pa-1]++;
    }
    void print_relation() {
        int i = 1;
        cout << "print" << endl;
        vector<int>::iterator it;
        vector<int>::iterator it_end;
        it_end = relation.end();
        for(it = relation.begin(); it != it_end; it++) {
            cout << "vert " << i << " parent: " << *it << endl;
            i++;
        }
        cout << endl;
    }
    void print_rank() {
        int i = 1;
        cout << "rank" << endl;
        vector<int>::iterator it;
        vector<int>::iterator it_end;
        it_end = rank.end();
        for(it = rank.begin(); it != it_end; it++) {
            cout << i << " rank: " << *it << endl;
            i++;
        }
        cout << endl;
    }
};

#include "graph2.cpp"
#endif // GRAPH_H