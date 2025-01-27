#include "appcontext.hpp"

#include <boost/beast/core/file.hpp>

#include "config.hpp"
#include "logging.hpp"

namespace kc {

AppContext::AppContext(): config_loaded(false) {
}

void AppContext::load_config(int argc, const char *argv[])
{
    config = init_config(argc, argv);
    config_loaded = true;
}

void AppContext::load_and_parse_cache() {
    load_and_parse_cache(ParseOperations::ALL);
}

void AppContext::load_and_parse_cache(ParseOperations operations)
{
    const auto env_paths = (*config)["path"].as<std::vector<std::string>>();

    for (const auto& env_path : env_paths) {
        print_and_log("Loading knowledge base from " + env_path);

        auto file_cache = std::make_shared<kc::FileContextCache>();
        file_cache->load(env_path);
        file_cache->parse_all(operations);

        file_caches.push_back(file_cache);
    }
}

std::string AppContext::command() const {
    if (config->count("command") == 1)
    {
        return (*config)["command"].as<std::string>();
    }
    else
    {
        return "";
    }
}

}