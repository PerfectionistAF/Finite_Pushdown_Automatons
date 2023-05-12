#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <QProcess>
#include <QStringList>
#include "utility.h"
#include <fstream>
using namespace boost;

struct Edge {
    string weight;
};
struct Vertex {
    vector<string> label;
};

typedef adjacency_list<vecS, vecS, directedS, Vertex, Edge> Graph;
using vertex_t = graph_traits<Graph>::vertex_descriptor;
using edge_t   = graph_traits<Graph>::edge_descriptor;

void buildGraph(FA);
#endif // GRAPH_H
