#pragma once

#include <memory>
#include <string>

#include <boost/program_options.hpp>

#include "parse/FileContextCache.hpp"

namespace kc {

class AppContext {
public:

    std::shared_ptr<boost::program_options::variables_map> config;
    std::vector<std::shared_ptr<kc::FileContextCache>> file_caches;

    AppContext();

    void load_config(int argc, const char *argv[]);
    void load_and_parse_cache();
    void load_and_parse_cache(ParseOperations operations);

    [[nodiscard]] std::string command() const;

private:

    bool config_loaded;

};

}