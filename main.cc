#include <vector>
#include <iostream>

#include "ast.hh"
#include "parser.hh"
#include "visitor.hh"

int main(int argc, char** argv) {
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        std::cout << "failed to open file: " << argv[1] << std::endl;
        return 0;
    }
    std::vector<Ast*> astLst;
    parse(astLst, fp);
    fclose(fp);
    for (int i = 0; i < astLst.size(); ++i) {
        Ast *ast = astLst[i];
        StringVisitor visitor;
        ast->accept(&visitor);
        std::cout << "parsed ast:" << std::endl
            << visitor.getResult() << std::endl;
        delete ast;
    }
    return 0;
}
