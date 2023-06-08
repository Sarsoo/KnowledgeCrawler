#pragma once

#include <string>
#include <filesystem>
namespace fs = std::filesystem;

namespace kc {

class FileEntry {
    public:

    fs::directory_entry file_entry;
    fs::path relative_path;

    bool content_loaded();
    std::string load_content();
    std::string get_content();
    void clear_content();

    private:

    std::string file_content;
};

}