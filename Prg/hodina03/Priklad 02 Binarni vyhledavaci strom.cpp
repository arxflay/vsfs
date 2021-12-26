// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>
#include <sstream>
#include <ctime>
#include "binarytree.hxx"

treeNode *createNode(treeNode *parent, int value)
{
    treeNode *node{ new treeNode{} };
    node->parent = parent;
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}

void traverse(treeNode *node, traverse_cb cb)
{
    if (node->left != nullptr)
        traverse(node->left, cb);
    if (node->right != nullptr)
        traverse(node->right, cb);

    cb(node);
}

void changeParentChild(treeNode *child, treeNode *newChild)
{
    if (child->parent != nullptr)
    {
        if (child->parent->left == child)
            child->parent->left = newChild;
        else if (child->parent->right == child)
            child->parent->right = newChild;
    }
}

void swapChildrenParents(treeNode *from, treeNode *to)
{
    if (to->parent == from)
    {
        changeParentChild(from, to);
        to->parent = from->parent;
        from->parent = to;
    }
    else
    {     
        changeParentChild(from, to);
        changeParentChild(to, from);

        treeNode *temp{ from->parent };
        from->parent = to->parent;
        to->parent = temp;
    }
}

void swap(treeNode *node, treeNode *to)
{
    treeNode *temp{ node->left };
    node->left = to->left;
    if (temp == to)
        to->left = node;
    else
        to->left = temp;

    temp = node->right;
    node->right = to->right;
    if (temp == to)
        to->right = node;
    else
        to->right = temp;

    swapChildrenParents(node, to);

    if (node->left != nullptr)
        node->left->parent = node;
    if (node->right != nullptr)
        node->right->parent = node;

    if (to->left != nullptr)
        to->left->parent = to;
    if (to->right != nullptr)
        to->right->parent = to;
    

}

treeNode *findBiggest(treeNode *node)
{
    if (node != nullptr && node->right != nullptr)
        return findBiggest(node->right);

    return node;
}

treeNode *insert(treeNode *node, int value)
{ 
    if (node != nullptr)
    {
        if (value < node->value)
        {
            if (node->left != nullptr)
                return insert(node->left, value);
            else
            {
                node->left = createNode(node, value);
                return node->left;
            }
        }
        else if (value > node->value)
        {   
            if (node->right != nullptr)
                return insert(node->right, value);
            else
            {
                node->right = createNode(node, value);
                return node->right;
            }
        }
        else
            return node;
    }

    return createNode(nullptr, value);
}


treeNode *convertArray(int *array, int length)
{
    treeNode *tree{ nullptr };

    for (int i{ 0 }; i < length; i++)
    {
        if (i == 0)
            tree = insert(tree, array[i]);
        else
            insert(tree, array[i]);
    }

    return tree;
}

treeNode *findUncle(treeNode *node) //a)
{
    treeNode *uncle{ nullptr };

    if (node->parent != nullptr && node->parent->parent != nullptr)
    {
        treeNode *grandParent{ node->parent->parent };

        if (grandParent->left == node->parent)
            uncle = grandParent->right;
        else
            uncle = grandParent->left;
    }

    return uncle;
}

void writePathRec(treeNode *root, treeNode *node, std::stringstream &strstream, int value) //b)
{
    if (node == nullptr)
    {
        std::cout << "couldn't find node\n";
        return;
    }

    if (node == root)
        strstream << "currentNode[root] -> (" << root->value << ")\n";
    else
        strstream << "currentNode -> (" << node->value << ")\n";

    if(value > node->value)
    {
        strstream << "move to right\n";
        writePathRec(root, node->right, strstream, value);
    }
    else if (value < node->value)
    {
        strstream << "move to left\n";
        writePathRec(root, node->left, strstream, value);
    }
    else
    {
        strstream << "end\n";
        std::cout << strstream.str();
    }
}

void writePath(treeNode *root, treeNode *node, int value) //b)
{
    std::stringstream strstream{};
    writePathRec(root, root, strstream, value);
}

int countNodes(treeNode *node) //c)
{
    if (node == nullptr)
        return 0;

    int count{ 1 };

    if(node->left != nullptr)
        count += countNodes(node->left);
    if(node->right != nullptr)
        count += countNodes(node->right);

    return count;
}



//pointer hell (loop pointers, incorrect swaps), it took 5h (or maybe even more) to get fully working function
treeNode *deleteNode(treeNode *root, treeNode *node, int value) //e) 
{
    if (node == nullptr)
        return root;
    else if (value < node->value)
        return deleteNode(root, node->left, value);
    else if (value > node->value)
        return deleteNode(root, node->right, value);

    treeNode *newRoot{ root };
    
    if (node->left != nullptr && node->right != nullptr)
    {
        treeNode *biggestFromLeft{ findBiggest(node->left) };

        if (newRoot == node)
            newRoot = biggestFromLeft;

        swap(node, biggestFromLeft);

        return deleteNode(newRoot, node, value);
    }
    else if (node->left != nullptr)
    {
        if (newRoot == node)
            newRoot = node->left;

        changeParentChild(node, node->left);
        node->left->parent = node->parent;
    }
    else if (node->right != nullptr)
    {
        if (newRoot == node)
            newRoot = node->right;
            
        changeParentChild(node, node->right);
        node->right->parent = node->parent;
    }
    else
    {
        if (newRoot == node)
            newRoot = nullptr;
        changeParentChild(node, nullptr);
    }
    
    delete node;

    return newRoot;
}

treeNode *deleteAbove(treeNode *root, treeNode *node, int value) //f)
{
    if (node == nullptr)
        return root;

    if (node->value > value) //nebude zkouset levou stranu pokud node->value <= value
        deleteAbove(root, node->left, value);
    deleteAbove(root, node->right, value);
    
    if (node->value > value)
    {
        if (node == root)
            return deleteNode(root, node, node->value);
        else
            deleteNode(root, node, node->value);
    }

    return root;
}

static inline void write_cb(treeNode *node)
{
    std::cout << node->value << ' ';
}

void traverse2(treeNode *node, traverse_cb cb) //g) v kombinaci s write_cb
{
    if (node->left != nullptr)
        traverse2(node->left, cb);

    cb(node);

    if (node->right != nullptr)
        traverse2(node->right, cb);

}

int main()
{
    srand(time(NULL));
    int array[]{ 50, 60, 10, 1, 74, 25, 30, 9, 85, 99, 90, 94, 33, 41, 46, 11, 29, 48, 82, 17 };
    int length{ sizeof(array) / sizeof(int) };
    treeNode *root{ convertArray(array, length) };
    root = deleteNode(root, root, 50);
    root = deleteAbove(root, root, 60);
    
    //traverse(root, write_cb);
    traverse2(root, write_cb);
    traverse(root, destroy_cb);
    return 0;
}