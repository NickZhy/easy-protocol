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

template <typename T>
std::string vec2str(std::vector<T*> *vec, std::string separator = " ", std::string before = "", std::string after = "") {
    if (vec == NULL) return "";
    std::string ret;
    for (typename std::vector<T*>::iterator it = vec->begin(); it != vec->end(); ++it) {
	ret += before;
	ret += ((Ast*) *it)->toString();
	ret += after;
	if (it != vec->end() - 1) {
	    ret += separator;
	}
    }
    return ret;
}

#endif
