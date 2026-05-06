#include "calc.h"

#include <stdexcept>

#include <math/math.h>

#include "task.h"

namespace calc
{

long Calc::Calculate() const
{
     switch( task_.operation )
     {
     case OperationType::addition: {
          return math::addition( task_.firstValue, task_.secondValue );
     }

     case OperationType::subtraction: {
          return math::subtraction( task_.firstValue, task_.secondValue );
     }

     case OperationType::multiplication: {
          return math::multiplication( task_.firstValue, task_.secondValue );
     }

     case OperationType::division: {
          return math::division( task_.firstValue, task_.secondValue );
     }

     case OperationType::power: {
          return math::power( task_.firstValue, task_.secondValue );
     }

     case OperationType::factorial: {
          return math::factorial( task_.firstValue );
     }

     default: {
          throw std::runtime_error( "undefined operation" );
     }
     }
}

Calc::Calc( Task task )
    : task_( task )
{
}

}// namespace calc