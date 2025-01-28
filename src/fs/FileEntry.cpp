#include "FileEntry.hpp"

#include <fstream>
#include <iostream>
#include <utility>

namespace kc {

FileEntry::FileEntry(fs::directory_entry entry)
    : file_entry(std::move(entry)), loaded(false) {
}

bool FileEntry::content_loaded() const
{
    return loaded;
}

std::vector<std::string> FileEntry::load_content()
{
    std::ifstream ifs(file_entry.path());

    for (std::string line; std::getline(ifs, line);)
    {
        file_content.emplace_back(line);
    }

    loaded = true;

    return file_content;
}

std::vector<std::string> FileEntry::get_content() const
{
    return file_content;
}

void FileEntry::clear_content()
{
    file_content.clear();
    file_content.shrink_to_fit();
    loaded = false;
}

}