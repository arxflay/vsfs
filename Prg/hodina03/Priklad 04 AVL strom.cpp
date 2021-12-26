// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>

struct AVLtreeNode
{
    AVLtreeNode *left;
    AVLtreeNode *right;
    int value;
    int balancedFactor;
};

AVLtreeNode *createNode(int val)
{
    AVLtreeNode *node{ new AVLtreeNode{}};
    node->balancedFactor = 0;
    node->left = nullptr;
    node->right = nullptr;
    node->value = val;

    return node;
}

AVLtreeNode *findUnbalancedNode(AVLtreeNode *node, AVLtreeNode **parent)
{
    if (node->balancedFactor > 1 || node->balancedFactor < -1)
        return node;

    AVLtreeNode *unbalancedNode{ nullptr };

    if (node->left != nullptr)
        unbalancedNode = findUnbalancedNode(node->left, parent);
    if (unbalancedNode == nullptr && node->right != nullptr)
        unbalancedNode = findUnbalancedNode(node->right, parent);
    
    if (unbalancedNode != nullptr && *parent == nullptr)
        *parent = node;
    
    return unbalancedNode;
}

int getHeigth(AVLtreeNode *node, int heigth)
{
    if (node == nullptr)
        return heigth - 1;
    
    if (node->left != nullptr && node->right != nullptr)
        return std::max(getHeigth(node->left, heigth + 1), getHeigth(node->right, heigth + 1));
    else if (node->left != nullptr)
        return getHeigth(node->left, heigth + 1);
    else if (node->right != nullptr)
        return getHeigth(node->right, heigth + 1);

    return heigth;
}

int bf(int rightHeigth, int leftHeigth)
{
    return rightHeigth - leftHeigth;
}

void recalculateBF(AVLtreeNode *node)
{
    node->balancedFactor = bf(getHeigth(node->right, 1), getHeigth(node->left, 1));
}

void recalculateBFsRec(AVLtreeNode *node, int heigth, int maxHeigth)
{
    if (node == nullptr || heigth == maxHeigth)
        return;

    recalculateBF(node);

    if (heigth + 1 >= maxHeigth)
        return;

    if (node->left != nullptr)
        recalculateBFsRec(node->left, heigth + 1, maxHeigth);
    if (node->right != nullptr)
        recalculateBFsRec(node->right, heigth, maxHeigth);
}

void recalculateBFs(AVLtreeNode *root, AVLtreeNode *endNode)
{
    if (root == nullptr || endNode == nullptr)
        return;

    int heigthFromRoot{ 0 };
    int heigthEndNode{ getHeigth(endNode, 0) };
    int maxHeigth{ 0 };

    recalculateBF(root);

    if (root->value > endNode->value)
    {
        heigthFromRoot = getHeigth(root->left, 1);
        maxHeigth = heigthFromRoot - heigthEndNode;
        recalculateBFsRec(root->left, 1, maxHeigth);
    }
    else
    {
        heigthFromRoot = getHeigth(root->right, 1);
        maxHeigth = heigthFromRoot - heigthEndNode;
        recalculateBFsRec(root->left, 1, maxHeigth);
    }
    
}

void swapParentChild(AVLtreeNode *parent, AVLtreeNode *child, AVLtreeNode *newChild)
{
    if (parent->left == child)
        parent->left = newChild;
    else if (parent->right == child)
        parent->right = newChild;
}

AVLtreeNode *rrRotation(AVLtreeNode *node, AVLtreeNode *parent)
{
    AVLtreeNode *newParent { node->right };
    node->right = newParent->left;
    newParent->left = node;

    if (parent != nullptr)
        swapParentChild(parent, node, newParent);
        
    recalculateBF(newParent);
    recalculateBF(node);

    return newParent;
}

AVLtreeNode *llRotation(AVLtreeNode *node, AVLtreeNode *parent)
{
    AVLtreeNode *newParent { node->left };
    node->left = newParent->right;
    newParent->right = node;

    if (parent != nullptr)
        swapParentChild(parent, node, newParent);

    recalculateBF(newParent);
    recalculateBF(node);

    return newParent;

}

