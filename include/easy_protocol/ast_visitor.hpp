#ifndef __AST_VISITOR__
#define __AST_VISITOR__

#include "ast.hpp"

class AstVisitor {
    public:
    virtual void visitType(Type *type) = 0;

    virtual void visitConstant(Constant *constant) = 0;

    virtual void visitIdentifier(Identifier *id) = 0;

    virtual void visitFunctionCall(FunctionCall *functionCall) = 0;

    virtual void visitIndexOf(IndexOf *indexOf) = 0;

    virtual void visitAccess(Access *access) = 0;

    virtual void visitTypeCast(TypeCast *typeCast) = 0;

    virtual void visitUnaOp(UnaOp *unaOp) = 0;

    virtual void visitBinOp(BinOp *binOp) = 0;

    virtual void visitAssign(Assign *assign) = 0;

    virtual void visitBreak(Break *bk) = 0;

    virtual void visitContinue(Continue *ct) = 0;

    virtual void visitReturn(Return *r) = 0;

    virtual void visitBlock(Block *block) = 0;

    virtual void visitExpStatement(ExpStatement *expStatement) = 0;

    virtual void visitDeclarator(Declarator *declarator) = 0;

    virtual void visitDeclaration(Declaration *declaration) = 0;

    virtual void visitIfStatement(IfStatement *ifStatement) = 0;

    virtual void visitWhileStatement(WhileStatement *whileStatement) = 0;

    virtual void visitFormalParameter(FormalParameter *formalParameter) = 0;

    virtual void visitFunctionHeader(FunctionHeader *functionHeader) = 0;

    virtual void visitFunctionDeclaration(FunctionDeclaration *functionDeclaration) = 0;

    virtual void visitStructDeclaration(StructDeclaration *structDeclaration) = 0;
};

#endif
