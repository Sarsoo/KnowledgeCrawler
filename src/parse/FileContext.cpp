#include "FileContext.hpp"

namespace kc {

FileContext::FileContext(std::shared_ptr<kc::FileEntry> entry)
    : file_entry(std::move(entry)), links_parsed(false) {
}

void FileContext::parse()
{
    if (!file_entry->content_loaded())
    {
        throw std::logic_error("cannot parse from file entry as it has not been loaded");
    }

    links.clear();
    images.clear();
    tags.clear();
    tasks.clear();

    parse_links();
    parse_images();
    parse_tags();
    parse_tasks();
}

void FileContext::parse(ParseOperations operations)
{
    if (!file_entry->content_loaded())
    {
        throw std::logic_error("cannot parse from file entry as it has not been loaded");
    }

    if ((operations & LINKS) != 0) {
        links.clear();
        parse_links();
    }

    if ((operations & IMAGES) != 0) {
        images.clear();
        parse_images();
    }

    if ((operations & TAGS) != 0) {
        tags.clear();
        parse_tags();
    }

    if ((operations & TASKS) != 0) {
        tasks.clear();
        parse_tasks();
    }
}

void FileContext::parse_links() {
    std::regex link_regex(MD_MD_LINK_REGEX);
    std::string file_content = file_entry->get_content();
    std::smatch link_match;
    while(std::regex_search(file_content, link_match, link_regex)) {

        links.emplace_back(link_match.str());
        file_content = link_match.suffix();
    }
}

void FileContext::parse_images() {
    std::regex image_regex(MD_IMAGE_LINK_REGEX);
    std::string file_content = file_entry->get_content();
    std::smatch image_match;
    while(std::regex_search(file_content, image_match, image_regex)) {

        images.emplace_back(image_match.str());
        file_content = image_match.suffix();
    }
}

void FileContext::parse_tags() {
#if __APPLE__
    std::regex tag_regex(MD_TAG_REGEX, std::regex::multiline);
#else
    std::regex tag_regex(MD_TAG_REGEX);
#endif
    std::string file_content = file_entry->get_content();
    std::smatch tag_match;
    while(std::regex_search(file_content, tag_match, tag_regex)) {

        tags.push_back(tag_match.str().substr(1));
        file_content = tag_match.suffix();
    }
}

void FileContext::parse_tasks() {
    std::regex task_regex(TASK_REGEX);
    std::string file_content = file_entry->get_content();
    std::smatch task_match;
    while(std::regex_search(file_content, task_match, task_regex)) {

        tasks.emplace_back(task_match[2], task_match[1], task_match[3]);
        file_content = task_match.suffix();
    }
}


std::filesystem::path FileContext::abs_path(const kc::Link &link) const {
    return file_entry->file_entry.path().parent_path() / fs::path(link.link);
}

}