#ifndef __DEFAULT_VISITOR__
#define __DEFAULT_VISITOR__

#include "ast_visitor.hpp"

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

#endif
