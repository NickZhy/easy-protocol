#ifndef __HELPER__
#define __HELPER__

#include <iostream>
#include <string>
#include <vector>
#include "ast.hpp"

std::string type2str(PrimitiveType type);

std::string op2str(UnaryOperator op);
std::string op2str(BinaryOperator op);
std::string op2str(AssignOperator op);

template <typename T>
void delVec(std::vector<T*> *vec) {
    if (vec == nullptr) return;
    for (typename std::vector<T*>::iterator it = vec->begin(); it != vec->end(); ++it) {
        delete (*it);
    }
}

#endif
