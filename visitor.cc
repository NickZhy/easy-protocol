#include "helper.hh"
#include "visitor.hh"

ToStringVisitor::ToStringVisitor(): indentLevel(0) {}

const std::string ToStringVisitor::INDENT = "    ";

void ToStringVisitor::clear() {
    result.clear();
}

std::string ToStringVisitor::getResult() {
    return result;
}

void ToStringVisitor::visitIdentifier(Identifier *id) {
    result.append(*(id->name));
}

void ToStringVisitor::visitType(Type *type) {
    if (type->isPrimitive) {
        result.append(type2str(type->priType));
    } else {
        type->refType->accept(this);
    }
    if(type->dims != nullptr) {
        visitVec(type->dims, "", "[", "]");
    }
}

void ToStringVisitor::visitConstant(Constant *constant) {
    if(constant->type == TYP_BOOL) {
	result.append(constant->intVal != 0 ? "true" : "false");
    } else {
        result.append(std::to_string(constant->intVal));
        switch(constant->type) {
	    case TYP_BYTE:
                result.push_back('B');
                break;
            case TYP_SHORT:
                result.push_back('S');
                break;
            case TYP_INT:
                result.push_back('I');
                break;
            case TYP_LONG:
                result.push_back('L');
                break;
            case TYP_FLOAT:
                result.push_back('F');
                break;
            case TYP_DOUBLE:
                result.push_back('D');
                break;
            default:
                result.append("<illegal type>");
        }
    }
}

void ToStringVisitor::visitFunctionCall(FunctionCall *functionCall) {
    functionCall->func->accept(this);
    result.push_back('(');
    visitVec(functionCall->args, ", ");
    result.push_back(')');
}

void ToStringVisitor::visitIndexOf(IndexOf *indexOf) {
    indexOf->var->accept(this);
    result.push_back('[');
    indexOf->idx->accept(this);
    result.push_back(']');
}

void ToStringVisitor::visitAccess(Access *access) {
    result.push_back('(');
    access->var->accept(this);
    result.push_back('.');
    access->field->accept(this);
    result.push_back(')');
}

void ToStringVisitor::visitTypeCast(TypeCast *typeCast) {
    result.push_back('(');
    typeCast->type->accept(this);
    result.push_back(' ');
    typeCast->expr->accept(this);
    result.push_back(')');
}

void ToStringVisitor::visitUnaOp(UnaOp *unaOp) {
    result.push_back('(');
    if(unaOp->op == OP_POS_INC || unaOp->op == OP_POS_DEC) {
        unaOp->expr->accept(this);
        result.append(op2str(unaOp->op));
    } else {
        result.append(op2str(unaOp->op));
        unaOp->expr->accept(this);
    }
    result.push_back(')');
}

void ToStringVisitor::visitBinOp(BinOp *binOp) {
    result.push_back('(');
    binOp->left->accept(this);
    result.append(" " + op2str(binOp->op) + " ");
    binOp->right->accept(this);
    result.push_back(')');
}

void ToStringVisitor::visitAssign(Assign *assign) {
    result.push_back('(');
    assign->lval->accept(this);
    result.append(" " + op2str(assign->op) + " ");
    assign->rval->accept(this);
    result.push_back(')');
}

void ToStringVisitor::visitBreak(Break *bk) {
    result.append("break");
}

void ToStringVisitor::visitContinue(Continue *ct) {
    result.append("continue");
}

void ToStringVisitor::visitReturn(Return *r) {
    result.append("return");
    if(r->var != nullptr) {
        result.push_back(' ');
        r->var->accept(this);
    }
}

void ToStringVisitor::visitBlock(Block *block) {
    std::string indents;
    for (int i = 0; i < indentLevel; ++i) {
        indents += INDENT;
    }

    result.append("{\n");
    ++indentLevel;
    visitVec(block->stats, "\n", indents + INDENT);
    --indentLevel;
    result.append("\n" + indents + "}");
}

void ToStringVisitor::visitExpStatement(ExpStatement *expStatement) {
    expStatement->expr->accept(this);
}

void ToStringVisitor::visitDeclarator(Declarator *declarator) {
    declarator->id->accept(this);
    if (declarator->exp != nullptr) {
        result.append(" = ");
        declarator->exp->accept(this);
    }
}

void ToStringVisitor::visitDeclaration(Declaration *declaration) {
    declaration->type->accept(this);
    result.push_back(' ');
    visitVec(declaration->varDecls, " ");
}

void ToStringVisitor::visitIfStatement(IfStatement *ifStatement) {
    result.append("if (");
    ifStatement->condition->accept(this);
    result.append(") ");
    ifStatement->first->accept(this);
    if (ifStatement->second != nullptr) {
        result.append(" else ");
        ifStatement->second->accept(this);
    }
}

void ToStringVisitor::visitWhileStatement(WhileStatement *whileStatement) {
    result.append("while (");
    whileStatement->condition->accept(this);
    result.append(") ");
    whileStatement->body->accept(this);
}

void ToStringVisitor::visitFormalParameter(FormalParameter *formalParameter) {
    formalParameter->type->accept(this);
    result.push_back(' ');
    formalParameter->id->accept(this);
}

void ToStringVisitor::visitFunctionHeader(FunctionHeader *functionHeader) {
    functionHeader->type->accept(this);
    result.push_back(' ');
    functionHeader->id->accept(this);
    result.push_back('(');
    visitVec(functionHeader->paramLst, ", ");
    result.push_back(')');
}

void ToStringVisitor::visitFunctionDeclaration(FunctionDeclaration *functionDeclaration) {
    functionDeclaration->header->accept(this);
    result.push_back(' ');
    functionDeclaration->body->accept(this);
}

void ToStringVisitor::visitStructDeclaration(StructDeclaration *structDeclaration) {
    result.append("struct");
    structDeclaration->id->accept(this);
    result.append(" {\n");
    visitVec(structDeclaration->body, "\n", INDENT);
    result.append("\n}");
}
