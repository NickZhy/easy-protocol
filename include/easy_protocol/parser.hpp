#ifndef __PARSER__
#define __PARSER__

#include <vector>
#include "ast_visitor.hpp"

void parse(std::vector<Ast*> &astLst, FILE *file);

#endif
