// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <string>
#include <iostream>
#include <cstdlib>
#include "darray.hxx"
#include "stack.hxx"

struct treeNode
{
    std::string value;
    darray *children;
};

using traverse_cb = void(*)(treeNode*);

bool isFull(treeNode *node)
{
    if (node == nullptr)
        return false;

    size_t count{ 0 };
    
    for (size_t i{ 0 }; i < node->children->length; i++)
        if (node->children->data[i] != nullptr)
            count++;
    
    if (count == node->children->length)
        return true;
    
    return false;
}

bool hasChild(treeNode *node)
{
    if (node == nullptr)
        return false;
    
    for (size_t i{ 0 }; i < node->children->length; i++)
        if (node->children->data[i] != nullptr)
            return true;

    return false;
}

void destroy_cb(treeNode *node)
{
    destroyDarray(node->children);
    delete node;
}

void write_cb(treeNode *node)
{
    std::cout << node->value << ' ';
}


treeNode *createNode(const std::string &value, size_t length)
{
    treeNode *node{ new treeNode{} };

    if (length > 0)
        node->children = createDarray(length);
    else
        node->children = createDarray(1);

    node->value = value;

    return node;
}

treeNode *insert(treeNode *root, const std::string &value, size_t length = 1)
{
    treeNode *node{ createNode(value, length) };
    if (root == nullptr)
        return node;
    
    if (isFull(root))
    {
        size_t oldLength{ root->children->length };
        expand(root->children);
        root->children->data[oldLength] = node;
    }
    else
    {
        for (size_t i{ 0 }; i < root->children->length; i++)
        {
            if (root->children->data[i] == nullptr)
            {
                root->children->data[i] = node;
                break;
            }
        }
    }

    return node; 
}

void traverse(treeNode *node, traverse_cb cb)
{
    for (size_t i { 0 }; i < node->children->length; i++)
        if (node->children->data[i] != nullptr)
            traverse((treeNode*)node->children->data[i], cb);

    cb(node);
}

treeNode *removeLeafsRec(treeNode *node) //a)
{
    if (!hasChild(node))
    {
        destroy_cb(node);
        return nullptr;
    }

    for (size_t i { 0 }; i < node->children->length; i++)
        if (node->children->data[i] != nullptr)
            node->children->data[i] = removeLeafsRec((treeNode*)node->children->data[i]);

    return node;
}

void findAndClear(treeNode *node, treeNode *el)
{
    for (size_t i{ 0 }; i < node->children->length; i++)
    {
        if (node->children->data[i] == el)
        {
            node->children->data[i] = nullptr;
            break;
        }
    }
}

void removeLeafs(treeNode *node) //b)
{
    stack *children{ createStack() };
    stack *parents{ createStack() };
    treeNode *cur{ node };
    treeNode *parent{ nullptr };

    while(cur != nullptr)
    {
        if (!hasChild(cur))
        {
            if (parent == nullptr)
                return;
            
            findAndClear(parent, cur);
            destroy_cb(cur);
        }
        else
        {
            for (size_t i{ 0 }; i < cur->children->length; i++)
            {
                if (cur->children->data[i] != nullptr)
                {
                    stackPush(children, cur->children->data[i]);
                    stackPush(parents, cur);
                }
            }
        }

        parent = (treeNode*)stackPop(parents);
        cur = (treeNode*)stackPop(children);
    }
    
    destroyStack(children);
    destroyStack(parents);
}

int main()
{
    treeNode *root{ insert(nullptr, "a", 1) };
    insert(root, "b");
    insert(root, "c");
    insert((treeNode*)root->children->data[1], "z");
    insert((treeNode*)root->children->data[1], "e");
    insert((treeNode*)((treeNode*)(root->children->data[1]))->children->data[1], "f");
    insert((treeNode*)root->children->data[1], "x");
    insert(root, "d");

    removeLeafs(root);
    traverse(root, write_cb);
    traverse(root, destroy_cb);
    
    return 0;
} 