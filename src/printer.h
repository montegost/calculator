#pragma once

#include "task.h"

namespace calc
{

class Printer
{
public:
     explicit Printer( Task task );

     void PrintResult( long result ) const;

private:
     Task task_;
};

}// namespace calc