// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>
#include <limits>
#include "graph.hxx"
#include "quicksort.hxx"

void initDijkstra(graph *g, size_t startPos)
{
    for (size_t i{ 0 }; i < g->count; i++)
    {
        if (i == startPos)
            continue;

        graphNode *node{ graph_getNode(g, i) };
        node->distance = std::numeric_limits<uint_fast64_t>::max();
    }
}

void doDijkstra(graphNode **nodes, size_t right)
{
    size_t len{ right };

    while(len > 0)
    {
        graphNode *node{ nodes[0] };
        node->visited = true;

        for (size_t i{ 0 }; i < node->edgeCount; i++)
        {
            edge *e{ node_getEdge(node, i) };
            graphNode *connNode{ e->connectedNode };

            if (connNode->visited)
                continue;

            uint_fast64_t newDistance{ node->distance + e->length };
        
            if (newDistance < connNode->distance)
                connNode->distance = newDistance;
        }

        std::swap(nodes[0], nodes[len]);
        len--;

        quicksort(nodes, len);
    }
}

void dijkstra(graph *g, size_t startPos)
{
    if (startPos >= g->count)
        return;

    initDijkstra(g, startPos);

    graphNode *startNode{ graph_getNode(g, startPos) };
    graphNode *firstNode{ graph_getNode(g, 0) };

    startNode->distance = 0;

    graphNode **copy{ new graphNode*[g->count] };
    std::copy((graphNode**)g->nodes->data, (graphNode**)g->nodes->data + g->count, copy);

    if (startPos != 0)
        std::swap(startNode, firstNode);

    doDijkstra(copy, g->count - 1);

    delete[] copy;
}

int main()
{
    return 0;
}