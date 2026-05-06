#pragma once

#include <string>
#include <string_view>

#include "task.h"

namespace calc
{

class Parser
{
public:
     explicit Parser( std::string_view raw );

     Task Parse() const;

     static void PrintUsage( const char* prog );

private:
     std::string raw_;
};

}// namespace calc