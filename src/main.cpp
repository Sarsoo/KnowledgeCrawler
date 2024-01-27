#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <regex>

#include "const.hpp"
#include "logging.hpp"
#include "config.hpp"
#include "appcontext.hpp"
#include "fs/fs.hpp"
#include "parse/FileContextCache.hpp"
#include "valid/link.hpp"
#include "image/img.hpp"

void run_validate(const kc::AppContext &app_context);
void run_img(const kc::AppContext &app_context);


int main(int argc, const char *argv[]) {
    
    init_logging();

    BOOST_LOG_TRIVIAL(info) << "================================";
    BOOST_LOG_TRIVIAL(info) << "              kc";
    BOOST_LOG_TRIVIAL(info) << "================================";
    BOOST_LOG_TRIVIAL(info) << "Starting up....";

    kc::AppContext app_context;
    app_context.load_config(argc, argv);

    if(app_context.config)
    {
        const auto command = app_context.command();
        if (!command.empty())
        {
            if (command == "validate")
            {
                app_context.load_and_parse_cache();
                run_validate(app_context);
            }
            else if (command == "img")
            {
                app_context.load_and_parse_cache();
                run_img(app_context);
            }
        }
        else
        {
            print_and_log_error("Command not found, exiting");
            return 1;
        }

        return 0;
    }

    return 1;
}

void run_validate(const kc::AppContext &app_context)
{
    kc::validate_links(app_context.file_cache->get());
}

void run_img(const kc::AppContext &app_context)
{
    kc::image_proc(app_context.file_cache->get());
}