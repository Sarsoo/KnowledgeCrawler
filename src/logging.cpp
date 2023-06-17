#include "logging.hpp"

#include <iostream>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

void init_logging()
{
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

    logging::add_file_log
    (
        keywords::file_name = "kc_%N.log",
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
        keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%",
        keywords::open_mode = std::ios::app
    );

    // logging::add_console_log(std::cout, boost::log::keywords::format = "[%TimeStamp%] [%Severity%] >> %Message%");

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::debug
    );

    logging::add_common_attributes();
}

inline void print_and_log(std::string log_line)
{
    BOOST_LOG_TRIVIAL(info) << log_line;
    std::cout << log_line << std::endl;
}