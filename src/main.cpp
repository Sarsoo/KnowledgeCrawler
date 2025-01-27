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
#include "net/http.hpp"
#include "net/ntfy.hpp"
#include "parse/FileContextCache.hpp"
#include "print/print.hpp"
#include "task/current_tasks.hpp"
#include "valid/link.hpp"
//#include "image/img.hpp"

void run_validate(const kc::AppContext &app_context);
void run_img(const kc::AppContext &app_context);
void run_print(const kc::AppContext &app_context);
void run_current_tasks(const kc::AppContext &app_context);
void run_test_net(const kc::AppContext &app_context);


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
                app_context.load_and_parse_cache(kc::LINKS);
                run_validate(app_context);
            }
            else if (command == "img")
            {
                app_context.load_and_parse_cache(kc::IMAGES);
                run_img(app_context);
            }
            else if (command == "print")
            {
                app_context.load_and_parse_cache();
                run_print(app_context);
            }
            else if (command == "current")
            {
                app_context.load_and_parse_cache(kc::TASKS);
                run_current_tasks(app_context);
            }
            else if (command == "net")
            {
                // app_context.load_and_parse_cache(kc::TASKS);
                run_test_net(app_context);
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
    BOOST_LOG_TRIVIAL(info) << "Running \"Validate Links\" command";
    for(const auto& file_cache : app_context.file_caches) {
        BOOST_LOG_TRIVIAL(info) << "Validating links in " << file_cache->get_root_path();
        kc::validate_links(file_cache->get());
    }
}

void run_img(const kc::AppContext &app_context)
{
    BOOST_LOG_TRIVIAL(info) << "Running \"Image Processing\" command";
    for(const auto& file_cache : app_context.file_caches) {
        BOOST_LOG_TRIVIAL(info) << "Image processing in " << file_cache->get_root_path();
        // kc::image_proc(file_cache->get());
    }
}

void run_print(const kc::AppContext &app_context)
{
    BOOST_LOG_TRIVIAL(info) << "Running \"Print\" command";
    for(const auto& file_cache : app_context.file_caches) {
        kc::print_file(file_cache->get());
    }
}

void run_current_tasks(const kc::AppContext &app_context)
{
    BOOST_LOG_TRIVIAL(info) << "Running \"Current Tasks\" command";
    for(const auto& file_cache : app_context.file_caches) {
        BOOST_LOG_TRIVIAL(info) << "Finding current tasks in " << file_cache->get_root_path();
        kc::current_tasks(file_cache->get());
    }
}

void run_test_net(const kc::AppContext &app_context)
{
    kc::notify("ntfy.sheep-ghoul.ts.net",
        kc::Notification("todo", "next test!"));
}