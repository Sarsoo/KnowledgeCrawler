#pragma once

#include <iostream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>

void init_logging(const std::string &log_path);

inline void print_and_log(std::string log_line)
{
    BOOST_LOG_TRIVIAL(info) << log_line;
    std::cout << log_line << std::endl;
}

inline void print_and_log_error(std::string log_line)
{
    BOOST_LOG_TRIVIAL(error) << log_line;
    std::cout << "ERROR: " << log_line << std::endl;
}