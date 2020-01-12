#ifndef __AST__
#define __AST__

#include <string>
#include <vector>

typedef enum {
    TYP_BOOL,
    TYP_BYTE,
    TYP_SHORT,
    TYP_INT,
    TYP_LONG,
    TYP_FLOAT,
    TYP_DOUBLE
} PrimitiveType;

typedef enum {
    OP_POS,
    OP_NEG,
    OP_NOT,
    OP_BNOT,
    OP_PRE_INC,
    OP_POS_INC,
    OP_PRE_DEC,
    OP_POS_DEC
} UnaryOperator;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_AND,
    OP_OR,
    OP_BXOR,
    OP_BAND,
    OP_BOR,
    OP_LSH,
    OP_RSH,
    OP_LT,
    OP_GR,
    OP_LE,
    OP_GE,
    OP_EQ,
    OP_NEQ
} BinaryOperator;

typedef enum {
    ASG_NORM,
    ASG_ADD,
    ASG_SUB,
    ASG_MUL,
    ASG_DIV,
    ASG_MOD,
    ASG_XOR,
    ASG_AND,
    ASG_OR,
    ASG_LSH,
    ASG_RSH
} AssignOperator;

class AstVisitor;

class Ast {
    public:
    virtual ~Ast() = 0;

    virtual void accept(AstVisitor*) = 0;
};

class Expression: public Ast {};

class Statement: public Ast {};

class Identifier: public Expression {
    public:
    std::string *name;

    Identifier(std::string *n);
    ~Identifier();

    void accept(AstVisitor *visitor);
};

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
    void setDims(std::vector<Expression*> *d);

    void accept(AstVisitor *visitor);
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

    void accept(AstVisitor *visitor);
};

class FunctionCall: public Expression {
    public:
    Expression *func;
    std::vector<Expression*> *args;

    FunctionCall(Expression *f, std::vector<Expression*> *a);
    ~FunctionCall();

    void accept(AstVisitor *visitor);
};

class IndexOf: public Expression {
    public:
    Expression *var, *idx;

    IndexOf(Expression *v, Expression *i);
    ~IndexOf();

    void accept(AstVisitor *visitor);
};

class Access: public Expression {
    public:
    Expression *var, *field;

    Access(Expression *v, Expression *f);
    ~Access();

    void accept(AstVisitor *visitor);
};

class TypeCast: public Expression {
    public:
    Type *type;
    Expression *expr;

    TypeCast(Type *t, Expression* e);
    ~TypeCast();

    void accept(AstVisitor *visitor);
};

class UnaOp: public Expression {
    public:
    UnaryOperator op;
    Expression *expr;

    UnaOp(UnaryOperator o, Expression *e);
    ~UnaOp();

    void accept(AstVisitor *visitor);
};

class BinOp: public Expression {
    public:
    BinaryOperator op;
    Expression *left, *right;

    BinOp(BinaryOperator o, Expression *l, Expression *r);
    ~BinOp();

    void accept(AstVisitor *visitor);
};

class Assign: public Expression {
    public:
    AssignOperator op;
    Expression *lval, *rval;

    Assign(AssignOperator o, Expression *lv, Expression *rv);
    ~Assign();

    void accept(AstVisitor *visitor);
};

// Statement
class Break: public Statement {
    public:
    void accept(AstVisitor *visitor);
};

class Continue: public Statement {
    public:
    void accept(AstVisitor *visitor);
};

class Return: public Statement {
    public:
    Expression *var;

    Return(Expression *v);
    ~Return();

    void accept(AstVisitor *visitor);
};

class Block: public Statement {
    public:
    std::vector<Statement*> *stats;

    Block(std::vector<Statement*> *s);
    ~Block();

    void accept(AstVisitor *visitor);
};

class ExpStatement: public Statement {
    public:
    Expression *expr;

    ExpStatement(Expression *e);
    ~ExpStatement();

    void accept(AstVisitor *visitor);
};

class Declarator: public Ast {
    public:
    Identifier *id;
    Expression *exp;

    Declarator(Identifier *i, Expression *e);
    ~Declarator();

    void accept(AstVisitor *visitor);
};

class Declaration: public Statement {
    public:
    Type *type;
    std::vector<Declarator*> *varDecls;

    Declaration(Type *i, std::vector<Declarator*> *v);
    ~Declaration();

    void accept(AstVisitor *visitor);
};

class IfStatement: public Statement {
    public:
    Expression *condition;
    Statement *first, *second;

    IfStatement(Expression *c, Statement *f, Statement *s);
    ~IfStatement();

    void accept(AstVisitor *visitor);
};

class WhileStatement: public Statement {
    public:
    Expression *condition;
    Statement *body;

    WhileStatement(Expression *c, Statement *b);
    ~WhileStatement();

    void accept(AstVisitor *visitor);
};

// Top-level declaration
class FormalParameter: public Ast {
    public:
    Type *type;
    Identifier *id;

    FormalParameter(Type *t, Identifier *i);
    ~FormalParameter();

    void accept(AstVisitor *visitor);
};

class FunctionHeader: public Ast {
    public:
    Type *type;
    Identifier *id;
    std::vector<FormalParameter*> *paramLst;

    FunctionHeader(Type *t, Identifier *i, std::vector<FormalParameter*> *p);
    ~FunctionHeader();

    void accept(AstVisitor *visitor);
};

class FunctionDeclaration: public Ast {
    public:
    FunctionHeader *header;
    Block *body;
    FunctionDeclaration(FunctionHeader *h, Block *b);
    ~FunctionDeclaration();

    void accept(AstVisitor *visitor);
};

class StructDeclaration: public Ast {
    public:
    Identifier *id;
    std::vector<Declaration*> *body;

    StructDeclaration(Identifier *i, std::vector<Declaration*> *b);
    ~StructDeclaration();

    void accept(AstVisitor *visitor);
};

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
