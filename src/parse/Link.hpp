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
    [[nodiscard]] bool is_external() const;

    explicit Link(const std::string &original);

    private:

    bool external;
};

}