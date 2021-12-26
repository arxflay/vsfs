// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#ifndef BINARYTREE_HXX
#define BINARYTREE_HXX

#include <sstream>

struct treeNode
{
    treeNode *left;
    treeNode *right;
    treeNode *parent;
    int value;
};

using traverse_cb = void(*)(treeNode*);
treeNode *createNode(treeNode *parent, int value);
void traverse(treeNode *node, traverse_cb cb);
treeNode *convertArray(int *array, int length);

treeNode *findUncle(treeNode *node); //a)

void writePathRec(treeNode *root, treeNode *node, std::stringstream &strstream, int value);
void writePath(treeNode *root, treeNode *node, int value); //b)

int countNodes(treeNode *node); //c)
treeNode *insert(treeNode *node, int value); //d)

void changeParentChild(treeNode *child, treeNode *newChild);
treeNode *findBiggest(treeNode *node);
void swapChildrenParents(treeNode *from, treeNode *to);
void swap(treeNode *node, treeNode *to);
treeNode *deleteNode(treeNode *root, treeNode *node, int value); //e)

treeNode *deleteAbove(treeNode *root, treeNode *node, int value); //f
void traverse2(treeNode *node, traverse_cb cb); //g) v kombinaci s write_cb

static inline void destroy_cb(treeNode *node) 
{
    delete node;
}

#endif