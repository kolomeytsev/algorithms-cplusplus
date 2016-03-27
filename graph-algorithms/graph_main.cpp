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