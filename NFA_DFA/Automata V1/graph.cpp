#include "graph.h"

void buildGraph(FA dfa)
{
    Graph g;
    map<vector<string>, vertex_t> vertices;
    for (auto &it : dfa.states)
    {
        vertices.insert({it, add_vertex(Vertex{it}, g)});
    }
    for (auto &pair : dfa.transition_table)
    {
        add_edge(vertices[pair.first.first], vertices[pair.second], Edge{pair.first.second}, g);
    }

    ofstream fout("graph.dot");

    // Write the graph in Graphviz format to the file
    write_graphviz(
        fout, g,
        [&](auto &out, auto v)
        {

            // out << "[label=\"" << g[v].label << "\"]";
            bool isAccepted = false;
            bool isInitial = false;
            for(auto states: dfa.accept)
            {
                vector<string> l;
                for (int i = 0; i < g[v].label.size(); i++)
                    l.push_back(g[v].label[i]);
                if(states == l)
                {
                    isAccepted = true;
                    break;
                }
            }

            for(auto s: g[v].label)
            {
                if(s == "&") {
                   isInitial = true;
                    break;
                }
            }
            if(!isInitial)
            {
                out << " [label=\"[";
                out << g[v].label[0];
                for (int i = 1; i < g[v].label.size(); i++)
                    out << "," << g[v].label[i];
                out << "]\"";
                if(isAccepted)
                    out << " shape=doublecircle]";
                else
                    out << "]";
            }
            else
            {
                out << "[label=\"\" shape=point]";
            }
        },
        [&](auto &out, auto e)
        {
            if(g[e].weight != "&")
                out << "[label=\"" << g[e].weight << "\"]";
        });

    // Close the file
    fout.close();

    QProcess process;
    QStringList arguments;
    arguments << "-Tpng" << "graph.dot" << "-o" << "graph.png";
    process.start("dot", arguments);

    // Wait for the process to finish and read its output
    process.waitForFinished();
}








