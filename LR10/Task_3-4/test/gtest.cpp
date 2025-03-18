#include <gtest/gtest.h>

#include "expression.h"
#include "binaryoperation.h"
#include "number.h"
#include "tools.h"

TEST(Expressions, test_1)
{
    Expression *expression = new BinaryOperation(new Number(2.5) , '+', new Number(3));
    ASSERT_EQ(expression->evaluate(), 5.5);
    delete expression;
}

TEST(Expressions, test_2)
{
    Expression *expression = new BinaryOperation(new Number(3) , '+', new BinaryOperation(new Number(4.5), '*', new Number(5)));
    ASSERT_EQ(expression->evaluate(), 25.5);
    delete expression;
}

TEST(Expressions, test_3)
{
    Expression *expression = new BinaryOperation(new Number(2) , '-', new BinaryOperation(new Number(2), '/', new Number(2)));
    ASSERT_EQ(expression->evaluate(), 1);
    delete expression;
}

TEST(Types, test_1)
{
    Expression *first = new BinaryOperation(nullptr, '\0', nullptr);
    Expression *second = new BinaryOperation(nullptr, '\0', nullptr);
    ASSERT_TRUE(check_equals(first, second));
    delete first;
    delete second;
}

TEST(Types, test_2)
{
    Expression *first = new BinaryOperation(nullptr, '\0', nullptr);
    Expression *second = new Number(0);
    ASSERT_FALSE(check_equals(first, second));
    delete first;
    delete second;
}

TEST(Types, test_3)
{
    Expression *first = new Number(0);
    Expression *second = new Number(0);
    ASSERT_TRUE(check_equals(first, second));
    delete first;
    delete second;
}