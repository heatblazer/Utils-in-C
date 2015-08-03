#include <stdlib.h>
#include "vector.h"
#include <stdio.h>


typedef struct p  {
    int capacity;
    int size;
    void** data;
} Private;


static void doubleAmountIfFull(Vector* v) {
    printf("Double amount if full\n");
    if ( v->unacessable->size == v->unacessable->capacity ) {
        v->unacessable->capacity = v->unacessable->capacity * 2;
        v->unacessable->data = (void**) realloc
                (v->unacessable->data,
                 sizeof(void*) * v->unacessable->capacity);
        if ( !v ) return;
    }
}


static void __addElement(Vector *v, void *d) {
    doubleAmountIfFull(v);
    v->unacessable->data[v->unacessable->size] =  d;
    v->unacessable->size+=1;
}


static void __setElement(Vector *v, int index, void *d) {
    if ( index < v->unacessable->capacity ||
         index > v->unacessable->capacity) {
        return;
    } else {
        v->unacessable->data[index] = d;
    }
}

static void* __getElement(Vector *v, int index) {
    if ( index < 0 ||
         index > v->unacessable->capacity ) {
        return 0x00;
    } else {
        return v->unacessable->data[index];
    }
}


Vector* newVector(int capacity) {
    Vector* v = (Vector*) malloc(sizeof(Vector));
    v->unacessable = (Private*) malloc(sizeof(Private));
    v->unacessable->capacity = capacity;
    v->unacessable->size = 0;
    v->unacessable->data = (void**) malloc(sizeof(void*)*capacity);
    v->callbacks = (vec_functions*) malloc(sizeof(vec_functions));
    v->callbacks->addElement = __addElement;
    v->callbacks->getElement = __getElement;
    v->callbacks->setElement = __setElement;
    if ( !v || ! v->callbacks || !v->unacessable) return 0x00;

    return v;
}


