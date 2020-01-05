#ifndef __VISITOR__
#define __VISITOR__

#include "ast.hh"

class StringVisitor: public AstVisitor {
    std::string result;
    public:
    void clear();

    std::string getResult();

    void visitType(Type *type);

    void visitConstant(Constant *constant);

    void visitIdentifier(Identifier *id);

    void visitFunctionCall(FunctionCall *functionCall);

    void visitIndexOf(IndexOf *indexOf);

    void visitAccess(Access *access);

    void visitTypeCast(TypeCast *typeCast);

    void visitUnaOp(UnaOp *unaOp);

    void visitIncDec(IncDec *incDec);

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

#endif
