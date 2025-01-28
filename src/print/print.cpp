#include "print.hpp"

#include <filesystem>
#include <iostream>

#include "../logging.hpp"
#include "../task/task.hpp"

namespace fs = std::filesystem;

namespace kc {

void print_file(const std::vector<std::shared_ptr<kc::FileContext>> &contexts)
{
    const auto date = day_clock::local_day();

    for (const auto &entry : contexts) {

        for (const auto &task : entry->tasks) {

            if (is_current(task, date))
                std::cout << "(" << task.get_content() << ") : " << task.get_due_date() << " " << entry->file_entry->file_entry.path() << std::endl;
        }
    }
}

}