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

int_fast32_t findSmallest(graph *g, int_fast32_t lastSmallest)
{
    int_fast32_t smallest{ -1 };

    for(size_t i{ 0 }; i < g->count; i++)
    {
        graphNode *node{ graph_getNode(g, i) };

        for (size_t j{ 0 }; j < node->edgeCount; j++)
        {
            edge *e{ node_getEdge(node, j) };

            if ((e->length > lastSmallest && (smallest == -1 || e->length < smallest)))
                smallest = e->length;
        }
    }

    return smallest;
}

void addEdgesToSkeleton(graphNode *node, graphNode *skeletonNode, graph *skeleton, int_fast32_t validLength)
{
    for (size_t i{ 0 }; i < node->edgeCount; i++)
    {
        edge *e{ node_getEdge(node, i) };

        if (e->length == validLength)
        {
            int_fast64_t value{ e->connectedNode->value };
            graphNode *newConnection{ findNode(skeleton, value) };

            if (hasConnectionWith(skeletonNode, newConnection) != nullptr)
                return;

            createDualConnection(skeletonNode, newConnection, e->length);

            if (hasCircle(skeleton))
                disconnectLastDual(skeletonNode, newConnection);

        }
    }
}

graph *findSkeleton(graph *g) //a)
{
    if (g->count == 0)
        return nullptr;

    graph *skeleton{ createGraph() };
    int_fast32_t length{ -1 };

    for (size_t i{ 0 }; i < g->count; i++)
    {
        graphNode *node{ graph_getNode(g, i) };
        insertValue(skeleton, node->value);
    }

    while ((length = findSmallest(g, length)) != -1)
    {
        for (size_t i{ 0 }; i < g->count; i++)
        {
            graphNode *node{ graph_getNode(g, i) };
            graphNode *skeletonNode{ graph_getNode(skeleton, i) };

            addEdgesToSkeleton(node, skeletonNode, skeleton, length);
        }
    }

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
                createDualConnection(node, rightNode, rand() % 10);
            }

            if (i > 0)
            {
                graphNode *upperNode{ graph_getNode(g, (i - 1) * l + j) };
                createDualConnection(node, upperNode, rand() % 10);
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

void writeRow(graph *g, size_t l, size_t offset, std::ofstream &file)
{
    for (size_t j{ 0 }; j < l; j++)
    {
        if (j == l - 1)
            file << 'x' << '\n';
        else
        {
            graphNode *node{ graph_getNode(g, offset * l + j) }; 
            int_fast32_t length{ 0 };

            if (j == 0)
                length = node_getEdge(node, 0)->length;
            else
                length = node_getEdge(node, 1)->length;

            file << "x-" << length << '-';
        }
    }
}

void writeBottomEdges(graph *g, size_t l, size_t offset, std::ofstream &file)
{
    for (size_t j{ 0 }; j < 3; j++)
    {
        for (size_t k{ 0 }; k < l; k++)
        {
            graphNode *node{ graph_getNode(g, offset * l + k) };

            if (j == 1)
            {
                int_fast32_t length{ node_getEdge(node, node->edgeCount - 1)->length };

                if (k == l - 1)
                    file << length << '\n';
                else
                    file << length << "   ";
            }
            else if (k == l - 1)
                file << "|" << '\n';
            else
                file << "|   ";
        }
    }
}

void saveRectGraph(graph *g, const std::string& filename) //c)
{
    std::ofstream file{};
    file.open(filename);

    size_t l{ findL(g) };
    size_t k{ g->count / l };

    for (size_t i{ 0 }; i < k; i++)
    {
        writeRow(g, l, i, file);

        if (i != k - 1)
            writeBottomEdges(g, l, i, file);
    }

    file.close();
}

int main()
{
    srand(time(NULL));
    graph *g{ createRectGraph(5, 4) };
    graph *z{ findSkeleton(g) };
    saveRectGraph(g, "test.txt");

    destroyGraph(g);
    destroyGraph(z);
    return 0;
}