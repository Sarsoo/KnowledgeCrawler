#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "const.hpp"
#include "logging.hpp"
#include "config.hpp"
#include "fs/fs.hpp"

int main(int argc, const char *argv[]) {
    
    init_logging();

    BOOST_LOG_TRIVIAL(info) << "================================";
    BOOST_LOG_TRIVIAL(info) << "              kc";
    BOOST_LOG_TRIVIAL(info) << "================================";
    BOOST_LOG_TRIVIAL(info) << "starting up....";

    auto config = init_config(argc, argv);

    if(config)
    {
        auto env_path = (*config)["path"].as<std::string>();
        BOOST_LOG_TRIVIAL(info) << "Loading knowledge base from " << env_path;

        kc::walk_dir(env_path);
    }
}