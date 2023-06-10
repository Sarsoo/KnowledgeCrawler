#pragma once

#include <string>
#include <regex>

namespace kc {

class Link {
    public:

    std::string original_form;
    std::string display;
    std::string link;
    std::string sublink;

    Link(std::string original);

    private:
};

}