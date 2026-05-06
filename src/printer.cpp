#include "printer.h"

#include <iostream>

#include "task.h"

namespace calc
{

static const char* operation_symbol( OperationType op )
{
     switch( op )
     {
     case OperationType::addition: {
          return "addition";
     }
     case OperationType::subtraction: {
          return "subtraction";
     }
     case OperationType::multiplication: {
          return "multiplication";
     }
     case OperationType::division: {
          return "division";
     }
     case OperationType::power: {
          return "power";
     }
     case OperationType::factorial: {
          return "factorial";
     }
     }
}

Printer::Printer( Task task )
    : task_( task )
{
}

void Printer::PrintResult( long result ) const
{
     if( task_.operation == OperationType::factorial )
     {
          std::cout << task_.firstValue << "! = " << result << "\n";
     }
     else
     {
          std::cout << task_.firstValue << " "
                    << operation_symbol( task_.operation ) << " "
                    << task_.secondValue << " = " << result << "\n";
     }
}

}// namespace calc