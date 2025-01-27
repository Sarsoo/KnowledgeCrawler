#include "print.hpp"

#include <filesystem>
#include <iostream>

#include "../logging.hpp"

namespace fs = std::filesystem;

namespace kc {

void print_file(const std::vector<std::shared_ptr<kc::FileContext>> &contexts)
{
    for (const auto &entry : contexts) {

        std::regex link_regex(UNCOMPLETED_TASK_REGEX);
        std::string file_content = entry->file_entry->get_content();
        std::smatch link_match;
        while(std::regex_search(file_content, link_match, link_regex)) {

            std::cout << entry->file_entry->file_entry.path() << " (" << link_match[2] << ") : " << link_match[3] << std::endl;

            file_content = link_match.suffix();
        }
    }
}

}