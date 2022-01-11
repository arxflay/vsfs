// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>
#include <string>
#include <cstring>
#include "queue.hxx"
#include "stack.hxx"

struct btreeNode
{
    btreeNode *left;
    btreeNode *right;
    std::string value;
    bool visited;
};

btreeNode *createNode(std::string value)
{
    btreeNode *node{ new btreeNode{} };
    node->left = nullptr;
    node->right = nullptr;
    node->visited = false;
    node->value = value;

    return node;
}

btreeNode *insert(btreeNode *node, const std::string &value)
{
    if (node != nullptr)
    {
        int cmp{ strcmp(value.c_str(), node->value.c_str()) };

        if (cmp <= 0)
        {
            if (node->left != nullptr)
                insert(node->left, value);
            else
                node->left = createNode(value);
            
            return node->left;
        }
        else
        {
            if (node->right != nullptr)
                insert(node->right, value);
            else
                node->right = createNode(value);
            
            return node->right;
        }
    }

    return createNode(value);
}


void destroyTree(btreeNode *node)
{
    if (node->left != nullptr)
        destroyTree(node->left);
    if (node->right != nullptr)
        destroyTree(node->right);

    delete node;
}

void writeSorted(btreeNode *node) //c)
{
    if (node == nullptr)
        return;

    stack *nodes{ createStack() };

    btreeNode *cur{ node };
    while(cur != nullptr)
    {
        if (cur->visited || (cur->left == nullptr && cur->right == nullptr))
            std::cout << cur->value << ' ';
        else
        {           
            if (cur->left != nullptr)
                stackPush(nodes, cur->left);

            stackPush(nodes, cur);

            if (cur->right != nullptr)
                stackPush(nodes, cur->right);
        
            cur->visited = true;
        }

        cur = (btreeNode*)stackPop(nodes);
    }

    destroyStack(nodes);
}

void writeByDepth(btreeNode *node) //d)
{
    if (node == nullptr)
        return;
        
    queue *q{ createQueue() };
    enqueue(q, node);
    int count = 1;
    int depth = 0;

    while(count != 0)
    {
        btreeNode *cur{ nullptr };

        for (int i { 0 }; i < count; i++)
        {
            cur = (btreeNode*)dequeue(q);

            if (cur->left != nullptr)
                enqueue(q, (void*)cur->left);

            std::cout << '"' << cur->value << "\" vzdalenost: " << depth << '\n';

            if (cur->right != nullptr)
                enqueue(q, (void*)cur->right);

        }

        count = q->count;
        depth++;
    }

    destroyQueue(q);
}

int main()
{
    btreeNode *root{ insert(nullptr, "test") };
    insert(root, "axel");
    insert(root, "verbtim");
    insert(root, "bx");
    insert(root, "lynx");
    insert(root, "verbtim202");
    insert(root, "a");
    insert(root, "vixel");
    insert(root, "ds");
    insert(root, "triv");
    writeByDepth(root);

    destroyTree(root);

    return 0;
}