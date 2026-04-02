
#include <getopt.h>

#include <math/math.h>

struct Task {
     char* firstValue = nullptr;
     char* secondValue = nullptr;
     char* operation = nullptr;
     long result = 0;
};

bool parse( int argc, char* argv[], struct Task* task )
{
     static struct option long_options[] = { { "first", required_argument, nullptr, 'f' },
                                             { "second", required_argument, nullptr, 's' },
                                             { "operation", required_argument, nullptr, 'w' },
                                             { nullptr, 0, nullptr, 0 } };

     int opt;
     int option_index = 0;

     while( ( opt = getopt_long( argc, argv, "f:s:w:", long_options, &option_index ) ) != -1 )
     {
          switch( opt )
          {
          case 'f':
               task->firstValue = optarg;
               break;

          case 's':
               task->secondValue = optarg;
               break;

          case 'w':
               task->operation = optarg;
               break;

          default:
               return false;
          }
     }

     return task->firstValue != nullptr && task->operation != nullptr;
}

bool check_int( const char* str )
{
     char* endptr = nullptr;
     errno = 0;

     strtol( str, &endptr, 10 );

     return errno == 0 && endptr != str && *endptr == '\0';
}

bool check_operation( const char* operation )
{
     return ( strcmp( operation, "addition" ) == 0 || strcmp( operation, "subtraction" ) == 0 ||
              strcmp( operation, "multiplication" ) == 0 || strcmp( operation, "division" ) == 0 ||
              strcmp( operation, "power" ) == 0 || strcmp( operation, "factorial" ) == 0 );
}

bool check( struct Task* task )
{
     if( !check_int( task->firstValue ) )
     {
          printf( "Invalid number for --first\n" );
          return false;
     }

     if( task->secondValue != nullptr )
     {
          if( !check_int( task->secondValue ) )
          {
               printf( "Invalid number for --second\n" );
               return false;
          }
     }

     if( !check_operation( task->operation ) )
     {
          printf(
               "Invalid value for --operation. Allowed: addition, subtraction, "
               "multiplication, division, power, factorial.\n" );
          return false;
     }

     return true;
}

bool calculate( struct Task* task )
{
     long firstValue = strtol( task->firstValue, nullptr, 10 );

     if( strcmp( task->operation, "addition" ) == 0 )
     {
          if( task->secondValue == nullptr )
          {
               printf( "For addition operation need second argument!\n" );
               return false;
          }
          long secondValue = strtol( task->secondValue, nullptr, 10 );
          return math::addition( firstValue, secondValue, &( task->result ) );
     }

     if( strcmp( task->operation, "subtraction" ) == 0 )
     {
          if( task->secondValue == nullptr )
          {
               printf( "For subtraction operation need second argument!\n" );
               return false;
          }
          long secondValue = strtol( task->secondValue, nullptr, 10 );
          return math::subtraction( firstValue, secondValue, &( task->result ) );
     }

     if( strcmp( task->operation, "multiplication" ) == 0 )
     {
          if( task->secondValue == nullptr )
          {
               printf( "For multiplication operation need second argument!\n" );
               return false;
          }
          long secondValue = strtol( task->secondValue, nullptr, 10 );
          return math::multiplication( firstValue, secondValue, &( task->result ) );
     }

     if( strcmp( task->operation, "division" ) == 0 )
     {
          if( task->secondValue == nullptr )
          {
               printf( "For division operation need second argument!\n" );
               return false;
          }
          long secondValue = strtol( task->secondValue, nullptr, 10 );
          return math::division( firstValue, secondValue, &( task->result ) );
     }

     if( strcmp( task->operation, "power" ) == 0 )
     {
          if( task->secondValue == nullptr )
          {
               printf( "For power operation need second argument!\n" );
               return false;
          }
          long secondValue = strtol( task->secondValue, nullptr, 10 );
          return math::power( firstValue, secondValue, &( task->result ) );
     }

     if( strcmp( task->operation, "factorial" ) == 0 )
     {
          return math::factorial( firstValue, &( task->result ) );
     }

     printf( "None of operations run!\n" );
     return false;
}

int main( int argc, char* argv[] )
{
     struct Task task;

     if( !parse( argc, argv, &task ) )
     {
          printf(
               "Usage: %s --first <num> [--second <num>] --operation "
               "<addition|subtraction|multiplication|division|power|factorial.>\n",
               argv[ 0 ] );
          return 1;
     }

     if( !check( &task ) )
     {
          return 1;
     }

     if( !calculate( &task ) )
     {
          return 1;
     }

     long firstValue = strtol( task.firstValue, nullptr, 10 );

     if( task.secondValue != nullptr )
     {
          long secondValue = strtol( task.secondValue, nullptr, 10 );
          printf( "first = %ld, second = %ld, operation = %s, result = %ld\n",
                  firstValue,
                  secondValue,
                  task.operation,
                  task.result );
     }
     else
     {
          printf( "first = %ld, operation = %s, result = %ld\n", firstValue, task.operation, task.result );
     }

     return 0;
}
