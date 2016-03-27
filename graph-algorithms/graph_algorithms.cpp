#include <iostream>
#include <vector>
#include <list>
#include <map>

template <class V, class E>
void algorithm_kosaraiu(Graph<V, E> graph) {
    cout << endl << "SCC: " << endl;
    vector<V> vect;
    vector<V>::iterator it;
    vector<V>::iterator it_end;

    vect = graph.dfs_stack_vect_return();

    graph.invert();
    graph.set_colors();

    vector< vector<V> > vect_vect;
    vector< vector<V> >::iterator it1;
    vector< vector<V> >::iterator it1_end;
    vector<V>::iterator it2;
    vector<V>::iterator it2_end;

    vect_vect = graph.dfs_stack_3(vect);

    cout << endl << "result:" << endl;
    it1_end = vect_vect.end();
    for(it1 = vect_vect.begin(); it1 != it1_end; it1++) {
        cout << "components: ";
        it2_end = (*it1).end();
        for(it2 = (*it1).begin(); it2 != it2_end; it2++)
            cout << (*it2) << " ";
        cout << endl;
    }
}

template <class V>
bool unvisited_exists(map<V, int> dm, map<V, int> visit_m, V* pv) {
    map<V, int>::iterator vit;
    map<V, int>::iterator vit_end;
    int min = INT_MAX;
    bool t = false;
    vit_end = visit_m.end();
    for(vit = visit_m.begin(); vit != vit_end; vit++) {
        if (vit->second == 0)
            if (dm[vit->first] < min) {
                min = dm[vit->first];
                *pv = vit->first;
                t = true;
            }
    }
    return t;
}

template <class V, class E>
map<V, int> algorithm_deikstra(Graph<V, E> graph, V vert) {
    typedef map< V, list< Elem < V, E > > > data_t;
    typedef list< Elem< V, E > > list_t;
    map<V, int> dmap;
    map<V, int> visit_map;
    typename data_t::iterator it;
    typename data_t::iterator it_end;
    V v;
    typename data_t g;
    g = graph.get_map();

    typename data_t::iterator Iter_map;
    typename list_t::iterator Iter_list;
    typename list_t::iterator Iter_list_end;
    list_t lst;

    it_end = g.end();
    for(it = g.begin(); it != it_end; it++)
        dmap[it->first] = INT_MAX;
    dmap[vert] = 0;

    it_end = g.end();
    for(it = g.begin(); it != it_end; it++) {
        visit_map[it->first] = 0;   //  vertex IS NOT visited
    }
    while (unvisited_exists(dmap, visit_map, &v)) {
        visit_map[v] = 1;
        Iter_map = g.find(v);
        lst = (Iter_map->second);
        Iter_list_end = lst.end();
        for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) {
            if (dmap[Iter_list->vert] > dmap[v] + Iter_list->edge) {
                dmap[Iter_list->vert] = dmap[v] + Iter_list->edge;
            }
        }
    }
    return dmap;
}

template <class V, class E>
vector<Elem2> Graph<V, E>::give_edges() {
    vector<Elem2> v;
    Elem2 str;
    typename data_t::iterator Iter_map;
    typename data_t::iterator Iter_map_end;
    typename list_t::iterator Iter_list;
    typename list_t::iterator Iter_list_end;
    typename data_t::iterator Iter_map_inverted;
    Iter_map_end = g.end();
    for(Iter_map = g.begin(); Iter_map != Iter_map_end; Iter_map++) {
        Iter_list_end = (Iter_map->second).end();
        str.vert1 = Iter_map->first;
        for(Iter_list = (Iter_map->second).begin(); Iter_list != Iter_list_end; Iter_list++){
            str.vert2 = Iter_list->vert;
            str.edge = Iter_list->edge;
            v.push_back(str);
        }
    }
    return v;
}

void print_edges(vector<Elem2> v) {
    vector<Elem2>::iterator it;
    vector<Elem2>::iterator it_end;
    it_end = v.end();
    for(it = v.begin(); it != it_end; it++)
        cout << it->vert1 << " -> " << it->vert2 << " = " << it->edge << endl;
}

template <class V, class E>
Graph<V, E> algorithm_kruskal(Graph<V, E> graph) {
    typedef map< V, list< Elem < V, E > > > data_t;
    typedef list< Elem< V, E > > list_t;
    Graph<V, E> new_graph;
    Elem2 str;
    vector<Elem2> v;
    v = graph.give_edges();             //step 1
    Compare cmp;
    sort(v.begin(), v.end(), cmp);

    typename data_t g;
    g = graph.get_map();

    typename data_t::iterator Iter_map;     //step 2
    typename data_t::iterator Iter_map_end;
    Iter_map_end = g.end();

    Sets s1;

    for(Iter_map = g.begin(); Iter_map != Iter_map_end; Iter_map++) {
        s1.make();
        new_graph.insert_vert(Iter_map->first);
    }

    vector<Elem2>::iterator vit;            //step 3
    vector<Elem2>::iterator vit_end;
    vit_end = v.end();
    for(vit = v.begin(); vit != vit_end; vit++) {
        int pa, pb;
        pa = s1.find(vit->vert1);
        pb = s1.find(vit->vert2);
        if (pa != pb) {
            s1.unite(pa, pb);
            new_graph.insert_edge(vit->vert1, vit->vert2, vit->edge);
        }
    }
    return new_graph;
}

int main()
{

    return 0;
}