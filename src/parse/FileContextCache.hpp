#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "FileContext.hpp"

namespace kc {

class FileContextCache {
    public:
    void load(std::string root_path);
    void clear();
    size_t size() const;
    std::vector<std::shared_ptr<kc::FileContext>> get() const;
    void parse_all();
    std::string get_root_path() const;

    std::unordered_map<std::string, std::vector<std::shared_ptr<kc::FileEntry>>> tag_map;

    private:
    std::vector<std::shared_ptr<kc::FileContext>> file_contexts;
    std::string root_path;
};

}