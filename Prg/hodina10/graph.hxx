// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#ifndef GRAPH_HXX
#define GRAPH_HXX

#include <cstdint>
#include <string>
#include <fstream>
#include "darray.hxx"

struct graphNode
{
    darray *edges;
    int_fast64_t value;
    size_t edgeCount;
    bool visited;
    uint_least32_t depth;
};

struct edge
{
    int_fast32_t length;
    graphNode *connectedNode;
};

struct graph
{
    darray *nodes;
    size_t count;
};

edge *createEdge(int_fast32_t length = 0, graphNode *node = nullptr);

void createConnection(graphNode *node, graphNode *target, int_fast32_t length = 0);
void createDualConnection(graphNode *node, graphNode *target, int_fast32_t length = 0);
void disconnectLast(graphNode *node);
void disconnectLastDual(graphNode *node, graphNode *target);
edge *node_getEdge(graphNode *node, int_fast32_t pos);
graphNode *node_getConnectedNode(graphNode *node, int_fast32_t pos);
graphNode *hasConnectionWith(graphNode *node, graphNode *target);
graphNode *createNode(int_fast64_t value, uint_least32_t depth = 0);
void destroyNode(graphNode *node);
graphNode *graph_getNode(graph *g, int_fast32_t pos);

graph *createGraph();
void destroyGraph(graph *g);

void insertNode(graph *g, graphNode *node);
void insertValue(graph *g, int_fast64_t value);

graphNode *findNode(graph *g, int_fast64_t value);
graph *loadGraph(const std::string &filename); //a)

void writeAllEdges(graphNode *node, std::ofstream &file);
void saveGraph(graph *g, const std::string &filename); //b)

bool hasVisitedEdge(graphNode *node);
void visit(graphNode *node);
void clearVisits(graph *g);
bool isCoherent(graph *g); //c)

bool findCircle(graphNode *node, graphNode *prev, graphNode *target);
bool hasCircle(graph *g); //d)

#endif