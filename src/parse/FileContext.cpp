#include "FileContext.hpp"

namespace kc {

FileContext::FileContext(kc::FileEntry entry)
: file_entry(entry)
{
    
}

void FileContext::parse()
{
    if (!file_entry.content_loaded())
    {
        throw std::logic_error("cannot parse from file entry as it has not been loaded");
    }

    links.clear();
    tags.clear();

    std::regex link_regex(MD_MD_LINK_REGEX);
    std::string file_content = file_entry.get_content();
    std::smatch link_match;
    while(std::regex_search(file_content, link_match, link_regex)) {
        
        links.push_back(kc::Link(link_match.str()));
        file_content = link_match.suffix();
    }

    std::regex tag_regex(MD_TAG_REGEX);
    file_content = file_entry.get_content();
    std::smatch tag_match;
    while(std::regex_search(file_content, tag_match, tag_regex)) {
        
        tags.push_back(tag_match.str());
        file_content = tag_match.suffix();
    }

}

}