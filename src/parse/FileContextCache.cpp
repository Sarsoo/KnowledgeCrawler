#include "FileContextCache.hpp"

#include <algorithm>

#if __cpp_lib_execution //checking to see if the <execution> header is there
#include <execution>
#endif

#include "../fs/fs.hpp"
#include "../logging.hpp"

namespace kc {

void FileContextCache::load(const std::string &root_path)
{
    BOOST_LOG_TRIVIAL(trace) << "Beginning cache load";

    const auto entries = kc::walk_dir(root_path);
    this->root_path.assign(root_path);

    for (const auto& entry : entries)
    {
        if (entry->relative_path.extension() == ".md")
        {
            entry->load_content();
        }

        file_contexts.push_back(std::make_shared<kc::FileContext>(entry));
    }

    BOOST_LOG_TRIVIAL(debug) << "Loaded " << size() << " entries";
}

void FileContextCache::parse_all()
{
    parse_all(ParseOperations::ALL);
}

void FileContextCache::parse_all(ParseOperations operations) {
    tag_map.clear();

#ifdef __cpp_lib_execution
    std::mutex m;
    std::for_each(std::execution::par, file_contexts.begin(), file_contexts.end(), [this, &operations, &m](std::shared_ptr<kc::FileContext> &context)
#else
    std::ranges::for_each(file_contexts, [this, &operations](const std::shared_ptr<kc::FileContext> &context)
#endif
    {
        if (context->file_entry->relative_path.extension() == ".md")
        {
            context->parse(operations);

            if (!context->tags.empty())
            {
#ifdef __cpp_lib_execution
                std::lock_guard<std::mutex> lock{m};
#endif
                for (const auto& tag : context->tags)
                {
                    tag_map[tag].push_back(context->file_entry);
                }
            }
        }
    });
}

void FileContextCache::clear()
{
    file_contexts.clear();
    file_contexts.shrink_to_fit();
}

size_t FileContextCache::size() const
{
    return file_contexts.size();
}

std::vector<std::shared_ptr<kc::FileContext>> FileContextCache::get() const
{
    return file_contexts;
}

std::string FileContextCache::get_root_path() const
{
    return root_path;
}

}