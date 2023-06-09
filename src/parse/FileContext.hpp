#pragma once

#include <vector>
#include <regex>

#include "../fs/FileEntry.hpp"
#include "Link.hpp"
#include "../const.hpp"

namespace kc {

class FileContext {
    public:

    FileContext(kc::FileEntry entry);

    kc::FileEntry file_entry;
    std::vector<kc::Link> links;
    std::vector<std::string> tags;

    void parse();

    private:

    bool links_parsed;
};

}