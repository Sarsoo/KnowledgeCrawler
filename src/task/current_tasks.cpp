#include "current_tasks.hpp"
#include "task.hpp"

#include <iostream>
#include <algorithm>
#include <boost/algorithm/string/join.hpp>

#include "../logging.hpp"

namespace kc {

std::string get_notification_content(const std::vector<Task>& tasks) {
    std::vector<std::string> contents(tasks.size());

    std::ranges::transform(tasks, contents.rbegin(), [](const Task &t) -> std::string { return t.get_content(); });

    return boost::join(contents, "\n");
}

int current_tasks(const kc::AppContext &app_context)
{
    const auto date = day_clock::local_day();
    std::vector<Task> tasks;

    for(const auto& file_cache : app_context.file_caches) {
        for (const auto &entry : file_cache->get()) {
            for (const auto &task : entry->tasks) {

                if (is_current(task, date)) {
                    tasks.emplace_back(task);
                }
            }
        }
    }

    std::ranges::sort(tasks, [](const Task &a, const Task &b)
    {
        return a.get_due_date() < b.get_due_date();
    });

    for (const auto& task : tasks) {
        std::cout << task.get_content() << " (" << task.get_due_date() << ")" << std::endl;
    }

    if (!tasks.empty() && app_context.config->contains(CONFIG_NOTIFY)) {
        print_and_log(std::format("Sending notification for {} tasks", tasks.size()));

        if (!app_context.config->contains(CONFIG_HOST)) {
            print_and_log_error("No NTFY host provided");
            return 1;
        }
        if (!app_context.config->contains(CONFIG_TOPIC)) {
            print_and_log_error("No NTFY topic name provided");
            return 1;
        }

        const auto host_name = (*app_context.config)[CONFIG_HOST].as<std::string>();
        const auto topic_name = (*app_context.config)[CONFIG_TOPIC].as<std::string>();

        const auto payload = get_notification_content(tasks);

        auto notif = kc::Notification(topic_name, payload);

        if (app_context.config->contains(CONFIG_TAGS)) {
            for (auto const& tag : (*app_context.config)[CONFIG_TAGS].as<std::vector<std::string>>()) {
                BOOST_LOG_TRIVIAL(info) << "Tagging notification with " << tag;
                notif.add_tag(tag);
            }
        }

        try{
            kc::notify(host_name, notif);
            print_and_log("Notification sent");
        }
        catch (const std::exception &e) {
            print_and_log_error(std::format("Exception occurred while sending notification - {}", e.what()));
        }
    }

    return 0;
}

}
