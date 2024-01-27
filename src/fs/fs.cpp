#include "fs.hpp"

#include <fstream>
#include <iostream>

static const std::string exclusions[] = {".git", ".obsidian"};

std::vector<std::shared_ptr<kc::FileEntry>> kc::walk_dir(const std::string dir)
{
    auto matched = std::vector<std::shared_ptr<kc::FileEntry>>();
    const auto base_path = fs::path(dir);

    for (auto const& dir_entry : fs::recursive_directory_iterator(base_path))
    {
        if (dir_entry.is_directory()) continue;

        auto excluded = false;
        const auto& dir_entry_path = dir_entry.path();
        auto dir_entry_path_string = dir_entry_path.string();

        for (auto const& exclusion: exclusions)
        {
            if (dir_entry_path_string.contains(exclusion))
            {
                excluded = true;
                break;
            }
        }

        if (!excluded) 
        {
            auto entry = std::make_shared<kc::FileEntry>(dir_entry);

            entry->relative_path = fs::relative(dir_entry_path, base_path);
            
            matched.push_back(entry);
        }
    }

    return matched;
}