template <class V, class E>
void Graph<V, E>::iterator_dfs::dfs_init(V vert, map<V, int> map_count) {
    ps_it.dfs_initiallize(vert);
    map_counter = map_count;
    map<V, int>::iterator ite;
    map<V, int>::iterator ite_end;

    ite = map_counter.begin();
    ite_end = map_counter.end();
    map_counter[*ps_it]++;
    while (1) {
        ++ps_it;
        map_counter[*ps_it]++;
        if (map_counter[*ps_it] == 2) {
            break;
        }
    }
    ite = map_counter.begin();
    ite_end = map_counter.end();
}

template <class V, class E>
typename Graph<V, E>::iterator_dfs Graph<V, E>::begin() { // BEGIN
    typename data_t::iterator Iter_map;
    typename data_t::iterator Iter_map_end;
    map<V, int> map_count;
    Iter_map = g.begin();
    Iter_map_end = g.end();
    for(; Iter_map != Iter_map_end; Iter_map++)
        map_count[Iter_map->first] = 0;
    Iter_map = g.begin();
    iterator_dfs iter(Iter_map, this);
    iter.dfs_init(Iter_map->first, map_count); // push'n'grey
    return iter;
}

template <class V, class E>
typename Graph<V, E>::iterator_dfs Graph<V, E>::end() {
    typename data_t::iterator Iter_map_end;
    Iter_map_end = g.end();
    iterator_dfs iter(Iter_map_end, this);
    return iter;
}

template <class V, class E>
Graph<V, E>::iterator_dfs::iterator_dfs(iterator_dfs const & iter) {
    ps_it = iter.ps_it;
    map_counter = iter.map_counter;
}

template <class V, class E>
void Graph<V, E>::iterator_dfs::operator=(iterator_dfs iter) {
    ps_it = iter.ps_it;
    map_counter = iter.map_counter;
}

template <class V, class E>
V* Graph<V, E>::iterator_dfs::operator->() {
    return (ps_it->);
}

template <class V, class E>
V Graph<V, E>::iterator_dfs::operator*() {
    return (*ps_it);
}

template <class V, class E>
typename Graph<V, E>::iterator_dfs & Graph<V, E>::iterator_dfs::operator++() {
    typename Graph<V, E>::pseudo_iterator iter_end;
    iter_end = ps_it.give_me_end();
    ++ps_it;
    if (ps_it != iter_end) {
        //cout << "SDAF" << endl;
        map_counter[*ps_it]++;
    }
    while (1) {
        if (ps_it != iter_end) {
            //cout << "F" << endl;
            if (map_counter[*ps_it]==2) {
                //cout << "returned" << endl;
                return *this;
            } else {
                //cout << "cycle" << endl;
                ++ps_it;
                if (ps_it != iter_end)
                    map_counter[*ps_it]++;
            }
        } else
            return *this;
    }
    return *this;
}

template <class V, class E>
typename Graph<V, E>::iterator_dfs Graph<V, E>::iterator_dfs::operator++(int) {
    iterator_dfs tmp(*this);
    typename Graph<V, E>::pseudo_iterator iter_end;
    iter_end = ps_it.give_me_end();
    ++ps_it;
    if (ps_it != iter_end) {
        //cout << "SDAF" << endl;
        map_counter[*ps_it]++;
    }
    while (1) {
        if (ps_it != iter_end) {
            //cout << "F" << endl;
            if (map_counter[*ps_it]==2) {
                //cout << "returned" << endl;
                return tmp;
            } else {
                //cout << "cycle" << endl;
                ++ps_it;
                if (ps_it != iter_end)
                    map_counter[*ps_it]++;
            }
        } else
            return tmp;
    }
    return tmp;
}

template <class V, class E>
bool Graph<V, E>::iterator_dfs::operator==(iterator_dfs iter) {
    return (ps_it == iter.ps_it);
}

template <class V, class E>
bool Graph<V, E>::iterator_dfs::operator!=(iterator_dfs iter) {
    return !(ps_it == iter.ps_it);
}