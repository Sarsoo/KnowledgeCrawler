#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "FileContext.hpp"

namespace kc {

class FileContextCache {
    public:
    void load(const std::string &root_path);
    void clear();
    [[nodiscard]] size_t size() const;
    [[nodiscard]] std::vector<std::shared_ptr<kc::FileContext>> get() const;
    void parse_all();
    [[nodiscard]] std::string get_root_path() const;

    std::unordered_map<std::string, std::vector<std::shared_ptr<kc::FileEntry>>> tag_map;

    private:
    std::vector<std::shared_ptr<kc::FileContext>> file_contexts;
    std::string root_path;
};

}