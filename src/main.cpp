﻿#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <regex>

#include "const.hpp"
#include "logging.hpp"
#include "config.hpp"
#include "fs/fs.hpp"
#include "parse/FileContextCache.hpp"
#include "valid/link.hpp"

void run_validate(std::shared_ptr<boost::program_options::variables_map> config);


int main(int argc, const char *argv[]) {
    
    init_logging();

    BOOST_LOG_TRIVIAL(info) << "================================";
    BOOST_LOG_TRIVIAL(info) << "              kc";
    BOOST_LOG_TRIVIAL(info) << "================================";
    BOOST_LOG_TRIVIAL(info) << "starting up....";

    auto config = init_config(argc, argv);

    if(config)
    {
        if (config->count("command") == 1)
        {
            auto command = (*config)["command"].as<std::string>();

            if (command == "validate")
            {
                run_validate(config);
            }
        }
        else
        {
            BOOST_LOG_TRIVIAL(info) << "command not found";
        }
    }
}

void run_validate(std::shared_ptr<boost::program_options::variables_map> config)
{
    auto env_path = (*config)["path"].as<std::string>();
    BOOST_LOG_TRIVIAL(info) << "Loading knowledge base from " << env_path;

    auto file_cache = kc::FileContextCache();
    file_cache.load(env_path);
    file_cache.parse_all();

    kc::validate_links(file_cache.get());
}