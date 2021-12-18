// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#ifndef LINKEDLIST_HXX
#define LINKEDLIST_HXX

#include <ostream>

struct listNode
{
    listNode *next;
    int value;
};

struct linkedList
{
    listNode *first;
    listNode *last;
    int count;
};

linkedList *linkedListCreate();
void linkedListDestroy(linkedList *list);

void pushNode(linkedList *list, listNode *node);
void push(linkedList *list, int value);
void removeNode(linkedList *list, listNode *node, listNode *prev);
int shift(linkedList *list);
void swapNodes(linkedList *list, listNode *cur, listNode *prev, listNode *next, listNode *nextPrev);

void saveList(linkedList *list, const std::string& filename); //a)
linkedList *loadList(const std::string& filename);            //b)
int countOccurences(linkedList *list, int val);               //c)
void removeLastMatch(linkedList *list, int val);              //d)
void removeHeighiest(linkedList *list);                       //e)
void reverse(linkedList *list);                               //f)
void sort(linkedList *list);                                  //g)
void swapFirstLast(linkedList *list);                         //h)
void swapSecondPenultimate(linkedList *list);                 //i)

linkedList *convertArray(int *array, int length);

std::ostream& operator<< (std::ostream& out, linkedList *list);

#endif