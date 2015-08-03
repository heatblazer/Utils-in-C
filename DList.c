#include "LOGFILES.h"
#include "DList.h"
#include "LNode.h"
/* this will be used in forEach() 
 * to signalize to the reference of 
 * the GUI class that a change has 
 * happened so progrss bar will update! */

/******************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* this will be set to max No of elements,
 * then it will decrease on successful finish of
 * a specific function, the result will be reported
 * to SimpleGUI class so progressbar will update
 * */
static int __indexForProgressBar = 0;

void setListIndex(int i) { __indexForProgressBar == 0? 0 : i; }
int getListIndex() { return __indexForProgressBar ; }

/* this is index for node counting
IMPORTANT: not to get it messed with index for
the progress bar!!!
*/
static int _index;
#define DECREASE() _index--
//static FILE* filetolog = NULL;

DList* createList(const char* message) {
    DList* dl =  (DList*)malloc(sizeof(DList));
    dl->head = dl->tail = NULL;
    printf("List created at %p; message:[%s]\n", dl, message);
    if ( dl != NULL ) return dl;
    else return NULL;
}
LNode* popBack(DList *list) {
    LNode* copy = (LNode*) malloc(sizeof(LNode));
    if ( list->head == NULL) return NULL;
    copy->data = strdup(list->tail->data);
    copy->index = list->tail->index;
    copy->next = NULL;
    /* need to add logic for prev and next too */
    deleteNode(list->tail);
    return copy;
}
void popFront2(DList* list) {
    LNode* t = list->head->next;
    free(list->head->data);
    free(list->head);
    list->head = t;
}

LNode* popFront(DList* list) {
    LNode* copy = (LNode*) malloc(sizeof(LNode));
    if ( list->head == NULL ) return NULL;
    copy->data = strdup(list->head->data);
    copy->index = list->head->index;
    copy->next = NULL;
    LNode* tempHead = list->head->next;
    deleteNode(list->head);
    list->head = tempHead;
    return copy;
}

void addBack(const char *data, DList *list) {
    LNode* tmp = NULL;
    if ( list->head == NULL ) {
        tmp = (LNode*) malloc(sizeof(LNode));
        tmp->data = strdup(data);
        tmp->index = _index++;
        tmp->next = list->tail;
        list->head->next =  tmp;
        list->head = tmp = list->tail;

       // printf("#%s %p\n", list->tail->prev->data, list->tail->prev);
    } else {
        tmp = (LNode*) malloc(sizeof(LNode));
        tmp->data = strdup(data);
        tmp->index = _index++;
        tmp->next = NULL;
        list->tail->next = tmp;
        list->tail = tmp;
    }
}


void addFront(const char *data, DList* list) {
    LNode *tmp = NULL;
    if ( list->head == NULL ) {
        tmp = (LNode*) malloc(sizeof(LNode));
        tmp->data = (char*) malloc(strlen(data)+1);
        tmp->data = strdup(data);
        tmp->index = _index++;
        tmp->next = list->head ;
        list->head = list->tail = tmp;
    } else {
        tmp = (LNode*)malloc(sizeof(LNode));
        tmp->data = (char*) malloc(strlen(data)+1);
        tmp->data = strdup(data);
       // *tmp->data++ = '\0'; //I`ll add this as reminder because it`s a bad error
        tmp->index = _index++;
        tmp->next = list->head;
        list->head = tmp;
    }
}


void* printList(DList *list) {
    FILE* fp = fopen(LOG_getLogName(NORMAL), "a+");
    LNode* tmp = list->head;
    while ( tmp ) {
        fprintf(fp, "[%s][%d]\n", tmp->data, tmp->index);
        tmp = tmp->next;
    }
    fclose(fp);
}

void freeList(DList* list) {
    while ( list->head != NULL ) {
        LNode* removed = list->head;
        list->head = list->head->next;
        if ( removed->data ) free(removed->data);
        free(removed);
    }
    _index = 0;
}
LNode* deleteNode(LNode *node) {
    LNode* tmp = node;
    if ( tmp) {
        if ( tmp->data ) free(tmp->data);
        free(tmp);
       _index--;
    }
    if ( node->next != NULL)
    return node->next;
}
/* to be used as callbacks */
//[3] - this works
void* cryptFileAndWriteBack(LNode* node) {
    Utils.copyOverwriteFileWithCryptOption(node->data,
                                           Utils.getKey(), 2);
}
char* getNodeData(LNode* n) {
    return n->data;
}

void* printFileFromList(LNode *list) {

    fprintf(stdout, "[%s][%d]\n", list->data, list->index);
}
/* delete file or dir from list */
void* unlinkFile(LNode* list) {
    if ( list->data) {
        if ( Utils.charAt(list->data, strlen(list->data)-1) == '/')  {
          // rmdir(list->data);
            remove(list->data);
        } else {
        //    unlink(list->data);
            remove(list->data);
        }
    }
}

/*IMPORTANT - add a parameter to signalize the 
 * GUI that a value has changed, then add a SIGNAL/SLOT
 * mechanism to monitor the change. Variable to function? */

void forEach(DList* list, _doSomething doit) {
    LNode* h = list->head;
    while ( h ) {
        doit(h);
        h = h->next;
        setListIndex(getListIndex()-1);
    }
}
/* for qt applications */




void copyFiles(LNode* data) {

}
//[deprecated]
/*
void cryptFile(LNode* data) {
    static int i=0;
    char* string = (char*) malloc(sizeof(char) * strlen(data->data) +2);
    strcpy(string, data->data);
    strcat(string, "a");
    encrypt(data->data, string, "shitz");
    free(string);
}
*/
void deleteElement(DList* list, const char* data) {

 /*TODO implement */
}

/* added 04/10/2014 - working
 * returns a similar to argv** to main
 * to pass elements in main() look a like
 * functions */
char** elementsAsStrings(DList* list) {
    int i = 0;
    LNode* walker1 = list->head;
    LNode* walker2 = list->head;
    while ( walker1 != NULL ) {
        i++;
        walker1 =  walker1->next;
    }
    int j=0;
    char** retstr = (char**) malloc(sizeof(char*)*i+1);
    /* why +1 works?, index at 0? debug later */

    while ( walker2 ) {
        printf("[elementsAsStrings()] %s\n", walker2->data);
        retstr[j++] = strdup(walker2->data);
        walker2 = walker2->next;
    }
    j=0;
    while ( j < i ) {
        printf("[elementsAsStrings()]: %s\n", retstr[j++]);
    }
    return retstr;
}
/* added 04/09/2014 - working still need a
 * split function */
char* toString(DList *l) {
    LNode* walker = l->head;
    int size=0;
    int elements = 0;
    while ( walker != NULL ) {
        size = size +  strlen(walker->data);
        elements++;
        walker = walker->next;
    }
    fprintf(stdout, "[toString()] size: %d\n", size+elements+1);
    char* retstr = (char*) malloc(sizeof(char) * size+elements+(elements/2));
    retstr[0] = '\0';
    LNode* walker2 = l->head;
    LNode* begin = walker2;
    while ( walker2 != NULL ) {
        strcat(retstr, walker2->data);
        strcat(retstr, ",");
        walker2 = walker2->next;
    }
    return retstr;
}

int getElementsInList(DList *l) {
    int size =0;
    LNode* walker = l->head;
    while ( walker != NULL ) {
        walker = walker->next;
        size++;
    }
    return size;
}
