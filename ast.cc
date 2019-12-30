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

void Type::setDims(std::vector<Expression*> *d) {
    dims = d;
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

// Identifier
Identifier::Identifier(char *n): name(n) {}

Identifier::~Identifier() {}

std::string Identifier::toString() {
    return name;
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

// IndexOf
IndexOf::IndexOf(Ast *v, Ast *e): var(v), exp(e) {}

IndexOf::~IndexOf() {
    delete var;
    delete exp;
}

std::string IndexOf::toString() {
    return var->toString() + "[" + exp->toString() + "]";
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

// TypeCast
TypeCast::TypeCast(Type *t, Ast *e): type(t), exp(e) {}

TypeCast::~TypeCast() {
    delete type;
    delete exp;
}

std::string TypeCast::toString() {
    return "(" + type->toString() + " " + exp->toString() + ")";
}

// UnaOp
UnaOp::UnaOp(int o, Ast *c): op(o), child(c) {}

UnaOp::~UnaOp() {
    delete child;
}

std::string UnaOp::toString() {
    return "(" + op2str(op) + child->toString() + ")";
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

// BinOp
BinOp::BinOp(int o, Ast *l, Ast *r): op(o), left(l), right(r) {}

BinOp::~BinOp() {
    delete left;
    delete right;
}

std::string BinOp::toString() {
    return "(" + left->toString() + op2str(op) + right->toString() + ")";
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

// Break
std::string Break::toString() {
    return "break";
}

// Continue
std::string Continue::toString() {
    return "continue";
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

// ExpStatement
ExpStatement::ExpStatement(Expression *e): exp(e) {}

ExpStatement::~ExpStatement() {
    delete exp;
}

std::string ExpStatement::toString() {
    return exp->toString();
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

// WhileStatement
WhileStatement::WhileStatement(Expression *c, Statement *b): condition(c), body(b) {}

WhileStatement::~WhileStatement() {
    delete condition;
    delete body;
}

std::string WhileStatement::toString() {
    return "while (" + condition->toString() + ") " + body->toString();
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

// FunctionDeclaration
FunctionDeclaration::FunctionDeclaration(FunctionHeader *h, Block *b): header(h), body(b) {}

FunctionDeclaration::~FunctionDeclaration() {
    delete header;
    delete body;
}

std::string FunctionDeclaration::toString() {
    return header->toString() + " " + body->toString();
}

// StructDeclaration
StructDeclaration::StructDeclaration(Identifier *i, std::vector<Declaration*> *b): id(i), body(b) {}

StructDeclaration::~StructDeclaration() {
    delete id;
    delVec(body);
    delete body;
}

std::string StructDeclaration::toString() {
    return "struct " + id->toString() + " {\n" + vec2str(body, "\n", "    ") + "\n}\n";
}
