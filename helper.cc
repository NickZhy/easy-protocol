#include <iostream>
#include "ast.hh"
#include "parser.tab.hh"
#include "helper.hh"

std::string type2str(PrimitiveType type) {
    const char *str;
    switch (type) {
	case TYP_BOOL:
	    str = "bool";
	    break;
	case TYP_BYTE: 
	    str = "byte";
	    break;
	case TYP_SHORT:
	    str = "short";
	    break;
	case TYP_INT: 
	    str = "int";
	    break;
	case TYP_LONG:
	    str = "long";
	    break;
	case TYP_FLOAT: 
	    str = "float";
	    break;
	case TYP_DOUBLE:
	    str = "double";
	    break;
    }
    return std::string(str);
}


std::string op2str(int op) {
    const char *str;
    switch (op) {
	case '+':
	    str = "+";
	    break;
	case '-':
	    str = "-";
	    break;
	case '*':
	    str = "*";
	    break;
	case '/':
	    str = "/";
	    break;
    	case '%':
	    str = "%";
	    break;
	case '^':
	    str = "^";
	    break;
	case '&':
	    str = "&";
	    break;
    	case '|':
	    str = "|";
	    break;
    	case '~':
	    str = "~";
	    break;
    	case '!':
	    str = "!";
	    break;
    	case '<':
	    str = "<";
	    break;
	case '>':
	    str = ">";
	    break;
	case '=':
	    str = "=";
	    break;
	case INC:
	    str = "++";
	    break;
	case DEC:
	    str = "--";
	    break;
	case LSH:
	    str = "<<";
	    break;
	case RSH:
	    str = ">>";
	    break;
	case LE:
	    str = "<=";
	    break;
	case GE:
	    str = ">=";
	    break;
	case EQ:
	    str = "==";
	    break;
	case NEQ:
	    str = "!=";
	    break;
	case ADD_ASG:
	    str = "+=";
	    break;
	case SUB_ASG:
	    str = "-=";
	    break;
	case MUL_ASG:
	    str = "+=";
	    break;
	case DIV_ASG:
	    str = "/=";
	    break;
	case MOD_ASG:
	    str = "%=";
	    break;
	case XOR_ASG:
	    str = "^=";
	    break;
	case AND_ASG:
	    str = "&=";
	    break;
	case OR_ASG:
	    str = "|=";
	    break;
	case LSH_ASG:
	    str = "<<=";
	    break;
	case RSH_ASG:
	    str = ">>=";
	    break;
	default:
	    str = "unknown";
    }
    return std::string(str);
}

