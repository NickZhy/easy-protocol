%define api.pure full
%locations
%lex-param { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param { std::vector<Ast*> &astLst }

%code requires {
    #include <string>
    #include <vector>

    #include "ast.hh"
    typedef void* yyscan_t;
}

%code provides {
    #include "parser.hh"
}

%{
    #include "parser.tab.hh"
    #include "lexer.lex.hh"

    void yyerror(YYLTYPE*, yyscan_t, std::vector<Ast*>&, const char*);
%}

%union {
    int	intVal;
    float floatVal;
    std::string *strVal;

    Ast	*node;
    Identifier *id;

    Expression *exp;
    std::vector<Expression*> *expLst;
    
    Declarator *declarator;
    std::vector<Declarator*> *declaratorLst;
    
    Declaration *declaration;
    std::vector<Declaration*> *declarationLst;

    Statement *stat;
    std::vector<Statement*> *statLst;
    Block *block;

    Type *type;
    PrimitiveType priType;
    
    FormalParameter *para;
    std::vector<FormalParameter*> *paraLst;

    FunctionHeader *funcHead;
    FunctionDeclaration *funcDecl;

    StructDeclaration* structDecl;
}

%token TOK_EOF 0

%token IF ELSE
%token WHILE
%token BREAK CONTINUE RETURN

%token TYPE TYPE_NAME
%token ID
%token INT_CON FLOAT_CON

%token INC DEC
%token LSH RSH
%token LE GE EQ NEQ
%token AND OR
%token ADD_ASG SUB_ASG MUL_ASG DIV_ASG MOD_ASG XOR_ASG AND_ASG OR_ASG LSH_ASG RSH_ASG

%token STRUCT

%type <priType> TYPE

%type <strVal> ID TYPE_NAME
%type <intVal> INT_CON
%type <floatVal> FLOAT_CON

%type <expLst> dim_exp arg_lst
%type <type> type basic_type array_type

%type <id> id struct_name
%type <exp> term term0 term1 term2
%type <exp> exp exp0 exp1 exp2 exp3 exp4 exp5 exp6 exp7 exp8 exp9 exp10

%type <block> block_stat
%type <stat> stat basic_stat if_stat while_stat
%type <statLst> stat_lst

%type <declarator> decl
%type <declaratorLst> decl_lst

%type <declaration> decl_stat
%type <declarationLst> decl_stat_lst decl_block


%type <para> formal_para
%type <paraLst> formal_para_lst
%type <funcHead> function_header
%type <funcDecl> function_decl
%type <structDecl> struct_decl

%destructor { } <intVal> <floatVal> <priType>
%destructor { delete $$; } <*>

%start program

%%
id
: ID	{ $$ = new Identifier($1); }
;

/* type */
type
: basic_type
| array_type
;

basic_type
: TYPE		{ $$ = new Type($1); }
| TYPE_NAME 	{ $$ = new Type(new Identifier($1)); }
;

array_type
: basic_type dim_exp	{ $1->setDims($2); $$ = $1; }
;

dim_exp
: '[' exp ']'		{ $$ = new std::vector<Expression*>(); $$->push_back($2); }
| dim_exp '[' exp ']'	{ $1->push_back($3); $$ = $1; }
;

/* arguments */
arg_lst
:			{ $$ = new std::vector<Expression*>(); }
| exp			{ $$ = new std::vector<Expression*>(); $$->push_back($1); }
| arg_lst ',' exp	{ $1->push_back($3); $$ = $1; }
;

/* term */
term0
: id 		{ $$ = $1; }
| INT_CON	{ $$ = new Constant($1); }
| FLOAT_CON	{ $$ = new Constant($1); }
| '(' exp ')'	{ $$ = $2; }
;

term1
: term0
| term1 INC 		{ $$ = new IncDec(INC, false, $1); }
| term1 DEC		{ $$ = new IncDec(DEC, false, $1); }
| term1 '(' arg_lst ')'	{ $$ = new FunctionCall($1, $3); }
| term1 '[' exp ']'	{ $$ = new IndexOf($1, $3); }
| term1 '.' term0	{ $$ = new Access($1, $3); }
;

term2
: term1
| INC term2	{ $$ = new IncDec(INC, true, $2); }
| DEC term2	{ $$ = new IncDec(DEC, true, $2); }
| '+' term2	{ $$ = new UnaOp('+', $2); }
| '-' term2	{ $$ = new UnaOp('-', $2); }
| '!' term2	{ $$ = new UnaOp('!', $2); }
| '~' term2	{ $$ = new UnaOp('~', $2); }
| '(' type ')' term2	{ $$ = new TypeCast($2, $4); } 
;

term: term2;

/* expression */
exp0
: term
| exp0 '*' term { $$ = new BinOp('*', $1, $3); }
| exp0 '/' term { $$ = new BinOp('/', $1, $3); }
| exp0 '%' term { $$ = new BinOp('%', $1, $3); }
;

exp1
: exp0
| exp1 '+' exp0 { $$ = new BinOp('+', $1, $3); }
| exp1 '-' exp0 { $$ = new BinOp('-', $1, $3); }
;

exp2
: exp1
| exp2 LSH exp1	{ $$ = new BinOp(LSH, $1, $3); }
| exp2 RSH exp1	{ $$ = new BinOp(RSH, $1, $3); }
;

exp3
: exp2
| exp3 '<' exp2 { $$ = new BinOp('<', $1, $3); }
| exp3 '>' exp2 { $$ = new BinOp('>', $1, $3); }
| exp3 LE exp2	{ $$ = new BinOp(LE, $1, $3); }
| exp3 GE exp2	{ $$ = new BinOp(GE, $1, $3); }
;

exp4
: exp3
| exp4 EQ exp3	{ $$ = new BinOp(EQ, $1, $3); }
| exp4 NEQ exp3	{ $$ = new BinOp(NEQ, $1, $3); }
;

exp5
: exp4 
| exp5 '&' exp4	{ $$ = new BinOp('&', $1, $3); }
;

exp6
: exp5
| exp6 '^' exp5 { $$ = new BinOp('^', $1, $3); }
;

exp7
: exp6
| exp7 '|' exp6 { $$ = new BinOp('|', $1, $3); }
;

exp8
: exp7
| exp8 AND exp7 { $$ = new BinOp(AND, $1, $3); }
;

exp9
: exp8
| exp9 OR exp8	{ $$ = new BinOp(OR, $1, $3); }
;

exp10
: exp9
| exp9 '=' exp10	{ $$ = new Assign('=', $1, $3); }
| exp9 ADD_ASG exp10	{ $$ = new Assign(ADD_ASG, $1, $3); }
| exp9 SUB_ASG exp10	{ $$ = new Assign(SUB_ASG, $1, $3); }
| exp9 MUL_ASG exp10	{ $$ = new Assign(MUL_ASG, $1, $3); }
| exp9 DIV_ASG exp10	{ $$ = new Assign(DIV_ASG, $1, $3); }
| exp9 MOD_ASG exp10	{ $$ = new Assign(MOD_ASG, $1, $3); }
| exp9 XOR_ASG exp10	{ $$ = new Assign(XOR_ASG, $1, $3); }
| exp9 AND_ASG exp10	{ $$ = new Assign(AND_ASG, $1, $3); }
| exp9 OR_ASG exp10	{ $$ = new Assign(OR_ASG, $1, $3); }
| exp9 LSH_ASG exp10	{ $$ = new Assign(LSH_ASG, $1, $3); }
| exp9 RSH_ASG exp10	{ $$ = new Assign(RSH_ASG, $1, $3); }
;

exp: exp10;

/* statement */
stat
: basic_stat
| if_stat
| while_stat
| block_stat    { $$ = $1; }
;

/* basic statement */
basic_stat
: decl_stat             { $$ = $1; } 
| exp ';'		{ $$ = new ExpStatement($1); }
| BREAK ';'		{ $$ = new Break(); }
| CONTINUE ';'		{ $$ = new Continue(); }
| RETURN ';'		{ $$ = new Return(NULL); }
| RETURN exp ';'	{ $$ = new Return($2); }
;

/* block */ 
stat_lst
:		{ $$ = new std::vector<Statement*>(); }
| stat_lst stat	{ $1->push_back($2); $$ = $1; }
;

block_stat
: '{' stat_lst '}'	{ $$ = new Block($2); }
;

/* declaration */
decl
: id		{ $$ = new Declarator($1, NULL); }
| id '=' exp 	{ $$ = new Declarator($1, $3); }
;

decl_lst
: decl			{ $$ = new std::vector<Declarator*>(); $$->push_back($1); }
| decl_lst ',' decl	{ $1->push_back($3); $$ = $1; }
;

decl_stat
: type decl_lst ';'	{ $$ = new Declaration($1, $2); }
;

decl_stat_lst
:				{ $$ = new std::vector<Declaration*>(); }
| decl_stat_lst decl_stat	{ $1->push_back($2); $$ = $1; }
;

decl_block
: '{' decl_stat_lst '}'	{ $$ = $2; }
;

/* if */
if_stat
: IF '(' exp ')' block_stat			{ $$ = new IfStatement($3, $5, NULL); }
| IF '(' exp ')' block_stat ELSE block_stat	{ $$ = new IfStatement($3, $5, $7); }
| IF '(' exp ')' block_stat ELSE if_stat	{ $$ = new IfStatement($3, $5, $7); }
;

/* while */
while_stat
: WHILE '(' exp ')' block_stat	{ $$ = new WhileStatement($3, $5); }
;

/* function */
formal_para
: type id	{ $$ = new FormalParameter($1, $2); }
;

formal_para_lst
:				{ $$ = new std::vector<FormalParameter*>(); }
| formal_para_lst formal_para	{ $1->push_back($2); $$ = $1; }
;

function_header
: type id '(' formal_para_lst ')'	{ $$ = new FunctionHeader($1, $2, $4); }
;

function_decl
: function_header block_stat	{ $$ = new FunctionDeclaration($1, $2); }
;

/* struct and union */
struct_name
: STRUCT id	{ $$ = $2; }
;

struct_decl
: struct_name decl_block	{ $$ = new StructDeclaration($1, $2); }
;

/* top level statement */
top_level_stat
: function_decl	{ astLst.push_back($1); }
| struct_decl   { astLst.push_back($1); yyget_extra(scanner)->insert(*($1->id->name)); }
;

program
: 
| program top_level_stat
;
%%

#include <unordered_set>
#include <iostream>

void yyerror(YYLTYPE* yyllocp, void* scanner, std::vector<Ast*> &ret, const char* msg) {
    printf("[%d:%d]: %s\n", yyllocp->first_line, yyllocp->first_column, msg);
}

void parse(std::vector<Ast*> &astLst, FILE *file) {
    yyscan_t scanner;
    std::unordered_set<std::string> types;
    yylex_init_extra(&types, &scanner);
    yyset_in(file, scanner);

    astLst.clear();
    int rst = yyparse(scanner, astLst);
    yylex_destroy(scanner);
    if (rst != 0) {
        std::cout << "Parse failed!" << std::endl;
    }
}

