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