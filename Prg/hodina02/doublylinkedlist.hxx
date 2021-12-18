// Tento zdrojovy kod jsem vypracoval zcela samostatne bez cizi pomoci
// Neokopiroval jsem ani neopsal jsem cizi zdrojove kody
// Nikdo mi pri vypracovani neradil
// Pokud nektery radek porusuje toto pravidlo je oznacen komentarem
// NENI MOJE TVORBA
// Poruseni techto pravidel se povazuje za podvod, ktery lze potrestat VYLOUCENIM ZE STUDIA
// Alexej Fedorenko, učo 37676 

#ifndef DOUBLY_LINKED_LIST_HXX
#define DOUBLY_LINKED_LIST_HXX

#include <ostream>

struct listNode
{
    listNode *next;
    listNode *prev;
    int value;
};

struct doublyLinkedList
{
    listNode *first;
    listNode *last;
    int count;
};

doublyLinkedList *doublyLinkedListCreate();
void doublyLinkedListDestroy(doublyLinkedList *list);
doublyLinkedList *convertArray(int *array, int length);
std::ostream& operator<< (std::ostream& out, doublyLinkedList *list);

void removeNode(doublyLinkedList *list, listNode *node);
void swapNodes(doublyLinkedList *list, listNode *cur, listNode *next);

void pushNode(doublyLinkedList *list, listNode *node);
void push(doublyLinkedList *list, int value);

int shift(doublyLinkedList *list);

void deleteAll(doublyLinkedList *list, int val) ;   //a)
void reverse(doublyLinkedList *list);               //b)
void sort(doublyLinkedList *list);                  //c)
void swapFirstLast(doublyLinkedList *list);         //d)
void swapSecondPenultimate(doublyLinkedList *list); //e)


#endif