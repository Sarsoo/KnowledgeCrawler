#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "const.hpp"
#include "logging.hpp"
#include "config.hpp"
#include "appcontext.hpp"
#include "net/http.hpp"
#include "parse/FileContextCache.hpp"
#include "print/print.hpp"
#include "task/current_tasks.hpp"
#include "valid/link.hpp"

#ifdef WITH_OPENCV
#include "image/img.hpp"
#endif

void run_validate(const kc::AppContext &app_context);
void run_img(const kc::AppContext &app_context);
void run_print(const kc::AppContext &app_context);
int run_current_tasks(const kc::AppContext &app_context);


int main(int argc, const char *argv[]) {

    kc::AppContext app_context;
    app_context.load_config(argc, argv);

    init_logging((*app_context.config)["logpath"].as<std::string>());

    try {
        BOOST_LOG_TRIVIAL(info) << "================================";
        BOOST_LOG_TRIVIAL(info) << "              kc";
        BOOST_LOG_TRIVIAL(info) << "================================";
        BOOST_LOG_TRIVIAL(info) << "Starting up....";

#ifdef __cpp_lib_execution
        BOOST_LOG_TRIVIAL(debug) << "Compiled with parallel loops";
#else
        BOOST_LOG_TRIVIAL(debug) << "Compiled WITHOUT parallel loops";
#endif

        if(app_context.config)
        {
            const auto command = app_context.command();
            if (!command.empty())
            {
                if (command == CMD_VALIDATE_TASKS)
                {
                    app_context.load_and_parse_cache(kc::LINKS);
                    run_validate(app_context);
                }
#ifdef WITH_OPENCV
                else if (command == CMD_IMG_TASKS)
                {
                    app_context.load_and_parse_cache(kc::IMAGES);
                    run_img(app_context);
                }
#endif
                else if (command == CMD_PRINT_TASKS)
                {
                    app_context.load_and_parse_cache();
                    run_print(app_context);
                }
                else if (command == CMD_CURRENT_TASKS)
                {
                    app_context.load_and_parse_cache(kc::TASKS);
                    return run_current_tasks(app_context);
                }
            }
            else
            {
                print_and_log_error("Command not found, exiting");
                return 1;
            }

            return 0;
        }
    }
    catch (const std::exception &e) {
        print_and_log_error(std::format("Exception occurred - {}", e.what()));
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
#ifdef WITH_OPENCV
    BOOST_LOG_TRIVIAL(info) << "Running \"Image Processing\" command";
    for(const auto& file_cache : app_context.file_caches) {
        BOOST_LOG_TRIVIAL(info) << "Image processing in " << file_cache->get_root_path();
        kc::image_proc(file_cache->get());
    }
#endif

}

void run_print(const kc::AppContext &app_context)
{
    BOOST_LOG_TRIVIAL(info) << "Running \"Print\" command";
    for(const auto& file_cache : app_context.file_caches) {
        kc::print_file(file_cache->get());
    }
}

int run_current_tasks(const kc::AppContext &app_context)
{
    BOOST_LOG_TRIVIAL(info) << "Running \"Current Tasks\" command";
    return kc::current_tasks(app_context);
}