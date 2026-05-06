#pragma once

#include "task.h"

namespace calc
{

class Calc
{
public:
     explicit Calc( Task task );

     long Calculate() const;

private:
     Task task_;
};

}// namespace calc