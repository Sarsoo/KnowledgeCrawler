#include "appcontext.hpp"

#include "config.hpp"
#include "logging.hpp"

namespace kc {

AppContext::AppContext()
{

}

void AppContext::load_config(int argc, const char *argv[])
{
    config = init_config(argc, argv);
    config_loaded = true;
}

void AppContext::load_and_parse_cache()
{
    auto env_path = (*config)["path"].as<std::string>();
    print_and_log("> Loading knowledge base from " + env_path);

    file_cache = std::make_shared<kc::FileContextCache>();
    file_cache->load(env_path);
    file_cache->parse_all();
}

std::string AppContext::command()
{
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