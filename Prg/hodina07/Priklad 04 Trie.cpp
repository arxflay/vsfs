// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 


#include <iostream>
#include <sstream>
#include "darray.hxx"

struct trieNode
{
    darray *children;
    int childCount;
    char value;
};

using traverse_cb = void(*)(trieNode*);

trieNode *getChild(trieNode *node, int childPos)
{
    return (trieNode*)(node->children->data[childPos]);
}

void traverse(trieNode *node, traverse_cb cb)
{
    for (int i { 0 }; i < node->childCount; i++)
        traverse(getChild(node, i), cb);

    cb(node);
}

void destroy_cb(trieNode *node)
{
    destroyDarray(node->children);
    delete node;
}

void write_cb(trieNode *node)
{
    std::cout << node->value << ' ';
}

bool isFull(trieNode *node)
{
    return node->childCount == static_cast<int>(node->children->length);
}

trieNode *createNode(char value)
{
    trieNode *node{ new trieNode{} };
    node->children = createDarray(2);
    node->value = value;
    node->childCount = 0;

    return node;
}

bool findRec(trieNode *node,  const std::string &value, size_t valuePos)
{
    if (valuePos == value.length())
        return true;

    for (int i{ 0 }; i < node->childCount; i++)
        if (getChild(node, i)->value == value[valuePos])
            return findRec(getChild(node , i), value, valuePos + 1);

    return false;
}

bool find(trieNode *root, const std::string &value)
{
    std::string word{};
    std::stringstream words {};
    words << value;

    while(words >> word)
        if (findRec(root, word, 0) == false)
            return false;

    return true;
}

void insertRec(trieNode *node, const std::string &value, size_t valuePos) //b)
{
    if (valuePos == value.length())
        return;

    for (int i{ 0 }; i < node->childCount; i++)
    {
        if (getChild(node, i)->value == value[valuePos])
        {
            insertRec(getChild(node , i), value, valuePos + 1);
            return;
        }
    }

    //if child with this value doesn't exist
    
    if (isFull(node))
        expand(node->children);

    node->children->data[node->childCount] = createNode(value[valuePos]);
    insertRec(getChild(node, node->childCount), value, valuePos + 1);
    node->childCount++;
    
}

void insert(trieNode *root, const std::string &value) //b)
{
    std::string word{};
    std::stringstream words {};
    words << value;

    while(words >> word)
        insertRec(root, word, 0);
}

void shiftChildren(trieNode *node, int childPos)
{
    for (int i{ childPos }; i < node->childCount - 1; i++)
        node->children->data[i] = node->children->data[i + 1];
    
    node->childCount--;
}

bool deleteValueRec(trieNode *node, const std::string &value, size_t valuePos)
{
    if (valuePos == value.length())
        return true;

    bool result{ false };
    
    for (int i{ 0 }; i < node->childCount; i++)
    {
        trieNode *child{ getChild(node , i) };

        if (child->value == value[valuePos])
        {
            result = deleteValueRec(getChild(node , i), value, valuePos + 1);

            if (result == true && child->childCount == 0)
            {
                shiftChildren(node, i);
                destroy_cb(child);
            }

            break;
        } 
    }

    return result;
}

void deleteValue(trieNode *root, const std::string &value) //b)
{
    std::string word{};
    std::stringstream words {};
    words << value;

    while(words >> word)
        deleteValueRec(root, word, 0);
}

int main()
{
    std::string strings[]{ "retrospective", "programming", "bear", "beer", "linux", "witchcraft", "negation", "negotiation", "salt", "bottle", "phone", "notepad", "mythril", "joke", "behavior", "stone", "rock", "calculator", "canister", "almond" };
    size_t len{ sizeof(strings) / sizeof(std::string) };
    trieNode *root{ createNode('\0') };
    for (size_t i{ 0 }; i < len; i++)
        insert(root, strings[i]);

    std::cout << std::boolalpha << find(root, "rocks") << '\n'; // false
    std::cout << std::boolalpha << find(root, "rock") << '\n'; // true
    std::cout << std::boolalpha << find(root, "roc") << '\n'; // true
    std::cout << std::boolalpha << find(root, "bear beer") << '\n';

    deleteValue(root, "retrospectiv"); // nothing removed
    deleteValue(root, "retrospective"); // etrospective removed, r is still here because we have word "rock"
        
    traverse(root, destroy_cb);
    
}