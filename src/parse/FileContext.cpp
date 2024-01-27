#include "FileContext.hpp"

#include <utility>

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

    std::regex link_regex(MD_MD_LINK_REGEX);
    std::string file_content = file_entry->get_content();
    std::smatch link_match;
    while(std::regex_search(file_content, link_match, link_regex)) {
        
        links.push_back(kc::Link(link_match.str()));
        file_content = link_match.suffix();
    }

    std::regex image_regex(MD_IMAGE_LINK_REGEX);
    file_content = file_entry->get_content();
    std::smatch image_match;
    while(std::regex_search(file_content, image_match, image_regex)) {
        
        images.push_back(kc::Link(image_match.str()));
        file_content = image_match.suffix();
    }

#if __APPLE__
    std::regex tag_regex(MD_TAG_REGEX, std::regex::multiline);
#else
    std::regex tag_regex(MD_TAG_REGEX);
#endif
    file_content = file_entry->get_content();
    std::smatch tag_match;
    while(std::regex_search(file_content, tag_match, tag_regex)) {
        
        tags.push_back(tag_match.str().substr(1));
        file_content = tag_match.suffix();
    }

}

std::filesystem::path FileContext::abs_path(kc::Link link)
{
    return file_entry->file_entry.path().parent_path() / fs::path(link.link);
}

}