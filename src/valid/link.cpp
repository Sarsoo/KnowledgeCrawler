#include "link.hpp"

#include <filesystem>
#include <iostream>

#include "../logging.hpp"

namespace fs = std::filesystem;

namespace kc {

std::vector<kc::FileLinkStateResult> validate_links(const std::vector<std::shared_ptr<kc::FileContext>> &contexts)
{
    std::vector<kc::FileLinkStateResult> ret;

    auto invalid_counter = 0;

    for (auto context : contexts)
    {
        if (context->links.size() > 0)
        {
            for (auto link: context->links)
            {
                if(!link.is_external()) {
                    
                    auto composed = context->file_entry->file_entry.path().parent_path() / fs::path(link.link);

                    auto entry = fs::directory_entry(composed);

                    if(!entry.exists())
                    {
                        print_and_log("Invalid link: " + std::string(context->file_entry->file_entry.path()) + " -> " + link.original_form);
                        invalid_counter++;
                    }
                }
            }
        }
    }

    if (invalid_counter == 0)
    {
        print_and_log("All links valid");
    }

    return ret;
}

}