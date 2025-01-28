#include "FileContext.hpp"

#include "../logging.hpp"

namespace kc {

FileContext::FileContext(std::shared_ptr<kc::FileEntry> entry)
    : file_entry(std::move(entry)), links_parsed(false) {
}

constexpr int MAX_LINE_LENGTH = 3000;

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

void FileContext::parse(const ParseOperations operations)
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
    const std::regex link_regex(MD_MD_LINK_REGEX, std::regex::optimize);
    const auto file_content = file_entry->get_content();

    for (const auto& line : file_content) {
        if (line.length() < MAX_LINE_LENGTH) {
            std::string line_content = line;
            std::smatch link_match;
            while(std::regex_search(line_content, link_match, link_regex)) {

                links.emplace_back(link_match.str());
                line_content = link_match.suffix();
            }
        }
        else {
            BOOST_LOG_TRIVIAL(trace) << "Skipping line because too long: " << line;
        }
    }
}

void FileContext::parse_images() {
    const std::regex image_regex(MD_IMAGE_LINK_REGEX, std::regex::optimize);
    const auto file_content = file_entry->get_content();

    for (const auto& line : file_content) {
        if (line.length() < MAX_LINE_LENGTH) {
            std::string line_content = line;
            std::smatch image_match;
            while(std::regex_search(line_content, image_match, image_regex)) {

                images.emplace_back(image_match.str());
                line_content = image_match.suffix();
            }
        }
        else {
            BOOST_LOG_TRIVIAL(trace) << "Skipping line because too long: " << line;
        }
    }
}

void FileContext::parse_tags() {
#if __APPLE__
    std::regex tag_regex(MD_TAG_REGEX, std::regex::multiline | std::regex::optimize);
#else
    std::regex tag_regex(MD_TAG_REGEX, std::regex::optimize);
#endif
    const auto file_content = file_entry->get_content();

    for (const auto& line : file_content) {
        if (line.length() < MAX_LINE_LENGTH) {
            std::string line_content = line;
            std::smatch tag_match;
            while(std::regex_search(line_content, tag_match, tag_regex)) {

                tags.push_back(tag_match.str().substr(1));
                line_content = tag_match.suffix();
            }
        }
        else {
            BOOST_LOG_TRIVIAL(trace) << "Skipping line because too long: " << line;
        }
    }
}

void FileContext::parse_tasks() {
    const std::regex task_regex(TASK_REGEX, std::regex::optimize);
    const auto file_content = file_entry->get_content();

    for (const auto& line : file_content) {
        if (line.length() < MAX_LINE_LENGTH) {
            std::string line_content = line;
            std::smatch task_match;
            while(std::regex_search(line_content, task_match, task_regex)) {

                tasks.emplace_back(task_match[2], task_match[1], task_match[3]);
                line_content = task_match.suffix();
            }
        }
        else {
            BOOST_LOG_TRIVIAL(trace) << "Skipping line because too long: " << line;
        }
    }
}


std::filesystem::path FileContext::abs_path(const kc::Link &link) const {
    return file_entry->file_entry.path().parent_path() / fs::path(link.link);
}

}
