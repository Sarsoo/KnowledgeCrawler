#pragma once

#include <string>

///////////////
/// COMMANDS
///////////////

static const std::string CMD_VALIDATE_TASKS = "validate";
static const std::string CMD_IMG_TASKS = "img";
static const std::string CMD_PRINT_TASKS = "print";
static const std::string CMD_CURRENT_TASKS = "current";


///////////////
/// CONFIG
///////////////

static const std::string CONFIG_NOTIFY = "notify";
static const std::string CONFIG_HOST = "host";
static const std::string CONFIG_TOPIC = "topic";
static const std::string CONFIG_TITLE = "title";
static const std::string CONFIG_TAGS = "tag";


///////////////
/// REGEXES
///////////////

static const std::string MD_LINK_REGEX = R"(\[.*?\]\(.*?\))";
static const std::string MD_MD_LINK_REGEX = R"(\[.*?\]\(.*?\.md(#.*?)*\))";
static const std::string MD_IMAGE_LINK_REGEX = R"(!\[.*?\]\(.*?\.png\))";
static const std::string MD_TAG_REGEX = R"((^|[[:blank:]])#{1}[^\s#.]+)";

static const std::string TASK_REGEX = R"(.*\[(.)\] (.+) 📅 (.*))";
static const std::string TIGHT_TASK_REGEX = R"(.*\[(.)\] (.+) 📅 (.{10}))";
static const std::string UNCOMPLETED_TASK_REGEX = R"(.*\[(.)\] (.+) 📅 (.{10})(?! [✅❌].*))";
