#ifndef DLIST_H
#define DLIST_H
#include "LNode.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
//#include "SimpleGUI.h"
void setListIndex(int);
int getListIndex();
struct SimpleGUI;

typedef struct DList {
    int size;
    LNode* head;
    LNode* tail;
} DList;

typedef void* (*_universalFunction)(void*, void*);

typedef void* (*_doSomething)(LNode*);
typedef void (*_doCrypt)(const char*, const char*, char* );
void* cryptFileAndWriteBack(LNode*);
void cryptFile(LNode*);
LNode* deleteNode(LNode *node) ;

void freeList(DList* list);
DList *createList(const char* message);

void addFront(const char* data, DList* list);
void addBack(const char* data, DList* list);

void popFront2(DList*); //OK
LNode* popFront(DList*);
LNode *popBack(DList*);

LNode* deleteNode(LNode* node);
void* printList(DList* list);
void* unlinkFile(LNode* list);
void* deleteFileFromList(LNode* list);
void* printFileFromList(LNode* list);
char* getNodeData(LNode* );
/*ver. 1 */
void forEach(DList* list, _doSomething doit);

/*ver. 2 for GUI progressbar */
void forEachCrypt(DList* list, _doCrypt cryptit);

void deleteElement(DList*, const char*);

/* new added to retrieve all elements comma separated to be
 * splitted by Utils.split(...)
 * */
char** elementsAsStrings(DList*);
char* toString(DList*) ;
int getElementsInList(DList*);
#endif // DLIST_H
