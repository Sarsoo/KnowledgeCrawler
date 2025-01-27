#pragma once

#include <vector>
#include "../parse/FileContext.hpp"

namespace kc {

void print_file(const std::vector<std::shared_ptr<kc::FileContext>> &contexts);

}