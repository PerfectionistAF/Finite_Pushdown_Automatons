#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <QProcess>
#include <QStringList>
#include "utility.h"
#include "pda.h"
#include <fstream>

using namespace boost;

struct Edge {
    string weight;
};

struct Edge_PDA {
    vector<string> weight;
};

struct Vertex {
    vector<string> label;
};

struct Vertex_PDA {
    vector<string> label;
};


typedef adjacency_list<vecS, vecS, directedS, Vertex, Edge> Graph;
typedef adjacency_list<vecS, vecS, directedS, Vertex_PDA, Edge_PDA> GraphPDA;

using vertex_t = graph_traits<Graph>::vertex_descriptor;
using edge_t   = graph_traits<Graph>::edge_descriptor;

using vertex_t_PDA = graph_traits<GraphPDA>::vertex_descriptor;
using edge_t_PDA   = graph_traits<GraphPDA>::edge_descriptor;

void buildGraph(FA);
void buildPDA(PDA);
void addEdge(vector<string>,vector<string>,string,Graph&);

#endif // GRAPH_H
