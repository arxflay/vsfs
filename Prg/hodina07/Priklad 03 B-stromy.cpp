// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <cstddef>
#include <iostream>
#include "quicksort.hxx"

struct btreeNode
{
    int m;
    int childCount;
    int keysCount;
    int *keys;
    btreeNode *parent;
    btreeNode **children;
};

using traverse_cb = void(*)(btreeNode*);

int minKeyCount(size_t m)
{
    if (m == 0)
        return 0;

    return (m - 1) / 2;
}

btreeNode *createNode(int m, btreeNode *parent = nullptr)
{
    if (m < 3)
    {
        std::cerr << "ERROR: parameter m must heighier than 2" << '\n';
        return nullptr;
    }

    btreeNode *node{ new btreeNode{} };
    node->m = m;
    node->parent = parent;
    node->childCount = 0;
    node->keysCount = 0;
    node->children = new btreeNode*[m]{ nullptr };
    node->keys = new int[m - 1]{ 0 };

    return node;
}

btreeNode *createNode(size_t m, int value)
{
    btreeNode *node{ createNode(m) };
    node->keys[0] = value;
    node->keysCount++;

    return node;
}

void traverse(btreeNode *node, traverse_cb cb)
{
    for (int i{ 0 }; i < node->childCount; i++)
        traverse(node->children[i], cb);

    cb(node);
}

void destroyNode(btreeNode *node)
{
    delete[] node->children;
    delete[] node->keys;
    delete node;
}

void write_cb(btreeNode *node)
{
    for (int i{ 0 }; i < node->keysCount; i++)
        std::cout << node->keys[i] << ' ';
}

void pushKey(btreeNode *node, int value)
{
    node->keys[node->keysCount++] = value;
}

void pushChild(btreeNode *node, btreeNode *child)
{
    node->children[node->childCount++] = child;
}

void insertChild(btreeNode *node, btreeNode *child, int childPos)
{
    pushChild(node, child);

    for (int j{ node->childCount - 1 }; j > childPos; j--)
        std::swap(node->children[j], node->children[j - 1]);
}

bool isLeaf(btreeNode *node)
{
    return node->childCount == 0;
}

bool isRoot(btreeNode *node)
{
    return node->parent == nullptr;
}

bool validKeyCount(btreeNode *node)
{
    return node->keysCount >= minKeyCount(node->m) && ((isLeaf(node)) || (node->keysCount == node->childCount - 1));
}

bool validChildCount(btreeNode *node)
{
    return isLeaf(node) || node->childCount <= node->m;
}

bool test(btreeNode *node) //a)
{   
    if (!isRoot(node) && (!validKeyCount(node) || !validChildCount(node)))
        return false;

    for (int i{ 0 }; i < node->childCount; i++)
    {
        bool result = false;
        result = test(node->children[i]);

        if (!result)
            return result;
    }

    return true;
}

btreeNode *find(btreeNode *node, int val) //b)
{
    if (node == nullptr)
        return nullptr;

    for (int key{ 0 }, child{ 0 }; key < node->keysCount; key++, child++)
    {
        if (node->keys[key] == val)
            break;
        else if (node->keys[key] > val)
            return find(node->children[child], val);
        else if (key + 1 == node->keysCount)
            return find(node->children[child + 1], val);
    }

    return node;
}

int findKeyPos(btreeNode *node, int value)
{
    int key{ 0 };

    for (; key < node->keysCount; key++)
        if (node->keys[key] == value)
            break;
    
    return key;
}

int findChildPos(btreeNode *node)
{
    if (node == nullptr)
        return 0;

    btreeNode *parent{ node->parent };

    if (parent == nullptr)
        return 0;

    int childPos{ 0 };

    for (; childPos < parent->childCount; childPos++)
        if (parent->children[childPos] == node)
            break;

    return childPos;
}

//insertion part

void insertKey(btreeNode *node, int value);
void split(btreeNode *node, int value, btreeNode *overflowChild);

