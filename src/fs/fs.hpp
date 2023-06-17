#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <memory>

#include "FileEntry.hpp"

namespace fs = std::filesystem;

namespace kc {

std::vector<std::shared_ptr<kc::FileEntry>> walk_dir(std::string dir);

}