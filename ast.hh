#ifndef __AST__
#define __AST__

#include <string>
#include <vector>

typedef enum PrimitiveType {
    TYP_BOOL,
    TYP_BYTE,
    TYP_SHORT,
    TYP_INT,
    TYP_LONG,
    TYP_FLOAT,
    TYP_DOUBLE
} PrimitiveType;

class Ast {
    public:
    virtual ~Ast() = 0;
    virtual std::string toString() = 0;
};

class Expression: public Ast {};

class Statement: public Ast {};

class Identifier;

// Type
class Type: public Ast {
    bool isPrimitive;
    union {
	PrimitiveType priType;
	Identifier *refType;
    };
    // A list of expressions holding the size of dimensions.
    std::vector<Expression*> *dims;
    public:
    Type(PrimitiveType t);
    Type(Identifier *r);
    ~Type();
    std::string toString();
    void setDims(std::vector<Expression*> *d);
};

// Expression
class Constant: public Expression {
    PrimitiveType  type;
    union {
	int intVal;
	float floatVal;
    };
    public:
    Constant(int v);
    Constant(float v);
    ~Constant();
    std::string toString();
};

class Identifier: public Expression {
    std::string name;
    public:
    Identifier(char *n);
    ~Identifier();
    std::string toString();
};

class FunctionCall: public Expression {
    Ast *func;
    std::vector<Expression*> *args;
    public:
    FunctionCall(Ast *f, std::vector<Expression*> *a);
    ~FunctionCall();
    std::string toString();
};

class IndexOf: public Expression {
    Ast *var, *exp;
    public:
    IndexOf(Ast *v, Ast *e);
    ~IndexOf();
    std::string toString();
};

class Access: public Expression {
    Ast *var, *field;
    public:
    Access(Ast *v, Ast *f);
    ~Access();
    std::string toString();
};

class TypeCast: public Expression {
    Type *type;
    Ast *exp;
    public:
    TypeCast(Type *t, Ast* e);
    ~TypeCast();
    std::string toString();
};

class UnaOp: public Expression {
    int op;
    Ast *child;
    public:
    UnaOp(int o, Ast *c);
    ~UnaOp();
    std::string toString();
};

class IncDec: public Expression {
    int op;
    bool isPrefix;
    Ast *child;
    public:
    IncDec(int t, bool isPrefix, Ast *c);
    ~IncDec();
    std::string toString();
};

class BinOp: public Expression {
    int op;
    Ast *left, *right;
    public:
    BinOp(int o, Ast *l, Ast *r);
    ~BinOp();
    std::string toString();
};

class Assign: public Expression {
    int op;
    Ast *lval, *rval;
    public:
    Assign(int o, Ast *lv, Ast *rv);
    ~Assign();
    std::string toString();
};

// Statement
class Break: public Statement {
    public:
    std::string toString();
};

class Continue: public Statement {
    public:
    std::string toString();
};

class Return: public Statement {
    Ast *val;
    public:
    Return(Ast *v);
    ~Return();
    std::string toString();
};

class Block: public Statement {
    std::vector<Statement*> *stats;
    public:
    Block(std::vector<Statement*> *s);
    ~Block();
    std::string toString();
};

class ExpStatement: public Statement {
    Expression *exp;
    public:
    ExpStatement(Expression *e);
    ~ExpStatement();
    std::string toString();
};

class Declarator: public Ast {
    Identifier *id;
    Expression *exp;
    public:
    Declarator(Identifier *i, Expression *e);
    ~Declarator();
    std::string toString();
};

class Declaration: public Statement {
    Type *type;
    std::vector<Declarator*> *varDecls;
    public:
    Declaration(Type *i, std::vector<Declarator*> *v);
    ~Declaration();
    std::string toString();
};

class IfStatement: public Statement {
    Expression *condition;
    Statement *first, *second;
    public:
    IfStatement(Expression *c, Statement *f, Statement *s);
    ~IfStatement();
    std::string toString();
};

class WhileStatement: public Statement {
    Expression *condition;
    Statement *body;
    public:
    WhileStatement(Expression *c, Statement *b);
    ~WhileStatement();
    std::string toString();
};

// Top-level declaration
class FormalParameter: public Ast {
    Type *type;
    Identifier *id;
    public:
    FormalParameter(Type *t, Identifier *i);
    ~FormalParameter();
    std::string toString();
};

class FunctionHeader: public Ast {
    Type *type;
    Identifier *id;
    std::vector<FormalParameter*> *paramLst;
    public:
    FunctionHeader(Type *t, Identifier *i, std::vector<FormalParameter*> *p);
    ~FunctionHeader();
    std::string toString();
};

class FunctionDeclaration: public Ast {
    FunctionHeader *header;
    Block *body;
    public:
    FunctionDeclaration(FunctionHeader *h, Block *b);
    ~FunctionDeclaration();
    std::string toString();
};

class StructDeclaration: public Ast {
    Identifier *id;
    std::vector<Declaration*> *body;
    public:
    StructDeclaration(Identifier *i, std::vector<Declaration*> *b);
    ~StructDeclaration();
    std::string toString();
};

#endif