#pragma once

#include <filesystem>
#include <vector>
#include "../parse/FileContext.hpp"

namespace kc {

    void current_tasks(const std::vector<std::shared_ptr<kc::FileContext>> &contexts);

}