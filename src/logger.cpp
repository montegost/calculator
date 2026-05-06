#include "logger.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <vector>

namespace calc
{

struct Logger::Impl {
     std::shared_ptr<spdlog::logger> logger;

     Impl()
     {
          auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
          auto file = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
               "calculator.log", /*truncate=*/false );

          std::vector<spdlog::sink_ptr> sinks{ console, file };
          logger = std::make_shared<spdlog::logger>( "calculator",
                                                     sinks.begin(), sinks.end() );

          logger->set_pattern( "[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v" );
          logger->set_level( spdlog::level::info );
          logger->flush_on( spdlog::level::warn );
     }
};

Logger::Logger() : pImpl( std::make_unique<Impl>() )
{
}
Logger::~Logger() = default;

Logger& Logger::GetInstance()
{
     static Logger inst;
     return inst;
}

void Logger::Debug( std::string_view msg )
{
     pImpl->logger->debug( msg );
}
void Logger::Info( std::string_view msg )
{
     pImpl->logger->info( msg );
}
void Logger::Error( std::string_view msg )
{
     pImpl->logger->error( msg );
}

}// namespace calc