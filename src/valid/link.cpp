#include "link.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace kc {

std::vector<kc::FileLinkStateResult> validate_links(const std::vector<std::shared_ptr<kc::FileContext>> &contexts)
{
    std::vector<kc::FileLinkStateResult> ret;

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
                        std::cout << link.link << " + " << context->file_entry->file_entry.path() << " = " << composed << std::endl;
                    }
                }
            }
        }
    }

    return ret;
}

}