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
    typename data_t::iterator Iter_map;     // define iterators
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
        return 2;   // no vert1 or no vert2
    Iter_list_end1 = (Iter_map->second).end();
    for(Iter_list = (Iter_map->second).begin(); Iter_list != Iter_list_end1; Iter_list++) {
        if (Iter_list->vert == vert2) {
            vert_vector.push_back(Iter_list->edge);
        }
    }
    if (vert_vector.empty())
        return 1;   //no road between vert1 and vert2
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
            if (flag == 0) {    // no vert added
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
                if (flag == 0) {    // no vert added
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
            if (flag == 0) {    // no vert added
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
                if (flag == 0) {    // no vert added
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
    if (!stack_it.empty()) {    // stack is not empty
        v = stack_it.top();
        if (G != 0)
            Iter_map = (*G).g.find(v);
        else {
            cout << "!!!" << endl;
            exit(1);
        }
        lst = (Iter_map->second);
        Iter_list_end = lst.end();
        for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) { //search for white son
            if (is_it_white(Iter_list->vert)) {
                stack_it.push(Iter_list->vert);
                paint_it_grey(Iter_list->vert);
                cur_it = (*G).g.find(Iter_list->vert);
                return *this;   //  white son exists
            }
        }
        stack_it.pop(); // no white son
        paint_it_black(Iter_map->first);
        cur_it = Iter_map;
        return *this;
    }
    else {  //  stack is empty
        if (white_exists_it()) {    //search for new white
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
    if (!stack_it.empty()) {    // stack is not empty
        v = stack_it.top();
        Iter_map = (*G).g.find(v);
        lst = (Iter_map->second);
        Iter_list_end = lst.end();
        for(Iter_list = lst.begin(); Iter_list != Iter_list_end; Iter_list++) { //search for white son
            if (is_it_white(Iter_list->vert)) {
                stack_it.push(Iter_list->vert);
                paint_it_grey(Iter_list->vert);
                cur_it = (*G).g.find(Iter_list->vert);
                return tmp; //  white son exists
            }
        }
        stack_it.pop(); // no white son
        paint_it_black(Iter_map->first);
        cur_it = Iter_map;
        return tmp;
    }
    else {  //  stack is empty
        if (white_exists_it()) {    //search for new white
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
