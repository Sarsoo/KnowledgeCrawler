#pragma once

#include <vector>
#include <memory>
#include <regex>
#include <filesystem>

#include "../fs/FileEntry.hpp"
#include "Link.hpp"
#include "../const.hpp"
#include "../task/task.hpp"

namespace kc {

enum ParseOperations
{
    LINKS = 1 << 0, // binary 0001
    IMAGES = 1 << 1, // binary 0010
    TAGS = 1 << 2, // binary 0100
    TASKS = 1 << 3,  // binary 1000

    ALL = LINKS | IMAGES | TAGS | TASKS
};

inline ParseOperations operator|(ParseOperations a, ParseOperations b)
{
    return static_cast<ParseOperations>(static_cast<int>(a) | static_cast<int>(b));
}

class FileContext {
    public:

    explicit FileContext(std::shared_ptr<kc::FileEntry> entry);

    std::shared_ptr<kc::FileEntry> file_entry;
    std::vector<kc::Link> links;
    std::vector<kc::Link> images;
    std::vector<std::string> tags;
    std::vector<Task> tasks;

    void parse();
    void parse(ParseOperations operations);
    [[nodiscard]] std::filesystem::path abs_path(const kc::Link &link) const;

    private:

    void parse_links();
    void parse_images();
    void parse_tags();
    void parse_tasks();

    bool links_parsed;
};

}
