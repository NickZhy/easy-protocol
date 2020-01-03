%option noyywrap
%option reentrant
%option yylineno
%option bison-bridge
%option bison-locations

%{
    #include "parser.tab.hh"
    
    #define YY_USER_ACTION                                                  \
        yylloc->first_line = yylloc->last_line;                             \
        yylloc->first_column = yylloc->last_column;                         \
        if (yylloc->last_line == yylineno)                                  \
            yylloc->last_column += yyleng;                                  \
        else {                                                              \
            yylloc->last_line = yylineno;                                   \
            yylloc->last_column = yytext + yyleng - strrchr(yytext, '\n');  \
        }
%}

EXP	([Ee][-+]?[0-9]+)

%%

"bool"	{ yylval->priType = TYP_BOOL; return TYPE; }
"byte"	{ yylval->priType = TYP_BYTE; return TYPE; }
"short"	{ yylval->priType = TYP_SHORT; return TYPE; }
"int"	{ yylval->priType = TYP_INT; return TYPE; }
"long"	{ yylval->priType = TYP_LONG; return TYPE; }
"float"	{ yylval->priType = TYP_FLOAT; return TYPE; }
"double"	{ yylval->priType = TYP_DOUBLE; return TYPE; }

"if"	{ return IF; }
"else"	{ return ELSE; }
"while"	{ return WHILE; }

"break"		{ return BREAK; }
"continue"	{ return CONTINUE; }
"return"	{ return RETURN; }

"struct"	{ return STRUCT; }


"+" | 
"-" |
"*" |
"/" |
"%" |

"^" |
"&" |
"|" |

"~" |
"!" |

"." |
"<" |
">" |
":" |

"(" |
")" |
"[" |
"]" |
"{" |
"}" |
"=" |
"," |
";"	{ return yytext[0]; }

"&&"	{ return AND; }
"||"	{ return OR; }

"++"	{ return INC; }
"--"	{ return DEC; }

"<<"	{ return LSH; }
">>"	{ return RSH; }

"<="	{ return LE; }
">="	{ return GE; }
"=="	{ return EQ; }
"!="	{ return NEQ; }

"+="	{ return ADD_ASG; }
"-="	{ return SUB_ASG; }
"*="	{ return MUL_ASG; }
"/="	{ return DIV_ASG; }
"%="	{ return MOD_ASG; }
"^="	{ return XOR_ASG; }
"&="	{ return AND_ASG; }
"|="	{ return OR_ASG; }
"<<="	{ return LSH_ASG; }
">>="	{ return RSH_ASG; }

[a-zA-Z_]+[a-zA-Z_0-9]*	{ yylval->strVal = yytext; return ID; }
[0-9]+	                { yylval->intVal = atoi(yytext); return INT_CON; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}?	{ yylval->floatVal = atof(yytext); return FLOAT_CON; }

[ \t]+	{ }
\n	{ }

<<EOF>> { return TOK_EOF; }
%%
