#include "config.hpp"

#include <memory>
#include <fstream>
#include <iostream>

#include <boost/program_options.hpp>

#include "const.hpp"
#include "logging.hpp"

po::options_description get_current_tasks_options() {
    po::options_description options("Current Tasks");
    options.add_options()
        (CONFIG_NOTIFY.c_str(), po::bool_switch(), "send notification to notify")
        (CONFIG_HOST.c_str(), po::value<std::string>(), "ntfy hostname")
        (CONFIG_TOPIC.c_str(), po::value<std::string>(), "ntfy topic name")
        (CONFIG_TITLE.c_str(), po::value<std::string>(), "title for notifications")
        (CONFIG_TAGS.c_str(), po::value<std::vector<std::string>>(), "tags to add to notification")
    ;

    return options;
}

std::shared_ptr<po::variables_map> init_config(int argc, const char *argv[])
{
    try {
        po::options_description visible_general("KC Config");
        visible_general.add_options()
            ("help,h", "produce help message")
            ("path,p", po::value<std::vector<std::string>>(), "set root path of knowledge base")
            ("config", po::value<std::string>()->default_value("kc.ini"), "config file location")
            ("logpath", po::value<std::string>()->default_value("."), "log folder location")
        ;

        po::options_description hidden_general("Hidden");
        hidden_general.add_options()
            ("command", po::value<std::string>(), "command to execute")
        ;

        po::positional_options_description positional;
        positional.add("command", 1);

        auto current_tasks_options = get_current_tasks_options();

        /////////
        // CMD
        /////////
        po::options_description cmdline_options;
        cmdline_options
            .add(visible_general)
            .add(hidden_general)
            .add(current_tasks_options)
        ;

        /////////
        // FILE
        /////////
        po::options_description config_file_options;
        config_file_options
            .add(visible_general)
            .add(hidden_general)
            .add(current_tasks_options)
        ;

        ////////////
        // PARSE
        ////////////

        auto vm = std::make_shared<po::variables_map>();
        po::store(po::command_line_parser(argc, argv)
                .positional(positional)
                .options(cmdline_options)
                // .allow_unregistered()
                .run(),
            *vm);

        if (vm->contains("config"))
        {
            auto config_path = (*vm)["config"].as<std::string>();
            // BOOST_LOG_TRIVIAL(info) << "Attempting file config load for " << config_path;

            if (std::ifstream ifs{config_path.c_str()}) {
                // BOOST_LOG_TRIVIAL(info) << "File opened, loading...";
                po::store(po::parse_config_file(ifs, config_file_options), *vm);
            }
        }
        po::notify(*vm);

        if (vm->contains("help")) {

            if (vm->count("command") == 1)
            {
                auto command = (*vm)["command"].as<std::string>();

                if (command == CMD_CURRENT_TASKS) {
                    std::cout << visible_general << std::endl << current_tasks_options;
                }
            }
            else
            {
                std::cout << visible_general;
            }

            return nullptr;
        }

        return vm;

    }
    catch (const po::error &ex)
    {
        std::cout << ex.what() << std::endl;

        return nullptr;
    }
}