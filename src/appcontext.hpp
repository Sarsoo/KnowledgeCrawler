#pragma once

#include <memory>
#include <string>

#include <boost/program_options.hpp>

#include "parse/FileContextCache.hpp"

namespace kc {

class AppContext {
public:

    std::shared_ptr<boost::program_options::variables_map> config;
    std::shared_ptr<kc::FileContextCache> file_cache;

    AppContext();

    void load_config(int argc, const char *argv[]);
    void load_and_parse_cache();

    std::string command();

private:

    bool config_loaded;

};

}