AVLtreeNode *rlRotation(AVLtreeNode *node, AVLtreeNode *parent)
{
    node->right = llRotation(node->right, node);
    return rrRotation(node, parent);
}

AVLtreeNode *lrRotation(AVLtreeNode *node, AVLtreeNode *parent)
{
    node->left = rrRotation(node->left, node);
    return llRotation(node, parent);
}

AVLtreeNode *balance(AVLtreeNode *root)
{
    AVLtreeNode *newRoot{ root };
    AVLtreeNode *unbalancedNode{ nullptr };
    AVLtreeNode *parent{ nullptr };

    while((unbalancedNode = findUnbalancedNode(newRoot, &parent)) != nullptr)
    {
        AVLtreeNode *newNode{ nullptr };
        if (unbalancedNode->balancedFactor > 1)
        {
            if (unbalancedNode->right->balancedFactor >= 0)
                newNode = rrRotation(unbalancedNode, parent);
            else
                newNode = rlRotation(unbalancedNode, parent);
        }
        else
        {
            if (unbalancedNode->left->balancedFactor <= 0)
                newNode = llRotation(unbalancedNode, parent);
            else
                newNode = lrRotation(unbalancedNode, parent);
        }

        if (unbalancedNode == newRoot)
            newRoot = newNode;
        else
            recalculateBFs(newRoot, newNode);

        parent = nullptr;
    }
    return newRoot;
}

int insertRec(AVLtreeNode *node, int val, int heigth, bool &isHeigthChanged)
{
    int childHeigth{ heigth + 1 };

    if (val > node->value)
    {
        int leftHeigth{ getHeigth(node->left, heigth + 1) };
        if (node->right != nullptr)
            childHeigth = insertRec(node->right, val, heigth + 1, isHeigthChanged);
        else
            node->right = createNode(val);
        
        node->balancedFactor = bf(childHeigth, leftHeigth);

        if (childHeigth > leftHeigth)
            isHeigthChanged = true;
    }
    else if (val < node->value)
    {
        int rightHeigth{ getHeigth(node->right, heigth + 1) };
        if (node->left != nullptr)
            childHeigth = insertRec(node->left, val, heigth + 1, isHeigthChanged);
        else
            node->left = createNode(val);

        node->balancedFactor = bf(rightHeigth, childHeigth);

        if (childHeigth > rightHeigth)
            isHeigthChanged = true;
    }
  
    return childHeigth;
}

AVLtreeNode *insert(AVLtreeNode *root, int val)
{
    if (root == nullptr)
        return createNode(val);

    bool isHeigthChanged = false;

    insertRec(root, val, 0, isHeigthChanged);
    if (isHeigthChanged)
        return balance(root);
    
    return root;
}

void destroyTree(AVLtreeNode *node)
{
    if (node->left != nullptr)
        destroyTree(node->left);
    if (node->right != nullptr)
        destroyTree(node->right);

    delete node;
    
}

int main()
{
    //multiple unbalanced nodes
    AVLtreeNode *root{ insert(nullptr, 5) };
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 2);
    root = insert(root, 6);
    root = insert(root, 4);
    root = insert(root, 8);
    root = insert(root, 1);
    root = insert(root, 0);
    destroyTree(root);

    //rrRotation
    root = insert(nullptr, 4);
    root = insert(root, 5);
    root = insert(root, 7);
    
    //llRotation
    root = insert(root, 2);
    root = insert(root, 1);
    destroyTree(root);

    //lrRotation
    root = insert(nullptr, 6);
    root = insert(root, 2);
    root = insert(root, 7);
    root = insert(root, 4);
    root = insert(root, 3);
    destroyTree(root);

    //rlRotation
    root = insert(nullptr, 3);
    root = insert(root, 2);
    root = insert(root, 7);
    root = insert(root, 4);
    root = insert(root, 5);
    destroyTree(root);
    return 0;
}