void push(btreeNode *node, btreeNode *left, btreeNode *right, int value, int index, int mid, int &midValue)
{
    if (index < mid)
        pushKey(left, value);
    else if (index == mid)
        midValue = value;
    else
        pushKey(right, value);
}

void splitChildren(btreeNode *original, btreeNode *left, btreeNode *right, btreeNode *overflowChild)
{
    int i{ 0 };
    for (; i < left->keysCount + 1; i++)
    {
        original->children[i]->parent = left;
        pushChild(left, original->children[i]);
    }

    for (int j{ 0 }; j < right->keysCount; j++)
    {
        original->children[i + j]->parent = right;
        pushChild(right, original->children[i + j]);
    }

    overflowChild->parent = right;
    pushChild(right, overflowChild);
}

void rootSplit(btreeNode *node, btreeNode *left, btreeNode *right, int midValue, btreeNode *overflowChild)
{
    node->keys[0] = midValue;
    node->keysCount = 1;

    left->parent = node;
    right->parent = node;
        
    if (node->childCount != 0)
    {
        splitChildren(node, left, right, overflowChild);
        node->childCount = 0;
    }

    pushChild(node, left);
    pushChild(node, right);
}

//workaround with overflowChild
void nodeSplit(btreeNode *node, btreeNode *left, btreeNode *right, int midValue, btreeNode *overflowChild)
{
    btreeNode *parent{ node->parent };
    left->parent = parent;
    right->parent = parent;

    if (node->childCount > 0)
        splitChildren(node, left, right, overflowChild);

    int i{ 0 };
    for (; i < parent->childCount; i++)
    {
        if (parent->children[i] == node)
        {
            parent->children[i] = left;
            destroyNode(node);
            break;
        }
    }

    btreeNode *newOverflowChild{ nullptr }; //used if after addition parent will have more children than order M

    if (parent->childCount + 1 > parent->m)
        newOverflowChild = right;

    if (i + 1 != parent->childCount) //i + 1 = next child
    {
        if (newOverflowChild != nullptr)
        {
            newOverflowChild = parent->children[parent->childCount - 1];
            parent->childCount--;
        }

        insertChild(parent, right, i + 1);
    }
    else
        if (newOverflowChild == nullptr)
            pushChild(parent, right);

    if (newOverflowChild != nullptr)
        split(parent, midValue, newOverflowChild);
    else
        insertKey(parent, midValue);
}

//probably overcomplicated 
void split(btreeNode *node, int value, btreeNode *overflowChild = nullptr)
{
    int newElPos{ 0 };

    for (newElPos = 0; newElPos < node->keysCount; newElPos++)
        if (node->keys[newElPos] > value)
            break;
    
    int mid{ node->m / 2 };
    btreeNode *left{ createNode(node->m) };
    btreeNode *right{ createNode(node->m) };
    int midValue{ 0 };
    char offset{ 0 };

    for (int i{ 0 }; i < node->keysCount || offset == 0; i++)
    {
        if (i + offset == newElPos)
        {
            push(node, left, right, value, i, mid, midValue);
            offset = 1;
            i--;
        }
        else
            push(node, left, right, node->keys[i], i + offset, mid, midValue);
    }

    if (node->parent == nullptr)
        rootSplit(node, left, right, midValue, overflowChild);
    else 
        nodeSplit(node, left, right, midValue, overflowChild);
}

void insertKey(btreeNode *node, int value)
{
    if (node->keysCount == node->m - 1)
        split(node, value);
    else
    {
        pushKey(node, value);
        quicksort(node->keys, node->keysCount - 1);
    }
}

void insert(btreeNode *node, int value) //c)
{
    if (node == nullptr)
        return;
    else if (isLeaf(node))
        insertKey(node, value);
    else
    {
        for (int key{ 0 }, child{ 0 }; key < node->keysCount; key++, child++)
        {
            if (node->keys[key] > value)
            {
                insert(node->children[child], value);
                break;
            }
            else if (key + 1 == node->keysCount)
            {
                insert(node->children[child + 1], value);
                break;
            }
        }
    }
}


