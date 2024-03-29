#pragma once

#include <vector>
#include <memory>
#include <regex>
#include <filesystem>

#include "../fs/FileEntry.hpp"
#include "Link.hpp"
#include "../const.hpp"

namespace kc {

class FileContext {
    public:

    explicit FileContext(std::shared_ptr<kc::FileEntry> entry);

    std::shared_ptr<kc::FileEntry> file_entry;
    std::vector<kc::Link> links;
    std::vector<kc::Link> images;
    std::vector<std::string> tags;

    void parse();
    std::filesystem::path abs_path(kc::Link link);

    private:

    bool links_parsed;
};

}