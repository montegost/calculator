#pragma once

#include <memory>
#include <string>
#include <string_view>

namespace calc
{

class Logger
{
public:
     static Logger& GetInstance();

     Logger( const Logger& ) = delete;
     Logger& operator=( const Logger& ) = delete;
     Logger( Logger&& ) = delete;
     Logger& operator=( Logger&& ) = delete;

     void Debug( std::string_view msg );
     void Info( std::string_view msg );
     void Error( std::string_view msg );

private:
     Logger();
     ~Logger();

     struct Impl;
     std::unique_ptr<Impl> pImpl;
};

}// namespace calc