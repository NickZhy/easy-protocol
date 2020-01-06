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
    if(type->dims != NULL) {
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
                result.append("B");
                break;
            case TYP_SHORT:
                result.append("S");
                break;
            case TYP_INT:
                result.append("I");
                break;
            case TYP_LONG:
                result.append("L");
                break;
            case TYP_FLOAT:
                result.append("F");
                break;
            case TYP_DOUBLE:
                result.append("D");
                break;
            default:
                result.append("<illegal type>");
        }
    }
}

void ToStringVisitor::visitFunctionCall(FunctionCall *functionCall) {
    functionCall->func->accept(this);
    result.append("(");
    visitVec(functionCall->args, ", ");
    result.append(")");
}

void ToStringVisitor::visitIndexOf(IndexOf *indexOf) {
    indexOf->var->accept(this);
    result.append("[");
    indexOf->exp->accept(this);
    result.append("]");
}

void ToStringVisitor::visitAccess(Access *access) {
    result.append("(");
    access->var->accept(this);
    result.append(".");
    access->field->accept(this);
    result.append(")");
}

void ToStringVisitor::visitTypeCast(TypeCast *typeCast) {
    result.append("(");
    typeCast->type->accept(this);
    result.append(" ");
    typeCast->exp->accept(this);
    result.append(")");
}

void ToStringVisitor::visitUnaOp(UnaOp *unaOp) {
    result.append("(");
    result.append(op2str(unaOp->op));
    unaOp->child->accept(this);
    result.append(")");
}

void ToStringVisitor::visitIncDec(IncDec *incDec) {
    result.append("(");
    if (incDec->isPrefix) {
        result.append(op2str(incDec->op));
        incDec->child->accept(this);
    } else {
        incDec->child->accept(this);
        result.append(op2str(incDec->op));
    }
    result.append(")");
}

void ToStringVisitor::visitBinOp(BinOp *binOp) {
    result.append("(");
    binOp->left->accept(this);
    result.append(" " + op2str(binOp->op) + " ");
    binOp->right->accept(this);
    result.append(")");
}

void ToStringVisitor::visitAssign(Assign *assign) {
    result.append("(");
    assign->lval->accept(this);
    result.append(" " + op2str(assign->op) + " ");
    assign->rval->accept(this);
    result.append(")");
}

void ToStringVisitor::visitBreak(Break *bk) {
    result.append("break");
}

void ToStringVisitor::visitContinue(Continue *ct) {
    result.append("continue");
}

void ToStringVisitor::visitReturn(Return *r) {
    result.append("return");
    if(r->val != NULL) {
        result.append(" ");
        r->val->accept(this);
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
    expStatement->exp->accept(this);
}

void ToStringVisitor::visitDeclarator(Declarator *declarator) {
    declarator->id->accept(this);
    if (declarator->exp != NULL) {
        result.append(" = ");
        declarator->exp->accept(this);
    }
}

void ToStringVisitor::visitDeclaration(Declaration *declaration) {
    declaration->type->accept(this);
    result.append(" ");
    visitVec(declaration->varDecls, " ");
}

void ToStringVisitor::visitIfStatement(IfStatement *ifStatement) {
    result.append("if (");
    ifStatement->condition->accept(this);
    result.append(") ");
    ifStatement->first->accept(this);
    if (ifStatement->second != NULL) {
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
    result.append(" ");
    formalParameter->id->accept(this);
}

void ToStringVisitor::visitFunctionHeader(FunctionHeader *functionHeader) {
    functionHeader->type->accept(this);
    result.append(" ");
    functionHeader->id->accept(this);
    result.append("(");
    visitVec(functionHeader->paramLst, ", ");
    result.append(")");
}

void ToStringVisitor::visitFunctionDeclaration(FunctionDeclaration *functionDeclaration) {
    functionDeclaration->header->accept(this);
    result.append(" ");
    functionDeclaration->body->accept(this);
}

void ToStringVisitor::visitStructDeclaration(StructDeclaration *structDeclaration) {
    result.append("struct");
    structDeclaration->id->accept(this);
    result.append(" {\n");
    visitVec(structDeclaration->body, "\n", INDENT);
    result.append("\n}");
}
