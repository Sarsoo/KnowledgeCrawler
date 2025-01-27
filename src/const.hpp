#pragma once

#include <string>

static const std::string MD_LINK_REGEX = R"(\[.*?\]\(.*?\))";
static const std::string MD_MD_LINK_REGEX = R"(\[.*?\]\(.*?\.md(#.*?)*\))";
static const std::string MD_IMAGE_LINK_REGEX = R"(!\[.*?\]\(.*?\.png\))";
static const std::string MD_TAG_REGEX = R"((^|[[:blank:]])#{1}[^\s#.]+)";

static const std::string TASK_REGEX = R"(.*\[(.)\] (.+) 📅 (.*))";
static const std::string TIGHT_TASK_REGEX = R"(.*\[(.)\] (.+) 📅 (.{10}))";
static const std::string UNCOMPLETED_TASK_REGEX = R"(.*\[(.)\] (.+) 📅 (.{10})(?! [✅❌].*))";
