#pragma once

#include <string>
#include <filesystem>

#include "../parse/Link.hpp"

namespace fs = std::filesystem;

namespace kc {

class FileEntry {
    public:

    FileEntry(fs::directory_entry entry);

    fs::directory_entry file_entry;
    fs::path relative_path;

    bool content_loaded() const;
    std::string load_content();
    std::string get_content() const;
    void clear_content();

    private:

    std::string file_content;
    bool loaded;
};

}