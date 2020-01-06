#ifndef __HELPER__
#define __HELPER__

#include <iostream>
#include <string>
#include <vector>
#include "ast.hh"

std::string type2str(PrimitiveType type);

std::string op2str(int op);

template <typename T>
void delVec(std::vector<T*> *vec) {
    if (vec == NULL) return;
    for (typename std::vector<T*>::iterator it = vec->begin(); it != vec->end(); ++it) {
        delete (*it);
    }
}

#endif
