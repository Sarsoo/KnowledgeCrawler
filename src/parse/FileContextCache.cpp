#include "FileContextCache.hpp"
#include "../fs/fs.hpp"
#include "../logging.hpp"

namespace kc {

void FileContextCache::load(std::string root_path)
{
    BOOST_LOG_TRIVIAL(trace) << "Beginning cache load";

    auto entries = kc::walk_dir(root_path);

    for (auto entry : entries)
    {
        if (entry.relative_path.extension() == ".md")
        {
            entry.load_content();
        }

        file_contexts.push_back(std::make_shared<kc::FileContext>(entry));
    }

    BOOST_LOG_TRIVIAL(debug) << "Loaded " << size() << " entries";
}

void FileContextCache::parse_all()
{
    for (auto context: file_contexts)
    {
        if (context->file_entry.relative_path.extension() == ".md")
        {
            context->parse();
        }
    }
}

void FileContextCache::clear()
{
    file_contexts.clear();
    file_contexts.shrink_to_fit();
}

size_t FileContextCache::size()
{
    return file_contexts.size();
}

std::vector<std::shared_ptr<kc::FileContext>> FileContextCache::get()
{
    return file_contexts;
}

}