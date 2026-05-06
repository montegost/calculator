#pragma once

namespace calc
{

enum class OperationType
{
     addition,
     subtraction,
     multiplication,
     division,
     power,
     factorial
};

struct Task {
     long firstValue = 0;
     long secondValue = 0;
     OperationType operation = OperationType::addition;
};

}// namespace calc