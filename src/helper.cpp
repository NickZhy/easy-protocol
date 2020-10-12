#include <iostream>
#include "ast.hpp"
#include "helper.hpp"

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

std::string op2str(UnaryOperator op) {
    const char *str;
    switch(op) {
        case OP_POS:
            str = "+";
            break;
        case OP_NEG:
            str = "-";
            break;
        case OP_NOT:
            str = "!";
            break;
        case OP_BNOT:
            str = "~";
            break;
        case OP_PRE_INC:
        case OP_POS_INC:
            str = "++";
            break;
        case OP_PRE_DEC:
        case OP_POS_DEC:
            str = "--";
            break;
        default:
            str = "unknown_una_op ";
            }
    return std::string(str);
}

std::string op2str(BinaryOperator op) {
    const char *str;
    switch (op) {
        case OP_ADD:
            str = "+";
            break;
        case OP_SUB:
            str = "-";
            break;
        case OP_MUL:
            str = "*";
            break;
        case OP_DIV:
            str = "/";
            break;
        case OP_MOD:
            str = "%";
            break;
        case OP_BXOR:
            str = "^";
            break;
        case OP_BAND:
            str = "&";
            break;
        case OP_BOR:
            str = "|";
            break;
        case OP_LSH:
            str = "<<";
            break;
        case OP_RSH:
            str = ">>";
            break;
        case OP_LT:
            str = "<";
            break;
        case OP_GR:
            str = ">";
            break;
        case OP_LE:
            str = "<=";
            break;
        case OP_GE:
            str = ">=";
            break;
        case OP_EQ:
            str = "==";
            break;
        case OP_NEQ:
            str = "!=";
            break;
        default:
            str = "unknown_bin_op ";
    }
    return std::string(str);
}

std::string op2str(AssignOperator op) {
    const char *str;
    switch (op) {
        case ASG_ADD:
            str = "+=";
            break;
        case ASG_SUB:
            str = "-=";
            break;
        case ASG_MUL:
            str = "*=";
            break;
        case ASG_DIV:
            str = "/=";
            break;
        case ASG_MOD:
            str = "%=";
            break;
        case ASG_XOR:
            str = "^=";
            break;
        case ASG_AND:
            str = "&=";
            break;
        case ASG_OR:
            str = "|=";
            break;
        case ASG_LSH:
            str = "<<=";
            break;
        case ASG_RSH:
            str = ">>=";
            break;
        default:
            str = "unknown_asg_op ";
    }
    return std::string(str);
}
