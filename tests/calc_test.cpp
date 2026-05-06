#include <gtest/gtest.h>

#include "calc.h"
#include "task.h"

using namespace calc;

static Task make_task(long first, long second, OperationType op) {
    Task t;
    t.firstValue = first;
    t.secondValue = second;
    t.operation = op;
    return t;
}

static Task make_unary(long first, OperationType op) {
    Task t;
    t.firstValue = first;
    t.operation = op;
    return t;
}

// ---------------------------------------------------------------------------
// Сложение
// ---------------------------------------------------------------------------

TEST(CalcTest, AdditionPositive) {
    Calc c(make_task(10, 5, OperationType::addition));
    EXPECT_EQ(c.Calculate(), 15);
}

TEST(CalcTest, AdditionWithZero) {
    Calc c(make_task(7, 0, OperationType::addition));
    EXPECT_EQ(c.Calculate(), 7);
}

TEST(CalcTest, AdditionNegative) {
    Calc c(make_task(-10, -5, OperationType::addition));
    EXPECT_EQ(c.Calculate(), -15);
}

TEST(CalcTest, AdditionMixedSigns) {
    Calc c(make_task(10, -3, OperationType::addition));
    EXPECT_EQ(c.Calculate(), 7);
}

// ---------------------------------------------------------------------------
// Вычитание
// ---------------------------------------------------------------------------

TEST(CalcTest, SubtractionPositive) {
    Calc c(make_task(10, 3, OperationType::subtraction));
    EXPECT_EQ(c.Calculate(), 7);
}

TEST(CalcTest, SubtractionResultNegative) {
    Calc c(make_task(3, 10, OperationType::subtraction));
    EXPECT_EQ(c.Calculate(), -7);
}

TEST(CalcTest, SubtractionFromZero) {
    Calc c(make_task(0, 5, OperationType::subtraction));
    EXPECT_EQ(c.Calculate(), -5);
}

// ---------------------------------------------------------------------------
// Умножение
// ---------------------------------------------------------------------------

TEST(CalcTest, MultiplicationPositive) {
    Calc c(make_task(4, 6, OperationType::multiplication));
    EXPECT_EQ(c.Calculate(), 24);
}

TEST(CalcTest, MultiplicationByZero) {
    Calc c(make_task(123, 0, OperationType::multiplication));
    EXPECT_EQ(c.Calculate(), 0);
}

TEST(CalcTest, MultiplicationByOne) {
    Calc c(make_task(42, 1, OperationType::multiplication));
    EXPECT_EQ(c.Calculate(), 42);
}

TEST(CalcTest, MultiplicationNegative) {
    Calc c(make_task(-3, 4, OperationType::multiplication));
    EXPECT_EQ(c.Calculate(), -12);
}

TEST(CalcTest, MultiplicationTwoNegatives) {
    Calc c(make_task(-3, -4, OperationType::multiplication));
    EXPECT_EQ(c.Calculate(), 12);
}

// ---------------------------------------------------------------------------
// Деление
// ---------------------------------------------------------------------------

TEST(CalcTest, DivisionExact) {
    Calc c(make_task(20, 4, OperationType::division));
    EXPECT_EQ(c.Calculate(), 5);
}

TEST(CalcTest, DivisionIntegerTruncation) {
    // Деление целых: 7/2 = 3 (отбрасывание дробной части).
    Calc c(make_task(7, 2, OperationType::division));
    EXPECT_EQ(c.Calculate(), 3);
}

TEST(CalcTest, DivisionByOne) {
    Calc c(make_task(42, 1, OperationType::division));
    EXPECT_EQ(c.Calculate(), 42);
}

TEST(CalcTest, DivisionNegative) {
    Calc c(make_task(-20, 4, OperationType::division));
    EXPECT_EQ(c.Calculate(), -5);
}

// ---------------------------------------------------------------------------
// Возведение в степень
// ---------------------------------------------------------------------------

TEST(CalcTest, PowerPositive) {
    Calc c(make_task(2, 8, OperationType::power));
    EXPECT_EQ(c.Calculate(), 256);
}

TEST(CalcTest, PowerToZero) {
    Calc c(make_task(5, 0, OperationType::power));
    EXPECT_EQ(c.Calculate(), 1);
}

TEST(CalcTest, PowerToOne) {
    Calc c(make_task(7, 1, OperationType::power));
    EXPECT_EQ(c.Calculate(), 7);
}

TEST(CalcTest, PowerOfOne) {
    Calc c(make_task(1, 100, OperationType::power));
    EXPECT_EQ(c.Calculate(), 1);
}

// ---------------------------------------------------------------------------
// Факториал (унарная операция)
// ---------------------------------------------------------------------------

TEST(CalcTest, FactorialOfZero) {
    Calc c(make_unary(0, OperationType::factorial));
    EXPECT_EQ(c.Calculate(), 1);
}

TEST(CalcTest, FactorialOfOne) {
    Calc c(make_unary(1, OperationType::factorial));
    EXPECT_EQ(c.Calculate(), 1);
}

TEST(CalcTest, FactorialOfFive) {
    Calc c(make_unary(5, OperationType::factorial));
    EXPECT_EQ(c.Calculate(), 120);
}

TEST(CalcTest, FactorialIgnoresSecondValue) {
    // Calc должен игнорировать second для унарной операции,
    // даже если он случайно установлен.
    Task t = make_task(5, 999, OperationType::factorial);
    Calc c(t);
    EXPECT_EQ(c.Calculate(), 120);
}