#include "binaryoperation.h"

BinaryOperation::BinaryOperation(Expression *left, char operation, Expression *right) :
    left(left), operation(operation), right(right) {}

BinaryOperation::~BinaryOperation()
{
    delete left;
    delete right;
}

double BinaryOperation::evaluate()
{
    switch (operation)
    {
    case '+':
        return left->evaluate() + right->evaluate();
    case '-':
        return left->evaluate() - right->evaluate();
    case '*':
        return left->evaluate() * right->evaluate();
    case '/':
        return left->evaluate() / right->evaluate();
    default:
        return 0;
    }
}