#pragma once
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace kc {

using namespace boost::gregorian;

enum TaskState {
    NOT_STARTED, IN_PROGRESS, COMPLETED, CANCELLED, UNKNOWN
};

constexpr TaskState get_task_state(char c);
constexpr char get_task_state(TaskState c);

class Task {
    public:

    explicit Task(const std::string &task_content, TaskState state, const std::string &due_date_str);
    explicit Task(const std::string &task_content, std::string state, const std::string &due_date_str);
    explicit Task(const std::string &task_content, TaskState state, const date &due_date_str);
    explicit Task(const std::string &task_content, TaskState state);
    explicit Task(const std::string &task_content);

    [[nodiscard]] std::string get_content() const;
    [[nodiscard]] date get_due_date() const;
    [[nodiscard]] TaskState get_state() const;

    private:

    std::string task_content;
    date due_date;
    TaskState state;
};

bool is_current(Task task);
bool is_current(Task task, date current_date);

}
