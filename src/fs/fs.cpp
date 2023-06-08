#include "fs.hpp"

#include <fstream>
#include <iostream>

static const std::string exclusions[] = {".git", ".obsidian"};

std::vector<kc::FileEntry> kc::walk_dir(std::string dir)
{
    auto matched = std::vector<kc::FileEntry>();
    auto base_path = fs::path(dir);

    for (auto const& dir_entry : fs::recursive_directory_iterator(base_path))
    {
        auto excluded = false;
        auto dir_entry_path = dir_entry.path();
        auto dir_entry_path_string = dir_entry_path.string();

        for (auto const& exclusion: exclusions)
        {
            if (dir_entry_path_string.contains(exclusion))
            {
                excluded = true;
            }
        }

        if (!excluded) 
        {
            auto entry = kc::FileEntry();

            entry.file_entry = dir_entry;
            entry.relative_path = fs::relative(dir_entry_path, base_path);
            
            matched.push_back(entry);
        }
    }

    return matched;
}