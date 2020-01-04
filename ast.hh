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
    public:
    bool isPrimitive;
    union {
	PrimitiveType priType;
	Identifier *refType;
    };
    // A list of expressions holding the size of dimensions.
    std::vector<Expression*> *dims;

    Type(PrimitiveType t);
    Type(Identifier *r);
    ~Type();
    std::string toString();
    void setDims(std::vector<Expression*> *d);
};

// Expression
class Constant: public Expression {
    public:
    PrimitiveType type;

    union {
	int intVal;
	float floatVal;
    };
    Constant(int v);
    Constant(float v);
    ~Constant();
    std::string toString();
};

class Identifier: public Expression {
    public:
    std::string *name;

    Identifier(std::string *n);
    ~Identifier();
    std::string toString();
};

class FunctionCall: public Expression {
    public:
    Ast *func;
    std::vector<Expression*> *args;

    FunctionCall(Ast *f, std::vector<Expression*> *a);
    ~FunctionCall();
    std::string toString();
};

class IndexOf: public Expression {
    public:
    Ast *var, *exp;

    IndexOf(Ast *v, Ast *e);
    ~IndexOf();
    std::string toString();
};

class Access: public Expression {
    public:
    Ast *var, *field;

    Access(Ast *v, Ast *f);
    ~Access();
    std::string toString();
};

class TypeCast: public Expression {
    public:
    Type *type;
    Ast *exp;

    TypeCast(Type *t, Ast* e);
    ~TypeCast();
    std::string toString();
};

class UnaOp: public Expression {
    public:
    int op;
    Ast *child;

    UnaOp(int o, Ast *c);
    ~UnaOp();
    std::string toString();
};

class IncDec: public Expression {
    public:
    int op;
    bool isPrefix;
    Ast *child;

    IncDec(int t, bool isPrefix, Ast *c);
    ~IncDec();
    std::string toString();
};

class BinOp: public Expression {
    public:
    int op;
    Ast *left, *right;

    BinOp(int o, Ast *l, Ast *r);
    ~BinOp();
    std::string toString();
};

class Assign: public Expression {
    public:
    int op;
    Ast *lval, *rval;

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
    public:
    Ast *val;

    Return(Ast *v);
    ~Return();
    std::string toString();
};

class Block: public Statement {
    public:
    std::vector<Statement*> *stats;

    Block(std::vector<Statement*> *s);
    ~Block();
    std::string toString();
};

class ExpStatement: public Statement {
    public:
    Expression *exp;

    ExpStatement(Expression *e);
    ~ExpStatement();
    std::string toString();
};

class Declarator: public Ast {
    public:
    Identifier *id;
    Expression *exp;

    Declarator(Identifier *i, Expression *e);
    ~Declarator();
    std::string toString();
};

class Declaration: public Statement {
    public:
    Type *type;
    std::vector<Declarator*> *varDecls;

    Declaration(Type *i, std::vector<Declarator*> *v);
    ~Declaration();
    std::string toString();
};

class IfStatement: public Statement {
    public:
    Expression *condition;
    Statement *first, *second;

    IfStatement(Expression *c, Statement *f, Statement *s);
    ~IfStatement();
    std::string toString();
};

class WhileStatement: public Statement {
    public:
    Expression *condition;
    Statement *body;
    
    WhileStatement(Expression *c, Statement *b);
    ~WhileStatement();
    std::string toString();
};

// Top-level declaration
class FormalParameter: public Ast {
    public:
    Type *type;
    Identifier *id;

    FormalParameter(Type *t, Identifier *i);
    ~FormalParameter();
    std::string toString();
};

class FunctionHeader: public Ast {
    public:
    Type *type;
    Identifier *id;
    std::vector<FormalParameter*> *paramLst;

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
    public:
    Identifier *id;
    std::vector<Declaration*> *body;

    StructDeclaration(Identifier *i, std::vector<Declaration*> *b);
    ~StructDeclaration();
    std::string toString();
};

#endif
