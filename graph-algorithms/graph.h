#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>

#ifndef GRAPH_H 
#define GRAPH_H

template <class V, class E>
struct Elem {
    V vert;
    E edge;
};

template <class V, class E>
class Graph {
    std::map< V, std::list<Elem<V, E> > > g;
    int nv;
    int ne;
public:
    Graph();
    int operator()(V vert1, V vert2, E* edge);
    bool insert_vert(V vert);
    bool insert_edge(V vert1, V vert2, E edge);
    bool erase_vert(V vert);
    bool erase_edge(V vert1, V vert2);
    int get_nv();
    int get_ne();
    void print_graph();
    void invert();
    std::map< V, std::list<Elem<V, E> > > & get_map();
};

#include "graph.cpp"
#endif // GRAPH_H