//deletion part

void merge(btreeNode *node, btreeNode *parent, int childPos);
void rearrange(btreeNode *node);
void btreeDelete(btreeNode *root, int value);

void shiftChildren(btreeNode *node, int childPos)
{
    for (int i{ childPos }; i < node->childCount - 1; i++)
        node->children[i] = node->children[i + 1];
    
    node->childCount--;
}

void shiftKeys(btreeNode *node, int keyPos)
{
    for (int i{ keyPos }; i < node->keysCount - 1; i++)
        node->keys[i] = node->keys[i + 1];
    
    node->keysCount--;
}

btreeNode *findImmidiateSibling(btreeNode *node, int &siblingPos, int minCount, int childPos)
{
    btreeNode *parent{ node->parent };
    btreeNode **parentChildren{ parent->children };
    btreeNode *succesor{ nullptr };

    if (childPos - 1 >= 0 && parentChildren[childPos - 1]->keysCount - 1 >= minCount)
    {
        succesor = parentChildren[childPos - 1];
        siblingPos = childPos - 1;
    }
    else if (childPos + 1 < parent->childCount && parentChildren[childPos + 1]->keysCount - 1 >= minCount)
    {
        succesor = parentChildren[childPos + 1];
        siblingPos = childPos + 1;
    }

    return succesor;
}

void borrowKeyFromNodeSibling(btreeNode *node, btreeNode *sibling, btreeNode *parent, int siblingPos, int childPos)
{
    int newKey{ 0 };
    btreeNode *child{ nullptr };

    if (siblingPos > childPos)
    {
        newKey = parent->keys[childPos];
        parent->keys[childPos] = sibling->keys[0];
        child = sibling->children[0];
        shiftKeys(sibling, 0);
        shiftChildren(sibling, 0);
    }
    else //siblingPos < childPos
    {
        newKey = parent->keys[siblingPos];
        parent->keys[siblingPos] = sibling->keys[--sibling->keysCount];
        child = sibling->children[--sibling->childCount];
    }

    child->parent = node;
    node->keys[node->keysCount++] = newKey;
    quicksort(node->keys, node->keysCount - 1);
    int newKeyPos{ findKeyPos(node, newKey) };
    insertChild(node, child, newKeyPos + 1);
}

void rearrange(btreeNode *node)
{
    if (!isRoot(node))
    {
        int minCount = minKeyCount(node->m);
        int childPos{ findChildPos(node) };
        int siblingPos{ 0 };
        btreeNode *parent{ node->parent };
        btreeNode *sibling{ findImmidiateSibling(node, siblingPos, minCount, childPos) };
        
        if (sibling != nullptr)
            borrowKeyFromNodeSibling(node, sibling, parent, siblingPos, childPos);
        else
        {
            merge(node, parent, childPos);
            destroyNode(node);
        }
    }
    else
    {
        btreeNode *child{ node->children[--node->childCount] };

        for (int i{ 0 }; i < child->keysCount; i++)
            pushKey(node, child->keys[i]);
        
        for (int i{ 0 }; i < child->childCount; i++)
        {
            child->children[i]->parent = node;
            pushChild(node, child->children[i]);
        }

        destroyNode(child);
    }
}

