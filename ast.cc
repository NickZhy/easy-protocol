#include <iostream>
#include <vector>

#include "ast.hh"
#include "parser.tab.hh"
#include "helper.hh"

// Ast virtual destructor
Ast::~Ast() {}

// Identifier
Identifier::Identifier(std::string *n): name(n) {}

Identifier::~Identifier() {
    delete name;
}

void Identifier::accept(AstVisitor *visitor) {
    visitor->visitIdentifier(this);
}

// Type
Type::Type(PrimitiveType t): isPrimitive(true), priType(t), dims(nullptr) {}

Type::Type(Identifier *i): isPrimitive(false), refType(i), dims(nullptr) {}

Type::~Type() {
    if (!isPrimitive) {
	delete refType;
    }
    if (dims != nullptr) {
	delVec(dims);
	delete dims;
    }
}

void Type::setDims(std::vector<Expression*> *d) {
    dims = d;
}

void Type::accept(AstVisitor *visitor) {
    visitor->visitType(this);
}

// Constant
Constant::Constant(int v): type(TYP_INT), intVal(v) {}

Constant::Constant(float v): type(TYP_FLOAT), floatVal(v) {}

Constant::~Constant() {}

void Constant::accept(AstVisitor *visitor) {
    visitor->visitConstant(this);
}

// FunctionCall
FunctionCall::FunctionCall(Ast* f, std::vector<Expression*> *a): func(f), args(a) {}

FunctionCall::~FunctionCall() {
    delete func;
    delVec(args);
    delete args;
}

void FunctionCall::accept(AstVisitor *visitor) {
    visitor->visitFunctionCall(this);
}

// IndexOf
IndexOf::IndexOf(Ast *v, Ast *e): var(v), exp(e) {}

IndexOf::~IndexOf() {
    delete var;
    delete exp;
}

void IndexOf::accept(AstVisitor *visitor) {
    visitor->visitIndexOf(this);
}

// Access
Access::Access(Ast* v, Ast *f): var(v), field(f) {}

Access::~Access() {
    delete var;
    delete field;
}

void Access::accept(AstVisitor *visitor) {
    visitor->visitAccess(this);
}

// TypeCast
TypeCast::TypeCast(Type *t, Ast *e): type(t), exp(e) {}

TypeCast::~TypeCast() {
    delete type;
    delete exp;
}

void TypeCast::accept(AstVisitor *visitor) {
    visitor->visitTypeCast(this);
}

// UnaOp
UnaOp::UnaOp(int o, Ast *c): op(o), child(c) {}

UnaOp::~UnaOp() {
    delete child;
}

void UnaOp::accept(AstVisitor *visitor) {
    visitor->visitUnaOp(this);
}

// IncDec
IncDec::IncDec(int o, bool p, Ast *c): op(o), isPrefix(p), child(c) {}

IncDec::~IncDec() {
    delete child;
}

void IncDec::accept(AstVisitor *visitor) {
    visitor->visitIncDec(this);
}

// BinOp
BinOp::BinOp(int o, Ast *l, Ast *r): op(o), left(l), right(r) {}

BinOp::~BinOp() {
    delete left;
    delete right;
}

void BinOp::accept(AstVisitor *visitor) {
    visitor->visitBinOp(this);
}

// Assign
Assign::Assign(int o, Ast *lv, Ast *rv): op(o), lval(lv), rval(rv) {}

Assign::~Assign() {
    delete lval;
    delete rval;
}

void Assign::accept(AstVisitor *visitor) {
    visitor->visitAssign(this);
}

// Break
void Break::accept(AstVisitor *visitor) {
    visitor->visitBreak(this);
}

// Continue
void Continue::accept(AstVisitor *visitor) {
    visitor->visitContinue(this);
}

// Return
Return::Return(Ast *v): val(v) {}

Return::~Return() {
    if (val != nullptr) {
	delete val;
    }
}

void Return::accept(AstVisitor *visitor) {
    visitor->visitReturn(this);
}

// Block
Block::Block(std::vector<Statement*> *s): stats(s) {}

Block::~Block() {
    delVec(stats);
    delete stats;
}

void Block::accept(AstVisitor *visitor) {
    visitor->visitBlock(this);
}

// ExpStatement
ExpStatement::ExpStatement(Expression *e): exp(e) {}

ExpStatement::~ExpStatement() {
    delete exp;
}

void ExpStatement::accept(AstVisitor *visitor) {
    visitor->visitExpStatement(this);
}

// VarDeclarator
Declarator::Declarator(Identifier *i, Expression *e): id(i), exp(e) {}

Declarator::~Declarator() {
    delete id;
    delete exp;
}

void Declarator::accept(AstVisitor *visitor) {
    visitor->visitDeclarator(this);
}

// Declaration
Declaration::Declaration(Type *t, std::vector<Declarator*> *v): type(t), varDecls(v) {}

Declaration::~Declaration() {
    delete type;
    delVec(varDecls);
    delete varDecls;
}

void Declaration::accept(AstVisitor *visitor) {
    visitor->visitDeclaration(this);
}

// IfStatement
IfStatement::IfStatement(
	Expression *c,
	Statement *f,
	Statement *s
): condition(c), first(f), second(s) {}

IfStatement::~IfStatement() {
    delete condition;
    delete first;
    delete second;
}

void IfStatement::accept(AstVisitor *visitor) {
    visitor->visitIfStatement(this);
}

// WhileStatement
WhileStatement::WhileStatement(Expression *c, Statement *b): condition(c), body(b) {}

WhileStatement::~WhileStatement() {
    delete condition;
    delete body;
}

void WhileStatement::accept(AstVisitor *visitor) {
    visitor->visitWhileStatement(this);
}

// FormalParameter
FormalParameter::FormalParameter(Type *t, Identifier *i): type(t), id(i) {}

FormalParameter::~FormalParameter() {
    delete type;
    delete id;
}

void FormalParameter::accept(AstVisitor *visitor) {
    visitor->visitFormalParameter(this);
}

// FunctionHeader
FunctionHeader::FunctionHeader(Type *t, Identifier *i, std::vector<FormalParameter*> *p): type(t), id(i), paramLst(p) {}

FunctionHeader::~FunctionHeader() {
    delete type;
    delete id;
    delVec(paramLst);
}

void FunctionHeader::accept(AstVisitor *visitor) {
    visitor->visitFunctionHeader(this);
}

// FunctionDeclaration
FunctionDeclaration::FunctionDeclaration(FunctionHeader *h, Block *b): header(h), body(b) {}

FunctionDeclaration::~FunctionDeclaration() {
    delete header;
    delete body;
}

void FunctionDeclaration::accept(AstVisitor *visitor) {
    visitor->visitFunctionDeclaration(this);
}

// StructDeclaration
StructDeclaration::StructDeclaration(Identifier *i, std::vector<Declaration*> *b): id(i), body(b) {}

StructDeclaration::~StructDeclaration() {
    delete id;
    delVec(body);
    delete body;
}

void StructDeclaration::accept(AstVisitor *visitor) {
    visitor->visitStructDeclaration(this);
}
