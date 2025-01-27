#include "config.hpp"

#include <memory>
#include <fstream>
#include <iostream>

#include <boost/program_options.hpp>

std::shared_ptr<po::variables_map> init_config(int argc, const char *argv[])
{
    try {
        po::options_description desc("Config");
        desc.add_options()
            ("help", "produce help message")
            ("path,p", po::value<std::vector<std::string>>(), "set root path of knowledge base")
            ("config", po::value<std::string>()->default_value("kc.ini"), "config file location")
            ("out,o", po::value<std::string>()->default_value("."), "output file location")
            ("command", po::value<std::string>(), "command to execute")
            ("subargs", po::value<std::vector<std::string> >(), "Arguments for command")
            ("index", po::value<int>()->default_value(1), "index")
        ;

        po::positional_options_description pos;
        pos.add("command", 1).add("subargs", -1);

        po::options_description cmdline_options;
        cmdline_options.add(desc);

        po::options_description config_file_options;
        config_file_options.add(desc);

        ////////////
        // PARSE
        ////////////

        auto vm = std::make_shared<po::variables_map>();
        po::store(po::command_line_parser(argc, argv)
                .options(cmdline_options)
                .positional(pos)
                // .allow_unregistered()
                .run(), 
            *vm);

        if (vm->contains("config"))
        {
            auto config_path = (*vm)["config"].as<std::string>();
            BOOST_LOG_TRIVIAL(info) << "Attempting file config load for " << config_path;

            if (std::ifstream ifs{config_path.c_str()}) {
                BOOST_LOG_TRIVIAL(info) << "File opened, loading...";
                po::store(po::parse_config_file(ifs, config_file_options), *vm);
            }
        }
        po::notify(*vm);

        if (vm->contains("help")) {
            std::cout << desc;

            return nullptr;
        }

        return vm;

    }
    catch (const po::error &ex)
    {
        BOOST_LOG_TRIVIAL(error) << ex.what();

        return nullptr;
    }
}