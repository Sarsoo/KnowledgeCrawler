#include "current_tasks.hpp"
#include "task.hpp"

#include <iostream>

namespace kc {

void current_tasks(const std::vector<std::shared_ptr<kc::FileContext>> &contexts)
{
    auto date = day_clock::local_day();

    for (const auto &entry : contexts) {

        for (const auto &task : entry->tasks) {

            if (is_current(task, date))
                std::cout << "(" << task.get_content() << ") : " << task.get_due_date() << " " << entry->file_entry->file_entry.path() << std::endl;
        }
    }
}

}