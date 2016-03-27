#include <iostream>

using namespace std;

int main()
{
	int x;
	cin >> x;
	return 0;
}
///////////////////////////////////////GRAPH////////////////////////////////
/*
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
*/
/*
#include "graph.h"

#ifndef GRAPH_CPP
#define GRAPH_CPP

#include <vector>

using namespace std;

template <class V, class E>
Graph<V, E>::Graph() {
	nv = 0;
	ne = 0;
}

template <class V, class E>
int Graph<V, E>::get_nv() {
	return nv;
}

template <class V, class E>
int Graph<V, E>::get_ne() {
	return ne;
}

template <class V, class E>
bool Graph<V, E>::insert_vert(V vert) {
	if (g.find(vert) == g.end()) {
		nv++;
		g[vert] = list<Elem<V, E> >();
		return true;
	} else {
		return false;
	}
}

template <class V, class E>
bool Graph<V, E>::insert_edge(V vert1, V vert2, E edge) {
	Elem<V, E> elem;
	elem.vert = vert2;
	elem.edge = edge;
	if (g.find(vert2) == g.end())
		return false;
	if (g.find(vert1) != g.end()) {
		ne++;
		g[vert1].push_back(elem);
		return true;
	} else {
		return false;
	}
}

template <class V, class E>
void Graph<V, E>::print_graph() {
	map< V, list<Elem <V, E> > >::iterator Iter_map;
	map< V, list<Elem <V, E> > >::iterator Iter_map_end;
	list<Elem<V, E> >::iterator Iter_list;
	list<Elem<V, E> >::iterator Iter_list_end;
	list<Elem<V, E> > lst;
	Iter_map_end = g.end();
	for(Iter_map = g.begin(); Iter_map != Iter_map_end; Iter_map++) {
		lst = (Iter_map->second);
		Iter_list_end = lst.end();
		for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) {
			cout << Iter_map->first << " -> " << Iter_list->vert;
			cout << " = " << Iter_list->edge << endl;
		}
	}
}

template <class V, class E>
bool Graph<V, E>::erase_vert(V vert) {
	map< V, list<Elem <V, E> > >::iterator Iter_map;		// define iterators
	map< V, list<Elem <V, E> > >::iterator Iter_map_end;
	list<Elem<V, E> >::iterator Iter_list;
	list<Elem<V, E> >::iterator Iter_list_end;

	Iter_map = g.find(vert);
	if (Iter_map != g.end()) {
		g.erase(Iter_map);
		Iter_map_end = g.end();
		for(Iter_map = g.begin(); Iter_map != Iter_map_end; Iter_map++) {
			Iter_list_end = (Iter_map->second).end();
			std::vector<std::pair<map< V, list<Elem <V, E> > >::iterator, 
				list<Elem<V, E> >::iterator>> iter_list_vector;
			for(Iter_list = (Iter_map->second).begin(); Iter_list != Iter_list_end; Iter_list++){
				if (Iter_list->vert == vert) {
					iter_list_vector.push_back(std::make_pair(Iter_map, Iter_list));
				}
			}
			for (int i = 0; i < iter_list_vector.size(); i++) {
				(iter_list_vector[i].first->second).erase(iter_list_vector[i].second);
			}
		}
		return true;
	} else {
		return false;
	}
}

template <class V, class E>
bool Graph<V, E>::erase_edge(V vert1, V vert2) {
	map< V, list<Elem <V, E> > >::iterator Iter_map;
	list<Elem<V, E> >::iterator Iter_list;
	list<Elem<V, E> >::iterator Iter_list_end;
	list<Elem<V, E> > lst;
	Iter_map = g.find(vert1);
	if (Iter_map != g.end()) {
		Iter_list_end = (Iter_map->second).end();
		std::vector<std::pair<map< V, list<Elem <V, E> > >::iterator, 
				list<Elem<V, E> >::iterator>> iter_list_vector;
		for(Iter_list = (Iter_map->second).begin(); Iter_list != Iter_list_end; Iter_list++) {
			if (Iter_list->vert == vert2) {
				iter_list_vector.push_back(std::make_pair(Iter_map, Iter_list));
			}
		}
		if (iter_list_vector.empty())
			return false;
		for (int i = 0; i < iter_list_vector.size(); i++) {
			(iter_list_vector[i].first->second).erase(iter_list_vector[i].second);
		}
		return true;
	} else {
		return false;
	}
}

template <class V, class E>
int Graph<V, E>::operator()(V vert1, V vert2, E* edge) {
	map< V, list<Elem <V, E> > >::iterator Iter_map;
	map< V, list<Elem <V, E> > >::iterator Iter_map2;
	list<Elem<V, E> >::iterator Iter_list;
	list<Elem<V, E> >::iterator Iter_list_end1;
	list<Elem<V, E> >::iterator Iter_list_end2;
	vector<E> vert_vector;
	E minimum;

	Iter_map = g.find(vert1);
	Iter_map2 = g.find(vert2);
	if ((Iter_map == g.end())||(Iter_map2 == g.end()))
		return 2;	// no vert1 or no vert2
	Iter_list_end1 = (Iter_map->second).end();
	for(Iter_list = (Iter_map->second).begin(); Iter_list != Iter_list_end1; Iter_list++) {
		if (Iter_list->vert == vert2) {
			//cout << "edge in vector: " << Iter_list->vert << " " << Iter_list->edge << endl;
			vert_vector.push_back(Iter_list->edge);
		}
	}
	if (vert_vector.empty())
		return 1;	//no road between vert1 and vert2
	
	vector<E>::iterator it1;
	vector<E>::iterator it2;
	vector<E>::iterator it_min;
	it1 = vert_vector.begin();
	it2 = vert_vector.end();
	it_min = min(it1, it2);
	minimum = *it_min;
	*edge = minimum;
	return 0;
}

template <class V, class E>
map< V, std::list<Elem<V, E> > > & Graph<V, E>::get_map() {
	return g;
}

template <class V, class E>
void Graph<V, E>::invert() {
	map< V, list<Elem <V, E> > >::iterator Iter_map;
	map< V, list<Elem <V, E> > >::iterator Iter_map_end;
	list<Elem <V, E> >::iterator Iter_list;
	list<Elem <V, E> >::iterator Iter_list_end;
	Graph<V, E> g_inverted;
	map< V, list<Elem <V, E> > >::iterator Iter_map_inverted;
	Iter_map_end = g.end();
	for(Iter_map = g.begin(); Iter_map != Iter_map_end; Iter_map++) {
		Iter_list_end = (Iter_map->second).end();
		g_inverted.insert_vert(Iter_map->first);
		for(Iter_list = (Iter_map->second).begin(); Iter_list != Iter_list_end; Iter_list++){
			g_inverted.insert_vert(Iter_list->vert);
			g_inverted.insert_edge(Iter_list->vert, Iter_map->first ,Iter_list->edge);
		}
	}
	g = g_inverted.get_map();
}

#endif // GRAPH_CPP
*/
/*
#include "graph.h"

using namespace std;

int main()
{
	ifstream fin("input2.txt");
	ofstream fout("output2.txt");
	string str;
	int v1, v2, edge, res;
	string cmd1, cmd2, cmd3, cmd4, cmd5, cmd_invert, cmd_exit, cmd_print;
	Graph<int, int> graph;
	int p = 101;
	cmd1 = "insert_vertex";
	cmd2 = "insert_edge";
	cmd3 = "erase_vertex";
	cmd4 = "erase_edge";
	cmd5 = "get_edge";
	cmd_invert = "invert";
	cmd_exit = "exit";
	cmd_print = "print";
	for(;;) {
		fin >> str;
		if (cmd1 == str) {
			fin >> v1;
			if (graph.insert_vert(v1))
				fout << "ok" << endl;
			else
				fout << "error" << endl;
		} else
		if (cmd2 == str) {
			fin >> v1;
			fin >> v2;
			fin >> edge;
			if (graph.insert_edge(v1, v2, edge))
				fout << "ok" << endl;
			else
				fout << "error" << endl;
		} else
		if (cmd3 == str) {
			fin >> v1;
			if (graph.erase_vert(v1))
				fout << "ok" << endl;
			else
				fout << "error" << endl;
		} else
		if (cmd4 == str) {
			fin >> v1;
			fin >> v2;
			if (graph.erase_edge(v1, v2))
				fout << "ok" << endl;
			else
				fout << "error" << endl;
		} else
		if (cmd5 == str) {
			fin >> v1;
			fin >> v2;
			if (graph(v1, v2, &p)==0)
				fout << p << endl;
			else
				fout << "edge doesn't exist" << endl;
		} else
		if (cmd_invert == str) {
			graph.invert();
			fout << "ok" << endl;
		} else
		if (cmd_print == str) {
			fout << endl << "cmd print" << endl << endl;
			graph.print_graph();
			cout << endl;
		} else
		if (cmd_exit == str) {
			fout << "See you later" << endl;
			return 0;
		} else {
			return 1;
		}
	}
	return 0;
}
*/

