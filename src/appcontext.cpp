#include "appcontext.hpp"

#include <boost/beast/core/file.hpp>

#include "config.hpp"
#include "logging.hpp"

#if __cpp_lib_execution //checking to see if the <execution> header is there
#include <execution>
#endif

namespace kc {

AppContext::AppContext(): config_loaded(false) {
}

void AppContext::load_config(const int argc, const char *argv[])
{
    config = init_config(argc, argv);
    config_loaded = true;
}

void AppContext::load_and_parse_cache() {
    load_and_parse_cache(ParseOperations::ALL);
}

void AppContext::load_and_parse_cache(ParseOperations operations)
{
    if (!config->contains("path")) {
        print_and_log_error("No paths provided");
        return;
    }

    const auto env_paths = (*config)["path"].as<std::vector<std::string>>();

#ifdef __cpp_lib_execution
    std::mutex m;
    std::for_each(std::execution::par, env_paths.begin(), env_paths.end(), [this, &operations, &m](const std::string &env_path)
#else
    std::ranges::for_each(env_paths, [this, &operations](const std::string &env_path)
#endif
    {
        print_and_log("Loading knowledge base from " + env_path);

        const auto file_cache = std::make_shared<kc::FileContextCache>();
        file_cache->load(env_path);
        file_cache->parse_all(operations);

#ifdef __cpp_lib_execution
        std::lock_guard<std::mutex> lock{m};
#endif
        file_caches.push_back(file_cache);
    });
}

std::string AppContext::command() const {
    if (config->count("command") == 1)
    {
        return (*config)["command"].as<std::string>();
    }
    return "";
}

}