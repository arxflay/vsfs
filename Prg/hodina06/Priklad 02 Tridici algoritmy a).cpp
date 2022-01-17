// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>
#include <cstdlib>
#include <ctime>

void writeArray(int *array, int length)
{
    for (int i{ 0 }; i < length; i++)
        std::cout << array[i] << ' ';
        
    std::cout << '\n';
}

struct heapNode
{
    heapNode *parent;
    heapNode *left;
    heapNode *right;
    int value;
};

heapNode *createNode(int value, heapNode *parent)
{
    heapNode *node{ new heapNode{} };
    node->left = nullptr;
    node->right = nullptr;
    node->value = value;
    node->parent = parent;

    return node;
}

int minDepth(heapNode *node, int depth)
{
    if (node == nullptr)
        return depth - 1;
    else if (node->left == nullptr || node->right == nullptr)
        return depth;

    return std::min(minDepth(node->left, depth + 1), minDepth(node->right, depth + 1));
}

int maxDepth(heapNode *node, int depth)
{
    if (node == nullptr)
        return depth - 1;
    else if (node->left == nullptr && node->right == nullptr)
        return depth;

    return std::max(maxDepth(node->left, depth + 1), maxDepth(node->right, depth + 1));
}


void changeParentChild(heapNode *child, heapNode *newChild)
{
    if (child->parent != nullptr)
    {
        if (child->parent->left == child)
            child->parent->left = newChild;
        else if (child->parent->right == child)
            child->parent->right = newChild;
    }
}

void swapChildrenParents(heapNode *from, heapNode *to)
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

        heapNode *temp{ from->parent };
        from->parent = to->parent;
        to->parent = temp;
    }
}

void swap(heapNode *node, heapNode *to)
{
    heapNode *temp{ node->left };
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

heapNode *insertRec(heapNode *node, int value)
{
    if (minDepth(node->left, 0) <= minDepth(node->right, 0))
    {
        if (node->left != nullptr)
            return insertRec(node->left, value);
        else
        {
            node->left = createNode(value, node);
            return node->left;           
        }
    }
    else
    {
        if (node->right != nullptr)
            return insertRec(node->right, value);
        else
        {
            node->right = createNode(value, node);
            return node->right;
        }
    }

    return node;
}

void siftUp(heapNode *node, heapNode **root)
{ 
    while(node->parent != nullptr)
    {
        if (node->value < node->parent->value)
        {
            if (node->parent == *root)
                *root = node;

            swap(node->parent, node);
        }
        else
            break;
    }
}

heapNode *insert(heapNode *root, int value)
{
    if (root == nullptr)
        return createNode(value, nullptr);

    heapNode *node{ insertRec(root, value) };
    siftUp(node, &root);

    return root;
}

heapNode *arrToHeapTree(int *arr, int right)
{
    heapNode *root{ createNode(arr[0], nullptr) };

    for (int i = 1; i <= right; i++)
        root = insert(root, arr[i]);

    return root;
}

heapNode *reheap(heapNode *root)
{
    heapNode *newRoot{ root };
    heapNode *l{ root->left };
    heapNode *r{ root->right };

    while(l != nullptr)
    {
        if (r != nullptr && r->value < root->value && r->value < l->value)
        {
            if (newRoot == root)
                newRoot = r;
            
            swap(root, r);
        }
        else if (l->value < root->value)
        {
            if (newRoot == root)
                newRoot = l;
            
            swap(root, l);
        }
        else
            break;
        
        l = root->left;
        r = root->right;
    }

    return newRoot;
}

heapNode *removeRoot(heapNode *root, int &rootVal)
{
    rootVal = root->value;
    heapNode *node{ root };

    while(true)
    {
        if (node->left != nullptr)
        {
            if (node->right == nullptr || maxDepth(node->left, 0) > maxDepth(node->right, 0))
                node = node->left;
            else
                node = node->right;
        }
        else
            break;
    }

    swap(root, node);

    if (root->parent != nullptr)
    {
        if (root->parent->left == root)
            root->parent->left = nullptr;
        else
            root->parent->right = nullptr;
    }

    delete root;

    return node;
}

static inline void write_cb(heapNode *node)
{
    std::cout << node->value << ' ';
}

void heapsort(int *arr, int right)
{
    if (right <= 0)
        return;

    heapNode *root{ arrToHeapTree(arr, right) };
    int last{ right };
    int val{ 0 };

    while(last >= 0)
    {
        root = removeRoot(root, val);
        root = reheap(root);
        arr[last--] = val;
    }

}

int main()
{
    srand(time(NULL));
    int array[15]{ };
    constexpr int length{ sizeof(array) / sizeof(int) };

    for (int i{ 0 }; i < length; i++)
        array[i] = rand() % 2555;

    std::cout << "original array:   ";
    writeArray(array, length);

    heapsort(array, length - 1);
    std::cout << "heapsorted array: ";
    writeArray(array, length);
    
    return 0;
}