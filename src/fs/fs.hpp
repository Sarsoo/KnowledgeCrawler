#pragma once

#include <string>
#include <filesystem>

#include "FileEntry.hpp"

namespace fs = std::filesystem;

namespace kc {

std::vector<kc::FileEntry> walk_dir(std::string dir);

}