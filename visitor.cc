#include "helper.hh"
#include "visitor.hh"

void StringVisitor::clear() {
    result.clear();
}

std::string StringVisitor::getResult() {
    return result;
}

void StringVisitor::visitIdentifier(Identifier *id) {
    result.append(id->toString());
}

void StringVisitor::visitType(Type *type) {
    result.append(type->toString());
}

void StringVisitor::visitConstant(Constant *constant) {
    result.append(constant->toString());
}

void StringVisitor::visitFunctionCall(FunctionCall *functionCall) {
    result.append(functionCall->toString());
}

void StringVisitor::visitIndexOf(IndexOf *indexOf) {
    result.append(indexOf->toString());
}

void StringVisitor::visitAccess(Access *access) {
    result.append(access->toString());
}

void StringVisitor::visitTypeCast(TypeCast *typeCast) {
    result.append(typeCast->toString());
}

void StringVisitor::visitUnaOp(UnaOp *unaOp) {
    result.append(unaOp->toString());
}

void StringVisitor::visitIncDec(IncDec *incDec) {
    result.append(incDec->toString());
}

void StringVisitor::visitBinOp(BinOp *binOp) {
    result.append(binOp->toString());
}

void StringVisitor::visitAssign(Assign *assign) {
    result.append(assign->toString());
}

void StringVisitor::visitBreak(Break *bk) {
    result.append(bk->toString());
}

void StringVisitor::visitContinue(Continue *ct) {
    result.append(ct->toString());
}

void StringVisitor::visitReturn(Return *r) {
    result.append(r->toString());
}

void StringVisitor::visitBlock(Block *block) {
    result.append(block->toString());
}

void StringVisitor::visitExpStatement(ExpStatement *expStatement) {
    result.append(expStatement->toString());
}

void StringVisitor::visitDeclarator(Declarator *declarator) {
    result.append(declarator->toString());
}

void StringVisitor::visitDeclaration(Declaration *declaration) {
    result.append(declaration->toString());
}

void StringVisitor::visitIfStatement(IfStatement *ifStatement) {
    result.append(ifStatement->toString());
}

void StringVisitor::visitWhileStatement(WhileStatement *whileStatement) {
    result.append(whileStatement->toString());
}

void StringVisitor::visitFormalParameter(FormalParameter *formalParameter) {
    result.append(formalParameter->toString());
}

void StringVisitor::visitFunctionHeader(FunctionHeader *functionHeader) {
    result.append(functionHeader->toString());
}

void StringVisitor::visitFunctionDeclaration(FunctionDeclaration *functionDeclaration) {
    result.append(functionDeclaration->toString());
}

void StringVisitor::visitStructDeclaration(StructDeclaration *structDeclaration) {
    result.append(structDeclaration->toString());
}
