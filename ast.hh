#ifndef __AST__
#define __AST__

#include <string>
#include <vector>

class AstVisitor;

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
    virtual void accept(AstVisitor*) = 0;
};

class Expression: public Ast {};

class Statement: public Ast {};

class Identifier: public Expression {
    public:
    std::string *name;

    Identifier(std::string *n);
    ~Identifier();

    std::string toString();
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

    std::string toString();
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

    std::string toString();
    void accept(AstVisitor *visitor);
};

class FunctionCall: public Expression {
    public:
    Ast *func;
    std::vector<Expression*> *args;

    FunctionCall(Ast *f, std::vector<Expression*> *a);
    ~FunctionCall();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class IndexOf: public Expression {
    public:
    Ast *var, *exp;

    IndexOf(Ast *v, Ast *e);
    ~IndexOf();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class Access: public Expression {
    public:
    Ast *var, *field;

    Access(Ast *v, Ast *f);
    ~Access();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class TypeCast: public Expression {
    public:
    Type *type;
    Ast *exp;

    TypeCast(Type *t, Ast* e);
    ~TypeCast();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class UnaOp: public Expression {
    public:
    int op;
    Ast *child;

    UnaOp(int o, Ast *c);
    ~UnaOp();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class IncDec: public Expression {
    public:
    int op;
    bool isPrefix;
    Ast *child;

    IncDec(int t, bool isPrefix, Ast *c);
    ~IncDec();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class BinOp: public Expression {
    public:
    int op;
    Ast *left, *right;

    BinOp(int o, Ast *l, Ast *r);
    ~BinOp();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class Assign: public Expression {
    public:
    int op;
    Ast *lval, *rval;

    Assign(int o, Ast *lv, Ast *rv);
    ~Assign();

    std::string toString();
    void accept(AstVisitor *visitor);
};

// Statement
class Break: public Statement {
    public:
    std::string toString();
    void accept(AstVisitor *visitor);
};

class Continue: public Statement {
    public:
    std::string toString();
    void accept(AstVisitor *visitor);
};

class Return: public Statement {
    public:
    Ast *val;

    Return(Ast *v);
    ~Return();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class Block: public Statement {
    public:
    std::vector<Statement*> *stats;

    Block(std::vector<Statement*> *s);
    ~Block();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class ExpStatement: public Statement {
    public:
    Expression *exp;

    ExpStatement(Expression *e);
    ~ExpStatement();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class Declarator: public Ast {
    public:
    Identifier *id;
    Expression *exp;

    Declarator(Identifier *i, Expression *e);
    ~Declarator();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class Declaration: public Statement {
    public:
    Type *type;
    std::vector<Declarator*> *varDecls;

    Declaration(Type *i, std::vector<Declarator*> *v);
    ~Declaration();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class IfStatement: public Statement {
    public:
    Expression *condition;
    Statement *first, *second;

    IfStatement(Expression *c, Statement *f, Statement *s);
    ~IfStatement();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class WhileStatement: public Statement {
    public:
    Expression *condition;
    Statement *body;

    WhileStatement(Expression *c, Statement *b);
    ~WhileStatement();

    std::string toString();
    void accept(AstVisitor *visitor);
};

// Top-level declaration
class FormalParameter: public Ast {
    public:
    Type *type;
    Identifier *id;

    FormalParameter(Type *t, Identifier *i);
    ~FormalParameter();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class FunctionHeader: public Ast {
    public:
    Type *type;
    Identifier *id;
    std::vector<FormalParameter*> *paramLst;

    FunctionHeader(Type *t, Identifier *i, std::vector<FormalParameter*> *p);
    ~FunctionHeader();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class FunctionDeclaration: public Ast {
    FunctionHeader *header;
    Block *body;
    public:
    FunctionDeclaration(FunctionHeader *h, Block *b);
    ~FunctionDeclaration();

    std::string toString();
    void accept(AstVisitor *visitor);
};

class StructDeclaration: public Ast {
    public:
    Identifier *id;
    std::vector<Declaration*> *body;

    StructDeclaration(Identifier *i, std::vector<Declaration*> *b);
    ~StructDeclaration();

    std::string toString();
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

    virtual void visitIncDec(IncDec *incDec) = 0;

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
