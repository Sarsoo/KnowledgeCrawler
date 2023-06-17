#pragma once

#include <memory>
#include <vector>
#include "../parse/FileContext.hpp"

namespace kc {

enum LinkState {
    VALID, INVALID
};

struct LinkStateResult {
    LinkState link_state;
    kc::Link link;
};

struct FileLinkStateResult {
    std::shared_ptr<FileContext> file_context;
    std::vector<LinkStateResult> link_states;
};

std::vector<FileLinkStateResult> validate_links(const std::vector<std::shared_ptr<kc::FileContext>> &contexts);

}