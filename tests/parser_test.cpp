#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

#include "parser.h"
#include "task.h"

using namespace calc;

// ---------------------------------------------------------------------------
// Корректный разбор бинарных операций
// ---------------------------------------------------------------------------

TEST(ParserTest, ParsesAddition) {
    Parser p(R"({"first": 10, "second": 5, "operation": "addition"})");
    Task task = p.Parse();

    EXPECT_EQ(task.firstValue, 10);
    EXPECT_EQ(task.secondValue, 5);
    EXPECT_EQ(task.operation, OperationType::addition);
}

TEST(ParserTest, ParsesSubtraction) {
    Parser p(R"({"first": 7, "second": 3, "operation": "subtraction"})");
    Task task = p.Parse();

    EXPECT_EQ(task.firstValue, 7);
    EXPECT_EQ(task.secondValue, 3);
    EXPECT_EQ(task.operation, OperationType::subtraction);
}

TEST(ParserTest, ParsesMultiplication) {
    Parser p(R"({"first": 4, "second": 6, "operation": "multiplication"})");
    Task task = p.Parse();

    EXPECT_EQ(task.operation, OperationType::multiplication);
}

TEST(ParserTest, ParsesDivision) {
    Parser p(R"({"first": 20, "second": 4, "operation": "division"})");
    Task task = p.Parse();

    EXPECT_EQ(task.operation, OperationType::division);
}

TEST(ParserTest, ParsesPower) {
    Parser p(R"({"first": 2, "second": 8, "operation": "power"})");
    Task task = p.Parse();

    EXPECT_EQ(task.operation, OperationType::power);
}

// ---------------------------------------------------------------------------
// Унарная операция: factorial — поле second не обязательно
// ---------------------------------------------------------------------------

TEST(ParserTest, ParsesFactorialWithoutSecond) {
    Parser p(R"({"first": 6, "operation": "factorial"})");
    Task task = p.Parse();

    EXPECT_EQ(task.firstValue, 6);
    EXPECT_EQ(task.operation, OperationType::factorial);
}

TEST(ParserTest, ParsesFactorialWithSecondIgnored) {
    // Если second присутствует, он не должен ломать разбор.
    Parser p(R"({"first": 5, "second": 999, "operation": "factorial"})");
    Task task = p.Parse();

    EXPECT_EQ(task.firstValue, 5);
    EXPECT_EQ(task.operation, OperationType::factorial);
}

// ---------------------------------------------------------------------------
// Отрицательные значения и нули
// ---------------------------------------------------------------------------

TEST(ParserTest, ParsesNegativeValues) {
    Parser p(R"({"first": -10, "second": -3, "operation": "addition"})");
    Task task = p.Parse();

    EXPECT_EQ(task.firstValue, -10);
    EXPECT_EQ(task.secondValue, -3);
}

TEST(ParserTest, ParsesZeros) {
    Parser p(R"({"first": 0, "second": 0, "operation": "addition"})");
    Task task = p.Parse();

    EXPECT_EQ(task.firstValue, 0);
    EXPECT_EQ(task.secondValue, 0);
}

// ---------------------------------------------------------------------------
// Невалидный JSON
// ---------------------------------------------------------------------------

TEST(ParserTest, ThrowsOnInvalidJson) {
    Parser p("not a json at all");
    EXPECT_THROW(p.Parse(), std::invalid_argument);
}

TEST(ParserTest, ThrowsOnEmptyString) {
    Parser p("");
    EXPECT_THROW(p.Parse(), std::invalid_argument);
}

TEST(ParserTest, ThrowsOnTruncatedJson) {
    Parser p(R"({"first": 10, "operation":)");
    EXPECT_THROW(p.Parse(), std::invalid_argument);
}

// ---------------------------------------------------------------------------
// Отсутствующие обязательные поля
// ---------------------------------------------------------------------------

TEST(ParserTest, ThrowsWhenFirstMissing) {
    Parser p(R"({"second": 5, "operation": "addition"})");
    EXPECT_THROW(p.Parse(), std::invalid_argument);
}

TEST(ParserTest, ThrowsWhenOperationMissing) {
    Parser p(R"({"first": 10, "second": 5})");
    EXPECT_THROW(p.Parse(), std::invalid_argument);
}

TEST(ParserTest, ThrowsWhenSecondMissingForBinaryOp) {
    Parser p(R"({"first": 10, "operation": "addition"})");
    EXPECT_THROW(p.Parse(), std::invalid_argument);
}

// ---------------------------------------------------------------------------
// Поля неверного типа
// ---------------------------------------------------------------------------

TEST(ParserTest, ThrowsWhenFirstIsString) {
    Parser p(R"({"first": "ten", "second": 5, "operation": "addition"})");
    EXPECT_THROW(p.Parse(), std::invalid_argument);
}

TEST(ParserTest, ThrowsWhenOperationIsNumber) {
    Parser p(R"({"first": 10, "second": 5, "operation": 42})");
    EXPECT_THROW(p.Parse(), std::invalid_argument);
}

TEST(ParserTest, ThrowsWhenSecondIsString) {
    Parser p(R"({"first": 10, "second": "five", "operation": "addition"})");
    EXPECT_THROW(p.Parse(), std::invalid_argument);
}

// ---------------------------------------------------------------------------
// Неизвестная операция
// ---------------------------------------------------------------------------

TEST(ParserTest, ThrowsOnUnknownOperation) {
    Parser p(R"({"first": 10, "second": 5, "operation": "modulo"})");
    EXPECT_THROW(p.Parse(), std::invalid_argument);
}

TEST(ParserTest, ThrowsOnEmptyOperation) {
    Parser p(R"({"first": 10, "second": 5, "operation": ""})");
    EXPECT_THROW(p.Parse(), std::invalid_argument);
}