/////////////////////////////////GRAPH2.0///////////////////////////////////////
/*
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
	iterator_dfs(typename data_t::iterator ptr_it, Graph<V, E>* pgraph) : ps_it(ptr_it, pgraph)	{}
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
		if (rank[pa-1] >= rank[pb-1])	//connect b to a
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
*/
/*
#include "graph2.h"

#ifndef GRAPH_CPP
#define GRAPH_CPP

template <class V, class E >
Graph<V, E >::Graph() {
	nv = 0;
	ne = 0;
}

template < class V, class E >
int Graph< V, E >::get_nv() {
	return nv;
}

template < class V, class E >
int Graph< V, E >::get_ne() {
	return ne;
}

template < class V, class E >
bool Graph< V, E >::insert_vert(V vert) {
	if (g.find(vert) == g.end()) {
		nv++;
		g[vert] = list<Elem<V, E> >();
		color_map[vert] = 0; // vert is white
		return true;
	} else {
		return false;
	}
}

template < class V, class E >
bool Graph< V, E >::insert_edge(V vert1, V vert2, E edge) {
	Elem< V, E > elem;
	elem.vert = vert2;
	elem.edge = edge;
	if (g.find(vert2) == g.end())
		return false;
	if (g.find(vert1) != g.end()) {
		ne++;
		g[vert1].push_back(elem);
		return true;
	} else {
		return false;
	}
}

template < class V, class E >
bool Graph< V, E >::erase_vert(V vert) {
	typename data_t::iterator Iter_map;		// define iterators
	typename data_t::iterator Iter_map_end;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end;
	typename data_color::iterator Iter_color_map;
	Iter_color_map = color_map.find(vert);
	Iter_map = g.find(vert);
	if (Iter_map != g.end()) {
		nv--;
		g.erase(Iter_map);
		color_map.erase(Iter_color_map);
		Iter_map_end = g.end();
		for(Iter_map = g.begin(); Iter_map != Iter_map_end; Iter_map++) {
			Iter_list_end = (Iter_map->second).end();
			vector< pair< typename data_t::iterator, typename list_t::iterator > > iter_list_vector;
			for(Iter_list = (Iter_map->second).begin(); Iter_list != Iter_list_end; Iter_list++){
				if (Iter_list->vert == vert) {
					iter_list_vector.push_back(make_pair(Iter_map, Iter_list));
				}
			}
			for (unsigned i = 0; i < iter_list_vector.size(); i++) {
				(iter_list_vector[i].first->second).erase(iter_list_vector[i].second);
			}
		}
		return true;
	} else {
		return false;
	}
}

template < class V, class E >
bool Graph< V, E >::erase_edge(V vert1, V vert2) {
	typename data_t::iterator Iter_map;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end;
	Iter_map = g.find(vert1);
	if (Iter_map != g.end()) {
		ne--;
		Iter_list_end = (Iter_map->second).end();
		vector< pair< typename data_t::iterator, typename list_t::iterator > > iter_list_vector;
		for(Iter_list = (Iter_map->second).begin(); Iter_list != Iter_list_end; Iter_list++) {
			if (Iter_list->vert == vert2) {
				iter_list_vector.push_back(make_pair(Iter_map, Iter_list));
			}
		}
		if (iter_list_vector.empty())
			return false;
		for (unsigned i = 0; i < iter_list_vector.size(); i++) {
			(iter_list_vector[i].first->second).erase(iter_list_vector[i].second);
		}
		return true;
	} else {
		return false;
	}
}

template <class V, class E >
int Graph< V, E >::operator()(V vert1, V vert2, E* edge) {
	typename data_t::iterator Iter_map;
	typename data_t::iterator Iter_map2;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end1;
	typename list_t::iterator Iter_list_end2;
	vector< E > vert_vector;
	E minimum;

	Iter_map = g.find(vert1);
	Iter_map2 = g.find(vert2);
	if ((Iter_map == g.end())||(Iter_map2 == g.end()))
		return 2;	// no vert1 or no vert2
	Iter_list_end1 = (Iter_map->second).end();
	for(Iter_list = (Iter_map->second).begin(); Iter_list != Iter_list_end1; Iter_list++) {
		if (Iter_list->vert == vert2) {
			vert_vector.push_back(Iter_list->edge);
		}
	}
	if (vert_vector.empty())
		return 1;	//no road between vert1 and vert2
	typename vector< E >::iterator it1;
	typename vector< E >::iterator it2;
	typename vector< E >::iterator it_min;
	it1 = vert_vector.begin();
	it2 = vert_vector.end();
	it_min = min(it1, it2);
	minimum = *it_min;
	*edge = minimum;
	return 0;
}

template < class V, class E >
typename Graph< V, E >::data_t & Graph< V, E >::get_map() {
	return g;
}

template < class V, class E >
void Graph< V, E >::invert() {
	typename data_t::iterator Iter_map;
	typename data_t::iterator Iter_map_end;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end;
	Graph< V, E > g_inverted;
	typename data_t::iterator Iter_map_inverted;
	Iter_map_end = g.end();
	for(Iter_map = g.begin(); Iter_map != Iter_map_end; Iter_map++) {
		Iter_list_end = (Iter_map->second).end();
		g_inverted.insert_vert(Iter_map->first);
		for(Iter_list = (Iter_map->second).begin(); Iter_list != Iter_list_end; Iter_list++){
			g_inverted.insert_vert(Iter_list->vert);
			g_inverted.insert_edge(Iter_list->vert, Iter_map->first ,Iter_list->edge);
		}
	}
	g = g_inverted.get_map();
}

template < class V, class E >
void Graph< V, E >::print_color_map() {
	typename data_color::iterator Iter_map;
	typename data_color::iterator Iter_map_end;
	Iter_map_end = color_map.end();
	for(Iter_map = color_map.begin(); Iter_map != Iter_map_end; Iter_map++) {
		cout << "color of " << Iter_map->first << " is " << Iter_map->second << endl;
	}
}

template <class V, class E>
void Graph<V, E>::print_graph() {
	typename data_t::iterator Iter_map;
	typename data_t::iterator Iter_map_end;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end;
	list_t lst;
	int flag;
	Iter_map_end = g.end();
	for(Iter_map = g.begin(); Iter_map != Iter_map_end; Iter_map++) {
		lst = (Iter_map->second);
		Iter_list_end = lst.end();
		flag = 0;
		for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) {
			cout << Iter_map->first << " - " << Iter_list->vert;
			cout << " = " << Iter_list->edge << endl;
			flag = 1;
		}
		if (flag == 0)
			cout << Iter_map->first << endl;
	}
}

template <class V, class E>
inline void Graph<V, E>::paint_grey(V vert) {
	color_map[vert] = 1;
}

template <class V, class E>
inline void Graph<V, E>::paint_black(V vert) {
	color_map[vert] = 2;
}

template <class V, class E>
bool Graph<V, E>::white_exists() {
	typename data_color::iterator Iter_map;
	typename data_color::iterator Iter_map_end;
	Iter_map_end = color_map.end();
	for(Iter_map = color_map.begin(); Iter_map != Iter_map_end; Iter_map++)
		if (Iter_map->second == 0)
			return true;
	return false;
}

template <class V, class E>
V Graph<V, E>::give_me_white() {
	typename data_color::iterator Iter_map;
	typename data_color::iterator Iter_map_end;
	Iter_map_end = color_map.end();
	for(Iter_map = color_map.begin(); Iter_map != Iter_map_end; Iter_map++)
		if (Iter_map->second == 0)
			return Iter_map->first;
}

template <class V, class E>
bool Graph<V, E>::is_white(V vert) {
	typename data_color::iterator Iter_map;
	Iter_map = color_map.find(vert);
	if (Iter_map != color_map.end()) {
		if (Iter_map->second == 0)
			return true;
		else
			return false;
	}
	return false;
}

template <class V, class E>
void Graph<V, E>::dfs_stack() {
	typename data_t::iterator Iter_map;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end;
	list_t lst;
	stack< V > s;
	V v;
	int flag;
	while (white_exists()) {
		v = give_me_white();
		s.push(v);
		paint_grey(v);
		//cout << v << " ";
		while (!s.empty()) {
			v = s.top();
			Iter_map = g.find(v);
			lst = (Iter_map->second);
			Iter_list_end = lst.end();
			flag = 0;
			for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) {
				if (is_white(Iter_list->vert)) {
					s.push(Iter_list->vert);
					paint_grey(Iter_list->vert);
					//cout << Iter_list->vert << " ";
					flag = 1;
					break;
				}
			}
			if (flag == 0) {	// no vert added
				s.pop();
				paint_black(v);
				cout << v << " ";
			}
		}
	}
}

template <class V, class E>
void Graph<V, E>::set_colors() {
	typename data_t::iterator Iter_map;
	typename data_t::iterator Iter_map_end;
	Iter_map = g.begin();
	Iter_map_end = g.end();
	for(; Iter_map != Iter_map_end; Iter_map++)
		color_map[Iter_map->first] = 0;
}

template <class V, class E>
void Graph<V, E>::print_colors() {
	typename data_t::iterator Iter_map;
	typename data_t::iterator Iter_map_end;
	Iter_map = g.begin();
	Iter_map_end = g.end();
	cout << endl << "printing colors: " << endl;
	for(; Iter_map != Iter_map_end; Iter_map++)
		cout << color_map[Iter_map->first] << " ";
	cout << endl;
}

template <class V, class E>
void Graph<V, E>::dfs_stack_reverse(vector<V> vect) {
	typename data_t::iterator Iter_map;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end;
	typename vector<V>::reverse_iterator rIter_vect;
	typename vector<V>::reverse_iterator  rIter_vect_end;
	list_t lst;
	stack<V> s;
	V v;
	int flag;
	rIter_vect_end = vect.rend();
	for(rIter_vect = vect.rbegin(); rIter_vect != rIter_vect_end; rIter_vect++) {
		v = *rIter_vect;
		if (color_map[v] == 0) {
			s.push(v);
			paint_grey(v);
			cout << v << " ";
			while (!s.empty()) {
				v = s.top();
				Iter_map = g.find(v);
				lst = (Iter_map->second);
				Iter_list_end = lst.end();
				flag = 0;
				for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) {
					if (is_white(Iter_list->vert)) {
						s.push(Iter_list->vert);
						paint_grey(Iter_list->vert);
						cout << Iter_list->vert << " ";
						flag = 1;
						break;
					}
				}
				if (flag == 0) {	// no vert added
					s.pop();
					paint_black(v);
					cout << v << " ";
				}
			}
		}
	}
}

template <class V, class E>
vector<V> Graph<V, E>::dfs_stack_vect_return() {
	typename data_t::iterator Iter_map;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end;
	list_t lst;
	stack<V> s;
	vector<V> vect;
	V v;
	int flag;
	while (white_exists()) {
		v = give_me_white();
		s.push(v);
		paint_grey(v);
		while (!s.empty()) {
			v = s.top();
			Iter_map = g.find(v);
			lst = (Iter_map->second);
			Iter_list_end = lst.end();
			flag = 0;
			for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) {
				if (is_white(Iter_list->vert)) {
					s.push(Iter_list->vert);
					paint_grey(Iter_list->vert);
					flag = 1;
					break;
				}
			}
			if (flag == 0) {	// no vert added
				s.pop();
				paint_black(v);
				vect.push_back(v);
			}
		}
	}
	return vect;
}

template <class V, class E>
vector< vector<V> > Graph<V, E>::dfs_stack_3(vector<V> vect) {
	typename data_t::iterator Iter_map;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end;
	typename vector<V>::reverse_iterator rIter_vect;
	typename vector<V>::reverse_iterator  rIter_vect_end;
	list_t lst;
	stack<V> s;
	V v;
	vector< vector<V> > vect_vect;
	typename vector< vector<V> >::iterator Iter_vect_vect;
	int flag;
	rIter_vect_end = vect.rend();
	for(rIter_vect = vect.rbegin(); rIter_vect != rIter_vect_end; rIter_vect++) {
		v = *rIter_vect;
		if (color_map[v] == 0) {
			vector<V> vect2;
			s.push(v);
			paint_grey(v);
			//cout << v << " ";
			while (!s.empty()) {
				v = s.top();
				Iter_map = g.find(v);
				lst = (Iter_map->second);
				Iter_list_end = lst.end();
				flag = 0;
				for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) {
					if (is_white(Iter_list->vert)) {
						s.push(Iter_list->vert);
						paint_grey(Iter_list->vert);
						//cout << Iter_list->vert << " ";
						flag = 1;
						break;
					}
				}
				if (flag == 0) {	// no vert added
					s.pop();
					paint_black(v);
					vect2.push_back(v);
				}
			}
			vect_vect.push_back(vect2);
		}
	}
	return vect_vect;
}

template <class V, class E>
map<V, int> Graph<V, E>::bfs(V vert) {
	map<V, int> dmap;
	typename data_t::iterator it;
	typename data_t::iterator it_end;
	it_end = g.end();
	for(it = g.begin(); it != it_end; it++) {
		dmap[it->first] = INT_MAX;
	}
	dmap[vert] = 0;

	typename data_t::iterator Iter_map;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end;
	list_t lst;
	queue<V> Q;
	V v;

	Q.push(vert);
	color_map[vert] = 1;
	while (!Q.empty()) {
		v = Q.front();
		Q.pop();
		Iter_map = g.find(v);
		lst = (Iter_map->second);
		Iter_list_end = lst.end();
		for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) {
			if (is_white(Iter_list->vert)) {
				dmap[Iter_list->vert] = dmap[v] + 1;
				Q.push(Iter_list->vert);
				color_map[Iter_list->vert] = 1;
			}
		}
		color_map[vert] = 2;
	}
	return dmap;
}

////////////////////////////////PSEUDO_ITERATOR/////////////////////////////////

template <class V, class E>
typename Graph<V, E>::pseudo_iterator Graph<V, E>::begin_pseudo() { // BEGIN
	typename data_t::iterator Iter_map;
	Iter_map = g.begin();
	pseudo_iterator it(Iter_map, this);
	it.dfs_initiallize(Iter_map->first); // push'n'grey
	return it;
}

template <class V, class E>
void Graph<V, E>::pseudo_iterator::dfs_initiallize(V vert) {
	stack_it.push(vert);
	color_map_it[vert] = 1;
}

template <class V, class E>
typename Graph<V, E>::pseudo_iterator Graph<V, E>::end_pseudo() {
	typename data_t::iterator Iter_map_end;
	Iter_map_end = g.end();
	pseudo_iterator it(Iter_map_end, this);
	return it;
}

template <class V, class E>
Graph<V, E>::pseudo_iterator::pseudo_iterator(typename data_t::iterator ptr_it, 
												Graph<V, E>* pgraph) {
	cur_it = ptr_it;
	G = pgraph;
}

template <class V, class E>
Graph<V, E>::pseudo_iterator::pseudo_iterator(pseudo_iterator const & it) {
	color_map_it = it.color_map_it;
	cur_it = it.cur_it;
	stack_it = it.stack_it;
	G = it.G;
}

template <class V, class E>
void Graph<V, E>::pseudo_iterator::operator=(pseudo_iterator it) {
	color_map_it = it.color_map_it;
	cur_it = it.cur_it;
	stack_it = it.stack_it;
	G = it.G;
}

template <class V, class E>
V* Graph<V, E>::pseudo_iterator::operator->() {
	V* pv;
	pv = new V;
	*pv = cur_it->first;
	return pv;
}

template <class V, class E>
V Graph<V, E>::pseudo_iterator::operator*() {
	V v = cur_it->first;
	return v;
}

template <class V, class E>
inline void Graph<V, E>::pseudo_iterator::paint_it_grey(V vert) {
	color_map_it[vert] = 1;
}

template <class V, class E>
inline void Graph<V, E>::pseudo_iterator::paint_it_black(V vert) {
	color_map_it[vert] = 2;
}

template <class V, class E>
bool Graph<V, E>::pseudo_iterator::is_it_white(V vert) {
	typename data_color::iterator Iter_map;
	Iter_map = color_map_it.find(vert);
	if (Iter_map != color_map_it.end())
		return false;
	else
		return true;
}

template <class V, class E>
bool Graph<V, E>::pseudo_iterator::white_exists_it() {
	typename data_t::iterator Iter_map;
	typename data_t::iterator Iter_map_end;
	typename data_color::iterator Iter_color;
	typename data_color::iterator Iter_color_end;
	Iter_map_end = (*G).g.end();
	Iter_color_end = color_map_it.end();
	for(Iter_map = (*G).g.begin(); Iter_map != Iter_map_end; Iter_map++) {
		Iter_color = color_map_it.find(Iter_map->first);
		if (Iter_color == Iter_color_end)
			return true;
	}
	return false;
}

template <class V, class E>
V Graph<V, E>::pseudo_iterator::give_it_white() {
	typename data_t::iterator Iter_map;
	typename data_t::iterator Iter_map_end;
	typename data_color::iterator Iter_color;
	typename data_color::iterator Iter_color_end;
	Iter_map_end = (*G).g.end();
	Iter_color_end = color_map_it.end();
	for(Iter_map = (*G).g.begin(); Iter_map != Iter_map_end; Iter_map++) {
		Iter_color = color_map_it.find(Iter_map->first);
		if (Iter_color == Iter_color_end)
			return Iter_map->first;
	}
}

template <class V, class E>
typename Graph<V, E>::pseudo_iterator & Graph<V, E>::pseudo_iterator::operator++() {
	typename data_t::iterator Iter_map;
	typename data_t::iterator Iter_map_find;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end;
	list_t lst;
	V v;
	if (!stack_it.empty()) {	// stack is not empty
		v = stack_it.top();
		if (G != 0)
			Iter_map = (*G).g.find(v);
		else {
			cout << "!!!" << endl;
			exit(1);
		}
		lst = (Iter_map->second);
		Iter_list_end = lst.end();
		for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) {	//search for white son
			if (is_it_white(Iter_list->vert)) {
				stack_it.push(Iter_list->vert);
				paint_it_grey(Iter_list->vert);
				cur_it = (*G).g.find(Iter_list->vert);
				return *this;	//	white son exists
			}
		}
		stack_it.pop();	// no white son
		paint_it_black(Iter_map->first);
		cur_it = Iter_map;
		return *this;
	}
	else {	//	stack is empty
		if (white_exists_it()) {	//search for new white
			v = give_it_white();
			stack_it.push(v);
			paint_it_grey(v); // !!!
			cur_it = (*G).g.find(v);
		} else {
			cur_it = (*G).g.end();
		}
		return *this;
	}
}

template <class V, class E>
typename Graph<V, E>::pseudo_iterator Graph<V, E>::pseudo_iterator::operator++(int) {
	pseudo_iterator tmp(*this);
	typename data_t::iterator Iter_map;
	typename data_t::iterator Iter_map_find;
	typename list_t::iterator Iter_list;
	typename list_t::iterator Iter_list_end;
	list_t lst;
	V v;
	if (!stack_it.empty()) {	// stack is not empty
		v = stack_it.top();
		Iter_map = (*G).g.find(v);
		lst = (Iter_map->second);
		Iter_list_end = lst.end();
		for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) {	//search for white son
			if (is_it_white(Iter_list->vert)) {
				stack_it.push(Iter_list->vert);
				paint_it_grey(Iter_list->vert);
				cur_it = (*G).g.find(Iter_list->vert);
				return tmp;	//	white son exists
			}
		}
		stack_it.pop();	// no white son
		paint_it_black(Iter_map->first);
		cur_it = Iter_map;
		return tmp;
	}
	else {	//	stack is empty
		if (white_exists_it()) {	//search for new white
			v = give_it_white();
			stack_it.push(v);
			paint_it_grey(v); // !!!
			cur_it = (*G).g.find(v);
		} else {
			cur_it = (*G).g.end();
		}
		return tmp;
	}
}

template <class V, class E>
bool Graph<V, E>::pseudo_iterator::operator==(pseudo_iterator it) {
	return (cur_it == it.cur_it);
}

template <class V, class E>
bool Graph<V, E>::pseudo_iterator::operator!=(pseudo_iterator it) {
	return !(cur_it == it.cur_it);
}

template <class V, class E>
typename Graph<V, E>::pseudo_iterator Graph<V, E>::pseudo_iterator::give_me_end() {
	return (*G).end_pseudo();
}
