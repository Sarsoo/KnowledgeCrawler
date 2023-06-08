#pragma once

#include <string>
#include <filesystem>
namespace fs = std::filesystem;

namespace kc {

class FileEntry {
    public:

    fs::directory_entry file_entry;
    fs::path relative_path;

    private:
};

}