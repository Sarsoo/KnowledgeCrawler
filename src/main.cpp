#include <vector>
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

        auto file_cache = kc::FileContextCache();
        file_cache.load(env_path);
        file_cache.parse_all();

        auto context = file_cache.get()[(*config)["index"].as<int>()];
        
        std::cout << context->file_entry->get_content() << std::endl << std::endl << std::endl;

        std::cout << "links: " << context->links.size() << std::endl;
        std::cout << "images: " << context->images.size() << std::endl;
        std::cout << "tags: " << context->tags.size() << std::endl << std::endl << std::endl;;

        for (auto link : context->links)
        {
            std::cout << link.original_form << "  " << link.display << " --- " << link.link << std::endl;
        }

        std::cout << "tag cache: " << file_cache.tag_map.size() << std::endl;

        for (auto tag : file_cache.tag_map)
        {
            std::cout << tag.first << ": ";

            for (auto tag_entry: tag.second)
            {
                std::cout << tag_entry->relative_path << ", ";
            }

            std::cout << std::endl;
        }

    }
}