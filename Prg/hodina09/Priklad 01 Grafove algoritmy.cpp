// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include "darray.hxx"

struct graphNode
{
    darray *edges;
    int_fast32_t value;
    size_t edgeCount;
    bool visited;
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

edge *createEdge(int_fast32_t length = 0, graphNode *node = nullptr)
{
    edge *e{ new edge{} };
    e->length = length;
    e->connectedNode = node;

    return e;
}

void createConnection(graphNode *node, graphNode *target, int_fast32_t length = 0)
{
    if (node->edgeCount == node->edges->length)
        expand(node->edges);
    
    node->edges->data[node->edgeCount++] = createEdge(length, target);
}

edge *node_getEdge(graphNode *node, int_fast32_t pos)
{
    return (edge*)node->edges->data[pos];
}

graphNode *node_getConnectedNode(graphNode *node, int_fast32_t pos)
{
    return node_getEdge(node, pos)->connectedNode;
}

graphNode *hasConnectionWith(graphNode *node, graphNode *target)
{
    for (size_t i{ 0 }; i < node->edgeCount; i++)
    {
        edge *e{ node_getEdge(node, i) };

        if (e->connectedNode == target)
            return target;
    }

    return nullptr;
}

graphNode *createNode(int_fast32_t value)
{
    graphNode *node{ new graphNode{} };
    node->value = value;
    node->edges = createDarray(2);
    node->edgeCount = 0;

    return node;
}

void destroyNode(graphNode *node)
{
    for (size_t i{ 0 }; i < node->edgeCount; i++)
        delete node_getEdge(node, i);
    
    destroyDarray(node->edges);
    delete node;
}

graphNode *graph_getNode(graph *g, int_fast32_t pos)
{
    return (graphNode*)(g->nodes->data[pos]);
}

graph *createGraph()
{
    graph *g{ new graph{} };
    g->nodes = createDarray(2);
    g->count = 0;
    
    return g;
}

void destroyGraph(graph *g)
{
    if (g == nullptr)
        return;

    for (size_t i{ 0 }; i < g->count; i++)
        destroyNode(graph_getNode(g, i));

    destroyDarray(g->nodes);

    delete g;
}

void insertNode(graph *g, graphNode *node)
{
    if (g->count == g->nodes->length)
        expand(g->nodes);

    g->nodes->data[g->count++] = node;
}

void insertValue(graph *g, int_fast32_t value)
{
    graphNode *node{ createNode(value) };
    insertNode(g, node);
}

graphNode *findNode(graph *g, int_fast32_t value)
{
    for (size_t i{ 0 }; i < g->count; i++)
    {
        graphNode *node{ graph_getNode(g, i) };

        if (node->value == value)
            return node;
    }

    return nullptr;
}

graph *loadGraph(const std::string &filename) //a)
{
    graph *g{ createGraph() };

    std::ifstream file{};
    file.exceptions(file.badbit | file.failbit);
    file.open(filename);

    std::string line{};

    while(!file.eof())
    {
        std::stringstream strstream{ };
        std::getline(file, line);
        strstream << line;

        int_fast32_t value{ 0 };

        if (!(strstream >> value))
            throw std::runtime_error("ERROR: INCORRECT FORMAT, first value should be an integer");
        else if ((findNode(g, value) != nullptr))
            throw std::runtime_error("ERROR: GRAPH ALREADY HAS NODE WITH VALUE " + std::to_string(value));
        
        insertValue(g, value);
    }

    file.seekg(file.beg);

    std::string arg{};
    int_fast32_t i{ 0 };

    while(!file.eof())
    {
        std::stringstream strstream{ };
        std::getline(file, line);
        graphNode *node{ graph_getNode(g, i) };
        strstream << line;
        strstream >> arg;

        if (!(strstream >> arg))
            throw std::runtime_error("ERROR: INCORRECT FORMAT, line should contain argument");
        else if (arg == "in_relation_with")
        {
            int_fast32_t value{ 0 };

            while(strstream >> value)
            {
                if (node->value == value)
                    throw std::runtime_error("ERROR: GRAPH NODE LOOP");

                graphNode *target{ findNode(g, value) };

                if (target == nullptr)
                    throw std::runtime_error("ERROR: GRAPH NODE WITH VALUE " + std::to_string(value) + " DOESN'T EXIST");
                else if (hasConnectionWith(node, target))
                    throw std::runtime_error("ERROR: GRAPH NODE IS ALREADY CONNECT WITH NODE THAT HAS VALUE " + std::to_string(value));

                createConnection(node, target);
            }
        }
        else if (arg != "empty")
            throw std::runtime_error("ERROR: INVALID ARGUMENT, valid arguments -> empty or in_relation_with");
        
        i++;
    }
    
    file.close();

    return g;
}

void writeAllEdges(graphNode *node, std::ofstream &file)
{
    for (size_t i{ 0 }; i < node->edgeCount; i++)
    {
        edge *e{ node_getEdge(node, i) };

        if (i + 1 == node->edgeCount)
            file << e->connectedNode->value;
        else
            file << e->connectedNode->value << " ";
    }
}

void saveGraph(graph *g, const std::string &filename) //b)
{
    std::ofstream file{};
    file.open(filename);
    
    for (size_t i{ 0 }; i < g->count; i++)
    {
        graphNode *node{ graph_getNode(g, i) };
        file << node->value << " ";

        if (node->edgeCount == 0)
            file << "empty";
        else
        {
            file << "in_relation_with ";
            writeAllEdges(node, file);
        }

        file << '\n';
    }

    file.close();
}

bool hasVisitedEdge(graphNode *node)
{
    for (size_t i{ 0 }; i < node->edgeCount; i++)
    {
        edge *e{ node_getEdge(node, i) };

        if (e->connectedNode->visited == true)
            return true;
    }

    return false;
}

void visit(graphNode *node)
{
    node->visited = true;

    for (size_t i{ 0 }; i < node->edgeCount; i++)
    {
        edge *e{ node_getEdge(node, i) };
        if (e->connectedNode->visited == false)
            visit(e->connectedNode);
    }
}

void clearVisits(graph *g)
{
    for (size_t i{ 0 }; i < g->count; i++)
    {
        graphNode *node{ graph_getNode(g, i) };
        node->visited = false;
    }
}

bool isCoherent(graph *g) //c)
{
    int componentCount{ 0 };

    for (size_t i{ 0 }; i < g->count; i++)
    {
        graphNode *node{ graph_getNode(g, i) };
        bool hasVisitedE{ hasVisitedEdge(node) };

        if (hasVisitedE == false)
            componentCount++;

        visit(node);
    }

    clearVisits(g);

    if (componentCount > 1)
    {
        std::cout << "Graph has " << componentCount << " components" << '\n';
        return false;
    }

    return true;
}

bool findCircle(graphNode *node, graphNode *prev, graphNode *target)
{
    bool found{ false };
    node->visited = true;

    if (prev != target)
    {
        graphNode *ftarget{ hasConnectionWith(node, target) };

        if (ftarget != nullptr)
        {
             std::cout << ftarget->value << "->" << node->value << "->";
             return true;
        }
    }

    for (size_t i{ 0 }; i < node->edgeCount; i++)
    {
        edge *e{ node_getEdge(node, i) };

        if (e->connectedNode->visited == false)
            found = findCircle(e->connectedNode, node, target);

        if (found)
        {
            if (node == target)
                std::cout << node->value << '\n';
            else
                std::cout << node->value << "->";
            break;
        }
    }

    node->visited = false;

    return found;

}

bool hasCircle(graph *g) //d)
{
    bool found{ false };
    for(size_t i{ 0 }; i < g->count; i++)
    {
        graphNode *node{ graph_getNode(g, i) };
        found = findCircle(node, node, node);

        if (found == true)
            break;
    }

    return found;
}

int main()
{
    graph *g{ loadGraph("test.txt") };
    saveGraph(g, "test2.txt");
    std::cout << "is Coherent? " <<  std::boolalpha << isCoherent(g) << '\n';
    std::cout << "has circle? " << hasCircle(g) << '\n';
    destroyGraph(g);
}