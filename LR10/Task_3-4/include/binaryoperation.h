#ifndef BINARYOPERATION_H
#define BINARYOPERATION_H

#include "expression.h"

class BinaryOperation : public Expression
{
private:
    Expression *left;
    char operation;
    Expression *right;

public:
    BinaryOperation(Expression *left, char operation, Expression *right);
    ~BinaryOperation();

    double evaluate() override;
};

#endif // BINARYOPERATION_H