/* 24.07.2015
 * added dynamic array of void pinters
 * */

#ifndef VECTOR
#define VECTOR
typedef struct vfunc vec_functions;
typedef struct p Private; //unacessible struct

typedef struct v {
    Private* unacessable;
    vec_functions* callbacks;
}Vector;

Vector* newVector(int);
typedef void (*_addElement)(Vector*, void*);
typedef void (*_setElement)(Vector*, int, void*);
typedef void* (*_getElement)(Vector*, int);



typedef struct vfunc {
    _addElement addElement;
    _setElement setElement;
    _getElement getElement;
} vec_functions;

#endif // VECTOR

