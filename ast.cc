#include <iostream>
#include <vector>

#include "ast.hh"
#include "parser.tab.hh"
#include "helper.hh"

// Ast virtual destructor
Ast::~Ast() {}

// Type
Type::Type(PrimitiveType t): isPrimitive(true), priType(t), dims(NULL) {}

Type::Type(Identifier *i): isPrimitive(false), refType(i), dims(NULL) {}

Type::~Type() {
    if (!isPrimitive) {
	delete refType;
    }
    if (dims != NULL) {
	delVec(dims);
	delete dims;
    }
}

void Type::setDims(std::vector<Expression*> *d) {
    dims = d;
}

std::string Type::toString() {
    std::string ret;
    if (isPrimitive) {
	ret = type2str(priType);
    } else {
	ret = refType->toString();
    }
    if (dims != NULL) {
	ret += vec2str(dims, "", "[", "]");
    }
    return ret;
}

void Type::accept(AstVisitor *visitor) {
    visitor->visitType(this);
}

// Constant
Constant::Constant(int v): type(TYP_INT), intVal(v) {}

Constant::Constant(float v): type(TYP_FLOAT), floatVal(v) {}

Constant::~Constant() {}

std::string Constant::toString() {
    std::string ret;
    switch (type) {
	case TYP_BOOL:
	    ret = (intVal != 0 ? "true" : "false");
            break;
	case TYP_BYTE: 
	    ret = std::to_string(intVal) + "B";
	    break;
	case TYP_SHORT:
	    ret = std::to_string(intVal) + "S";
	    break;
	case TYP_INT: 
	    ret = std::to_string(intVal) + "I";
	    break;
	case TYP_LONG:
	    ret = std::to_string(intVal) + "L";
	    break;
	case TYP_FLOAT: 
	    ret = std::to_string(intVal) + "F";
	    break;
	case TYP_DOUBLE:
	    ret = std::to_string(intVal) + "D";
	    break;
	default:
	    ret = "illegal type";
    }
    return ret;
}

void Constant::accept(AstVisitor *visitor) {
    visitor->visitConstant(this);
}

// Identifier
Identifier::Identifier(std::string *n): name(n) {}

Identifier::~Identifier() {
    delete name;
}

std::string Identifier::toString() {
    return *name;
}

void Identifier::accept(AstVisitor *visitor) {
    visitor->visitIdentifier(this);
}

// FunctionCall
FunctionCall::FunctionCall(Ast* f, std::vector<Expression*> *a): func(f), args(a) {}

FunctionCall::~FunctionCall() {
    delete func;
    delVec(args);
    delete args;
}

std::string FunctionCall::toString() {
   return func->toString() + "(" + vec2str(args, ", ") + ")";
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

std::string IndexOf::toString() {
    return var->toString() + "[" + exp->toString() + "]";
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

std::string Access::toString() {
    return "(" + var->toString() + "." + field->toString() + ")";
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

std::string TypeCast::toString() {
    return "(" + type->toString() + " " + exp->toString() + ")";
}

void TypeCast::accept(AstVisitor *visitor) {
    visitor->visitTypeCast(this);
}

// UnaOp
UnaOp::UnaOp(int o, Ast *c): op(o), child(c) {}

UnaOp::~UnaOp() {
    delete child;
}

std::string UnaOp::toString() {
    return "(" + op2str(op) + child->toString() + ")";
}

void UnaOp::accept(AstVisitor *visitor) {
    visitor->visitUnaOp(this);
}

// IncDec
IncDec::IncDec(int o, bool p, Ast *c): op(o), isPrefix(p), child(c) {}

IncDec::~IncDec() {
    delete child;
}

std::string IncDec::toString() {
    std::string ret = "(";
    if (isPrefix) {
	ret += op2str(op) + child->toString();
    } else {
	ret += child->toString() + op2str(op);
    }
    return ret + ")";
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

std::string BinOp::toString() {
    return "(" + left->toString() + op2str(op) + right->toString() + ")";
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

std::string Assign::toString() {
    return "(" + lval->toString() + op2str(op) + rval->toString() + ")";
}

void Assign::accept(AstVisitor *visitor) {
    visitor->visitAssign(this);
}

// Break
std::string Break::toString() {
    return "break";
}

void Break::accept(AstVisitor *visitor) {
    visitor->visitBreak(this);
}

// Continue
std::string Continue::toString() {
    return "continue";
}

void Continue::accept(AstVisitor *visitor) {
    visitor->visitContinue(this);
}

// Return
Return::Return(Ast *v): val(v) {}

Return::~Return() {
    if (val != NULL) {
	delete val;
    }
}

std::string Return::toString() {
    std::string ret = "return";
    if (val != NULL) {
	ret += " " + val->toString();
    }
    return ret;
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

std::string Block::toString() {
    static int indLevel = 0;
    const std::string INDENT("    ");

    std::string indents;
    for (int i = 0; i < indLevel; ++i) {
	indents += INDENT;
    }
    ++indLevel;
    std::string ret = "{\n" + vec2str(stats, "\n", indents + INDENT) + "\n" + indents + "}";
    --indLevel;
    return ret;
}

void Block::accept(AstVisitor *visitor) {
    visitor->visitBlock(this);
}

// ExpStatement
ExpStatement::ExpStatement(Expression *e): exp(e) {}

ExpStatement::~ExpStatement() {
    delete exp;
}

std::string ExpStatement::toString() {
    return exp->toString();
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

std::string Declarator::toString() {
    std::string ret = id->toString();
    if (exp != NULL) {
	ret += "=" + exp->toString();
    }
    return ret;
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

std::string Declaration::toString() {
    return type->toString() + " " + vec2str(varDecls, " ");
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

std::string IfStatement::toString() {
    std::string ret = "if (" + condition->toString() + ") " + first->toString();
    if (second != NULL) {
	ret += " else " + second->toString();
    }
    return ret;
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

std::string WhileStatement::toString() {
    return "while (" + condition->toString() + ") " + body->toString();
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

std::string FormalParameter::toString() {
    return type->toString() + " " + id->toString();
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

std::string FunctionHeader::toString() {
    return type->toString() + " " + id->toString() + "(" + vec2str(paramLst, " ") + ")";
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

std::string FunctionDeclaration::toString() {
    return header->toString() + " " + body->toString();
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

std::string StructDeclaration::toString() {
    return "struct " + id->toString() + " {\n" + vec2str(body, "\n", "    ") + "\n}";
}

void StructDeclaration::accept(AstVisitor *visitor) {
    visitor->visitStructDeclaration(this);
}
