#include "logging.hpp"

#include <filesystem>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;
namespace fs = std::filesystem;

void init_logging(const std::string &log_path)
{
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

    auto log_file = std::string(fs::path(log_path) / fs::path("kc_%N.log"));

    logging::add_file_log
    (
        keywords::file_name = log_file,
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