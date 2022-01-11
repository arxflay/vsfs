// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>

struct treeNode
{
    treeNode *left;
    treeNode *right;
    int repetitionCount;
    std::string word;
};

using traverse_cb = void(*)(treeNode*);

treeNode *createNode(const std::string &word)
{
    treeNode *node{ new treeNode{} };
    node->repetitionCount = 1;
    node->word = word;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}

treeNode *createNode(const std::string &word, int repetitionCount)
{
    treeNode *node{ new treeNode{} };
    node->repetitionCount = repetitionCount;
    node->word = word;
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

void traverseDesc(treeNode *node, traverse_cb cb)
{
    if (node->right != nullptr)
        traverse(node->right, cb);

    cb(node);

    if (node->left != nullptr)
        traverse(node->left, cb);
}

static inline void destroy_cb(treeNode *node) 
{
    delete node;
}

treeNode *insert(treeNode *node, const std::string &word)
{
    if (node != nullptr)
    {
        int cmp{ strcmp(word.c_str(), node->word.c_str()) };

        if (cmp < 0)
        {
            if (node->left != nullptr)
                insert(node->left, word);
            else
                node->left = createNode(word);
            
            return node->left;
        }
        else if (cmp > 0)
        {
            if (node->right != nullptr)
                insert(node->right, word);
            else
                node->right = createNode(word);
            
            return node->right;
        }
        else
        {
            node->repetitionCount++;
            return node;
        }
    }

    return createNode(word);
}

treeNode *insertByRepetition(treeNode *node, const std::string &word, int repetitionCount)
{
    if (node != nullptr)
    {
        if (repetitionCount < node->repetitionCount)
        {
            if (node->left != nullptr)
                insertByRepetition(node->left, word, repetitionCount);
            else
                node->left = createNode(word, repetitionCount);
            
            return node->left;
        }
        else if (repetitionCount > node->repetitionCount)
        {
            if (node->right != nullptr)
                insertByRepetition(node->right, word, repetitionCount);
            else
                node->right = createNode(word, repetitionCount);
            
            return node->right;
        }
        else
        {
            node->word += ", " + word;
            return node;
        }
    }

    return createNode(word, repetitionCount);
}

void createRepetitionTree(treeNode *node, treeNode **repeationTree)
{
    if (node->left != nullptr)
        createRepetitionTree(node->left, repeationTree);

    if (*repeationTree == nullptr)
        *repeationTree = insertByRepetition(nullptr, node->word, node->repetitionCount);
    else
        insertByRepetition(*repeationTree, node->word, node->repetitionCount);

    if (node->right != nullptr)
        createRepetitionTree(node->right, repeationTree);  
}

static inline void write_cb(treeNode *node)
{  
    std::cout << "Pocet vyskytu " << node->repetitionCount << ": " << node->word << '\n';
}

void mostCommonWords(const std::string &file)
{
    std::ifstream istr;
    std::stringstream strstream;
    istr.exceptions(istr.failbit | istr.badbit);

    istr.open(file);
    strstream << istr.rdbuf();
    istr.close();
    
    std::string word{ };
    treeNode *tree{ nullptr };
    treeNode *repeationTree{ nullptr };

    while(strstream >> word)
    {
        if (tree == nullptr)
            tree = insert(nullptr, word);
        else
            insert(tree, word);
    }

    if (tree != nullptr)
    {
        createRepetitionTree(tree, &repeationTree);
        traverseDesc(repeationTree, write_cb);    
        traverse(tree, destroy_cb);
        traverse(repeationTree, destroy_cb);
    }

}

int main()
{
    mostCommonWords("test.txt");
    return 0;
}


