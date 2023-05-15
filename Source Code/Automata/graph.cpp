#include "graph.h"
#include "pda.h"

void buildGraph(FA dfa)
{
    Graph g;
    bool color = false;
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
            if(!color) {
                out << "bgcolor=\"transparent\"";
                color = true;
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


void buildPDA(PDA pda)
{
    GraphPDA g;
    bool isColored = false;
    map<vector<string>, vertex_t_PDA> vertices;
    for (auto it : pda.states)
    {
        vertices.insert({{it}, add_vertex(Vertex_PDA{{it}}, g) });
    }
    for (auto pair : pda.transitionTable)
    {
        for(auto st: pair.second)
            add_edge(vertices[pair.first.first], vertices[{st}], Edge_PDA{pair.first.second}, g);
    }

    ofstream fout("graph.dot");

    // Write the graph in Graphviz format to the file
    write_graphviz(
        fout, g, [&](auto &out, auto v)
        {
            out << " [label=\"";

            if(g[v].label[0] == "qAccept")
            {
                out << g[v].label[0];
                out << "\" shape=doublecircle]";
            }
            else if(g[v].label[0] == "&")
            {
                out << "\" shape=point]";
            }
            else
            {
                out << g[v].label[0] << "\"]";
            }
            if(!isColored)
            {
                isColored = true;
                out << "bgcolor=\"transparent\"";
            }
        },
        [&](auto &out, auto e)
        {
            for (int i = 0; i < g[e].weight.size(); i++)
            {
                if(i == 0) out << " [label=\"[";
                out << g[e].weight[i];
                if(i < g[e].weight.size()-1)
                out << ",";
            }
            out << "]\"]";
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


void addEdge(vector<string> src, vector<string> dest, string symbol, Graph &g)
{
    bool isColored = false;
    static map<vector<string>, vertex_t> vertices;



    if(vertices.find(src) == vertices.end())
        vertices.insert({src, add_vertex(Vertex{src}, g)});
    if(vertices.find(dest) == vertices.end())
        vertices.insert({dest, add_vertex(Vertex{dest}, g)});
    add_edge(vertices[src], vertices[dest], Edge{symbol}, g);

    ofstream fout("graph.dot");

    write_graphviz(
        fout, g, [&](auto &out, auto v)
        {

            out << "[label=\""<< g[v].label.front() << "\"]";

            if(!isColored)
            {
                isColored = true;
                out << "bgcolor=\"transparent\"";
            }
        },
        [&](auto &out, auto e)
        {
            out << "[label=\""<< g[e].weight << "\"]";
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









