#include "FileEntry.hpp"

#include <fstream>
#include <iostream>

namespace kc {

bool FileEntry::content_loaded()
{
    return !file_content.empty();
}

std::string FileEntry::load_content()
{
    std::ifstream ifs(file_entry.path());
    file_content.assign( (std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()) );

    return file_content;
}

std::string FileEntry::get_content()
{
    return file_content;
}

void FileEntry::clear_content()
{
    file_content.clear();
    file_content.shrink_to_fit();
}

}