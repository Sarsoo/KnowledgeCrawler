#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

#include "logging.cpp"
#include "config.cpp"

using namespace std;

int main(int argc, const char *argv[]) {
    try{
        init_logging();

        BOOST_LOG_TRIVIAL(info) << "================================";
        BOOST_LOG_TRIVIAL(info) << "   kc";
        BOOST_LOG_TRIVIAL(info) << "================================";
        BOOST_LOG_TRIVIAL(info) << "starting up....";

        auto config = init_config(argc, argv);

        if(config)
        {
            BOOST_LOG_TRIVIAL(info) << "hello world";
        }
    }
    catch (const po::error &ex)
    {
        BOOST_LOG_TRIVIAL(error) << ex.what();
    }
}