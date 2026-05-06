#include <iostream>
#include <stdexcept>
#include <string>

#include "calc.h"
#include "logger.h"
#include "parser.h"
#include "printer.h"
#include "task.h"

int main( int argc, char* argv[] )
{
     auto& logger = calc::Logger::GetInstance();
     try
     {
          if( argc == 2 && ( std::string( argv[ 1 ] ) == "-h" || std::string( argv[ 1 ] ) == "--help" ) )
          {
               calc::Parser::PrintUsage( argv[ 0 ] );
               return 0;
          }

          if( argc != 2 )
          {
               std::cerr << "Error: expected exactly one argument (JSON string)\n\n";
               calc::Parser::PrintUsage( argv[ 0 ] );
               return 1;
          }

          calc::Parser parser( argv[ 1 ] );
          calc::Task task = parser.Parse();

          logger.Info( "Input json - " + std::string( argv[ 1 ] ) );

          calc::Calc calc( task );
          long result = calc.Calculate();

          calc::Printer printer( task );
          printer.PrintResult( result );

          return 0;
     }
     catch( const std::exception& e )
     {
          logger.Error( e.what() );
          return 1;
     }
     catch( ... )
     {
          logger.Error( "Error: unknown exception" );
          return 1;
     }
}