void merge(btreeNode *node, btreeNode *parent, int childPos)
{
    btreeNode *mergedNode{ nullptr };
    int parentKey{ 0 };

    if (childPos > 0)
    {
        mergedNode = parent->children[childPos - 1];
        parentKey = parent->keys[childPos - 1];
        shiftKeys(parent, childPos - 1);

        if (!isLeaf(node))
            for (int i{ 0 }; i < node->childCount; i++)
                pushChild(mergedNode, node->children[i]);
    }
    else
    {
        mergedNode = parent->children[childPos + 1];
        parentKey = parent->keys[0];
        shiftKeys(parent, 0);

        if (!isLeaf(node))
            for (int i{ 0 }; i < node->childCount; i++)
                insertChild(mergedNode, node->children[i], i);
    }

    for (int i{ 0 }; i < node->keysCount; i++)
        pushKey(mergedNode, node->keys[i]);
        
    pushKey(mergedNode, parentKey);
    quicksort(mergedNode->keys, mergedNode->keysCount - 1);
    shiftChildren(parent, childPos);

    if ((!isRoot(parent) && parent->keysCount < minKeyCount(parent->m)) || (parent->keysCount < 1))
        rearrange(parent);
}

void borrowKeyFromLeafSibling(btreeNode *leaf, btreeNode *sibling, btreeNode *parent, int siblingPos, int childPos)
{
    int newKey{ 0 };

    if (siblingPos > childPos)
    {
        newKey = parent->keys[childPos];
        parent->keys[childPos] = sibling->keys[0];
        shiftKeys(sibling, 0);
    }
    else //siblingPos < childPos
    {
        newKey = parent->keys[siblingPos];
        parent->keys[siblingPos] = sibling->keys[--sibling->keysCount];
    }
    
    leaf->keys[leaf->keysCount - 1] = newKey;
    quicksort(leaf->keys, leaf->keysCount - 1);
}

void deleteLeafKey(btreeNode *leaf, int keyPos)
{
    int minCount{ minKeyCount(leaf->m) };

    if (leaf->keysCount - 1 >= minCount)
        shiftKeys(leaf, keyPos);
    else
    {
        int childPos{ findChildPos(leaf) };
        int siblingPos{ 0 };
        btreeNode *parent{ leaf->parent };
        btreeNode *sibling{ findImmidiateSibling(leaf, siblingPos, minCount, childPos) };

        if (sibling != nullptr)
            borrowKeyFromLeafSibling(leaf, sibling, parent, siblingPos, childPos);
        else
        {
            shiftKeys(leaf, keyPos);
            merge(leaf, parent, childPos);
            destroyNode(leaf);
        }
    }
}

btreeNode *findPredecessor(btreeNode *node)
{
    if (!isLeaf(node))
        return findPredecessor(node->children[node->childCount - 1]);
    
    return node;
}

void deleteNodeKey(btreeNode *node, int keyPos)
{
    int oldkey{ node->keys[keyPos] };
    btreeNode *predecessor{ findPredecessor(node->children[keyPos]) };
    node->keys[keyPos] = predecessor->keys[predecessor->keysCount - 1];
    predecessor->keys[predecessor->keysCount - 1] = oldkey;
    btreeDelete(predecessor, oldkey);
}

void btreeDelete(btreeNode *root, int value) //d)
{
    btreeNode *node{ find(root, value) };

    if (node != nullptr)
    {
        int keyPos{ findKeyPos(node, value) };

        if (isLeaf(node))
            deleteLeafKey(node, keyPos);
        else
            deleteNodeKey(node, keyPos);
    }

}

int main()
{
    int arr[]{ 29, 6, 10, 1, 8, 25, 0, 48, 11, 33, 22, 54, 4, 45, 19, 59, 7, 2, 9};
    size_t length{ sizeof(arr) / sizeof(int) };
    btreeNode *root{ createNode(4, 5) };

    for (size_t i{ 0 }; i < length; i++)
        insert(root, arr[i]);

    btreeDelete(root, 5);
    btreeDelete(root, 4);
    btreeDelete(root, 2);
    btreeDelete(root, 6);
    btreeDelete(root, 7);
    btreeDelete(root, 0);
    btreeDelete(root, 1);
    btreeDelete(root, 10);
    btreeDelete(root, 9);
    btreeDelete(root, 11);
    btreeDelete(root, 8);
    btreeDelete(root, 19);
    
    std::cout << std::boolalpha << test(root) << '\n';

    traverse(root, destroyNode);

    return 0;
}
