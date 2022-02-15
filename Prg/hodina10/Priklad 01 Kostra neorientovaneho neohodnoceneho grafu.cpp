// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <limits>
#include <iostream>
#include <fstream>
#include "graph.hxx"

void graphRecSkeleton(graphNode *node, graph *skeleton, graphNode *skeletonNode)
{
    node->visited = true;

    for (size_t i{ 0 }; i < node->edgeCount; i++)
    {
        edge *e{ node_getEdge(node, i) };
        graphNode *connectedNode{ e->connectedNode };

        if (!connectedNode->visited)
        {
            graphNode *newSkeletonNode{ createNode(connectedNode->value, connectedNode->depth) };
            insertNode(skeleton, newSkeletonNode);   

            createConnection(skeletonNode, newSkeletonNode);
            createConnection(newSkeletonNode, skeletonNode);

            graphRecSkeleton(connectedNode, skeleton, newSkeletonNode);
        }
    }

}

graph *findGraphSkeleton(graph *g) //a)
{
    if (g == nullptr || !isCoherent(g) || g->count <= 1)
        return nullptr;

    graph *skeleton{ createGraph() };
    graphNode *firstNode{  graph_getNode(g, 0) };
    graphNode *skeletonNode{ createNode(firstNode->value) };
    insertNode(skeleton, skeletonNode);

    graphRecSkeleton(graph_getNode(g, 0), skeleton, skeletonNode);
    clearVisits(g);

    return skeleton;
}

graph *createRectGraph(size_t k, size_t l) //b)
{
    if (k == 0 || l == 0)
        throw std::runtime_error("parameter k or l is equal to zero");

    graph *g{ createGraph() };

    int_fast64_t value{ std::numeric_limits<int_fast64_t>::min() };

    for (size_t i{ 0 }; i < k * l; i++)
    {
        graphNode *node{ createNode(value++, i / l) };
        insertNode(g, node);
    }

    for (size_t i{ 0 }; i < k; i++)
    {
        for (size_t j{ 0 }; j < l; j++)
        {
            graphNode *node{ graph_getNode(g, i * l + j) };

            if (j + 1 != l)
            {
                graphNode *rightNode{ graph_getNode(g, i * l + (j + 1)) };
                createDualConnection(node, rightNode);
            }

            if (i > 0)
            {
                graphNode *upperNode{ graph_getNode(g, (i - 1) * l + j) };
                createDualConnection(node, upperNode);
            }
        }
    }

    return g;
}

size_t findL(graph *g)
{
    if (g->count == 0)
        return 0;

    size_t l{ 1 };
    graphNode *prev{ graph_getNode(g, 0) };

    for (;l < g->count; l++)
    {
        graphNode *node{ graph_getNode(g, l) };

        if (prev->depth != node->depth)
            break;

        prev = node;
    }

    return l;
}

void writeRow(graph *g, size_t l, std::ofstream &file)
{
    for (size_t j{ 0 }; j < l; j++)
    {
        if (j == l - 1)
            file << 'x' << '\n';
        else
            file << "x---";
    }
}

void writeBottomEdges(graph *g, size_t l, size_t k, std::ofstream &file)
{
    for (size_t j{ 0 }; j < 3; j++)
    {
        for (size_t k{ 0 }; k < l; k++)
        {
            if (k == l - 1)
                file << "|" << '\n';
            else
                file << "|   ";
        }
    }
}

void saveRectGraph(graph *g, const std::string& filename) //c)
{
    if (g->count == 0)
        return;

    std::ofstream file{};
    file.open(filename);
    size_t l{ findL(g) };
    size_t k{ g->count / l };

    for (size_t i{ 0 }; i < k; i++)
    {
        writeRow(g, l, file);

        if (i != k - 1)
            writeBottomEdges(g, l, k, file);
    }

    file.close();
}

int main()
{
    graph *g{ createRectGraph(1, 4) };
    saveRectGraph(g, "test.txt");

    graph *skeleton{ findGraphSkeleton(g) };
    std::cout << hasCircle(skeleton) << '\n';

    destroyGraph(g);
    destroyGraph(skeleton);

    return 0;
}