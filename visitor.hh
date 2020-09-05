#ifndef __VISITOR__
#define __VISITOR__

#include "ast.hh"

class ToStringVisitor: public AstVisitor {
    private:
    std::string result;
    int indentLevel;
    static const std::string INDENT;

    template <typename T>
    void visitVec(
            std::vector<T*> *vec,
            std::string separator = " ",
            std::string before = "",
            std::string after = "") {
        if (vec == nullptr) return;
        for (typename std::vector<T*>::iterator it = vec->begin(); it != vec->end(); ++it) {
            result.append(before);
            (*it)->accept(this);
            result.append(after);
            if (it != vec->end() - 1) {
                result.append(separator);
            }
        }
    }

    public:
    ToStringVisitor();

    void clear();

    std::string getResult();

    void visitIdentifier(Identifier *id);

    void visitType(Type *type);

    void visitConstant(Constant *constant);

    void visitFunctionCall(FunctionCall *functionCall);

    void visitIndexOf(IndexOf *indexOf);

    void visitAccess(Access *access);

    void visitTypeCast(TypeCast *typeCast);

    void visitUnaOp(UnaOp *unaOp);

    void visitBinOp(BinOp *binOp);

    void visitAssign(Assign *assign);

    void visitBreak(Break *bk);

    void visitContinue(Continue *ct);

    void visitReturn(Return *r);

    void visitBlock(Block *block);

    void visitExpStatement(ExpStatement *expStatement);

    void visitDeclarator(Declarator *declarator);

    void visitDeclaration(Declaration *declaration);

    void visitIfStatement(IfStatement *ifStatement);

    void visitWhileStatement(WhileStatement *whileStatement);

    void visitFormalParameter(FormalParameter *formalParameter);

    void visitFunctionHeader(FunctionHeader *functionHeader);

    void visitFunctionDeclaration(FunctionDeclaration *functionDeclaration);

    void visitStructDeclaration(StructDeclaration *structDeclaration);
};

class DefaultVisitor: public AstVisitor {
    public:
    void visitIdentifier(Identifier *id) {}

    void visitType(Type *type) {}

    void visitConstant(Constant *constant) {}

    void visitFunctionCall(FunctionCall *functionCall) {}

    void visitIndexOf(IndexOf *indexOf) {}

    void visitAccess(Access *access) {}

    void visitTypeCast(TypeCast *typeCast) {}

    void visitUnaOp(UnaOp *unaOp) {}

    void visitBinOp(BinOp *binOp) {}

    void visitAssign(Assign *assign) {}

    void visitBreak(Break *bk) {}

    void visitContinue(Continue *ct) {}

    void visitReturn(Return *r) {}

    void visitBlock(Block *block) {}

    void visitExpStatement(ExpStatement *expStatement) {}

    void visitDeclarator(Declarator *declarator) {}

    void visitDeclaration(Declaration *declaration) {}

    void visitIfStatement(IfStatement *ifStatement) {}

    void visitWhileStatement(WhileStatement *whileStatement) {}

    void visitFormalParameter(FormalParameter *formalParameter) {}

    void visitFunctionHeader(FunctionHeader *functionHeader) {}

    void visitFunctionDeclaration(FunctionDeclaration *functionDeclaration) {}

    void visitStructDeclaration(StructDeclaration *structDeclaration) {}
};

class StructVisitor: public DefaultVisitor {
    public:
    void visitStructDeclaration(StructDeclaration *structDeclaration);
};

#endif
