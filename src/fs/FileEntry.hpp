#pragma once

#include <string>
#include <filesystem>

#include "../parse/Link.hpp"

namespace fs = std::filesystem;

namespace kc {

class FileEntry {
    public:

    explicit FileEntry(fs::directory_entry entry);

    fs::directory_entry file_entry;
    fs::path relative_path;

    [[nodiscard]] bool content_loaded() const;
    std::vector<std::string> load_content();
    [[nodiscard]] std::vector<std::string> get_content() const;
    void clear_content();

    private:

    std::vector<std::string> file_content;
    bool loaded;
};

}