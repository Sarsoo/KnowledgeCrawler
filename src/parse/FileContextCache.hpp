#pragma once

#include <vector>
#include <memory>
#include "FileContext.hpp"

namespace kc {

class FileContextCache {
    public:
    void load(std::string root_path);
    void clear();
    size_t size();
    std::vector<std::shared_ptr<kc::FileContext>> get();
    void parse_all();

    private:
    std::vector<std::shared_ptr<kc::FileContext>> file_contexts;
};

}