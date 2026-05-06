#include "parser.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <unordered_map>

#include "task.h"

using json = nlohmann::json;

namespace calc
{

static OperationType parse_operation( std::string_view operation )
{
     static const std::unordered_map<std::string_view, OperationType> map{
          { "addition", OperationType::addition },
          { "subtraction", OperationType::subtraction },
          { "multiplication", OperationType::multiplication },
          { "division", OperationType::division },
          { "power", OperationType::power },
          { "factorial", OperationType::factorial },
     };

     auto it = map.find( operation );
     if( it == map.end() )
     {
          throw std::invalid_argument( "unknown operation: " + std::string( operation ) );
     }
     return it->second;
}

static void require_number_field( const json& json, std::string_view field )
{
     if( !json.contains( field ) )
     {
          throw std::invalid_argument( "missing required field: " + std::string( field ) );
     }
     if( !json[ field ].is_number_integer() )
     {
          throw std::invalid_argument( "field must be a number: " + std::string( field ) );
     }
}

Parser::Parser( std::string_view raw )
    : raw_( raw )
{
}

Task Parser::Parse() const
{
     json parsed;
     try
     {
          parsed = json::parse( raw_ );
     }
     catch( const json::parse_error& e )
     {
          throw std::invalid_argument( std::string( "invalid JSON: " ) + e.what() );
     }

     Task task;

     require_number_field( parsed, "first" );
     task.firstValue = parsed[ "first" ].get<long>();

     if( !parsed.contains( "operation" ) )
     {
          throw std::invalid_argument( "missing required field: operation" );
     }
     if( !parsed[ "operation" ].is_string() )
     {
          throw std::invalid_argument( "field must be a string: operation" );
     }
     task.operation = parse_operation( parsed[ "operation" ].get<std::string>() );

     if( task.operation != OperationType::factorial )
     {
          require_number_field( parsed, "second" );
          task.secondValue = parsed[ "second" ].get<long>();
     }

     return task;
}

void Parser::PrintUsage( const char* prog )
{
     std::cerr
          << "Usage: " << prog << " '<json>'\n\n"
          << "JSON format:\n"
          << "  {\n"
          << "    \"first\":     <number>,       // required\n"
          << "    \"second\":    <number>,       // required for binary ops\n"
          << "    \"operation\": \"<op>\"          // required\n"
          << "  }\n\n"
          << "Supported operations:\n"
          << "  addition | subtraction | multiplication | division | power | factorial\n\n"
          << "Example:\n"
          << "  " << prog << " '{\"first\": 10, \"second\": 5, \"operation\": \"addition\"}'\n";
}

}// namespace calc