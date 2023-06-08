#pragma once

#include <boost/program_options.hpp>
#include <boost/log/trivial.hpp>

namespace po = boost::program_options;

std::shared_ptr<po::variables_map> init_config(int argc, const char *argv[]);