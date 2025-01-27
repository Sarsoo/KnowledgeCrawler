#pragma once
#include <string>

namespace kc {

enum TaskState {
    NOT_STARTED, IN_PROGRESS, COMPLETED, CANCELLED, UNKNOWN
};

constexpr TaskState get_task_state(char c);
constexpr char get_task_state(TaskState c);

class Task {
    public:

    explicit Task(const std::string &task_content, TaskState state, const std::string &due_date_str);
    explicit Task(const std::string &task_content, TaskState state);
    explicit Task(const std::string &task_content);

    private:

    std::string task_content;
    std::string due_date_str;
    TaskState state;
};

}
