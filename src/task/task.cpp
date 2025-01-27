#include "task.hpp"

namespace kc {

constexpr TaskState get_task_state(char c){
    switch(c){
        case ' ':
            return TaskState::NOT_STARTED;
        case '/':
            return TaskState::IN_PROGRESS;
        case 'x':
            return TaskState::COMPLETED;
        case '-':
            return TaskState::CANCELLED;
    }

    return TaskState::UNKNOWN;
}

constexpr char get_task_state(TaskState c){
    switch(c){
        case TaskState::NOT_STARTED:
            return ' ';
        case TaskState::IN_PROGRESS:
            return '/';
        case TaskState::COMPLETED:
            return 'x';
        case TaskState::CANCELLED:
            return '-';
    }

    return '?';
}

bool is_current(Task task) {
    return is_current(task, day_clock::local_day());
}


bool is_current(Task task, date current_date) {
    return task.get_due_date() <= current_date
    && (task.get_state() == TaskState::NOT_STARTED || task.get_state() == TaskState::IN_PROGRESS);
}

Task::Task(const std::string &task_content, TaskState state, const std::string &due_date_str)
    : task_content(task_content), state(state), due_date(from_simple_string(due_date_str)) {
}

Task::Task(const std::string &task_content, std::string state, const std::string &due_date_str)
    : task_content(task_content), state(get_task_state(state[0])), due_date(from_simple_string(due_date_str)) {
}

Task::Task(const std::string &task_content, TaskState state, const date &due_date_str)
    : task_content(task_content), state(state), due_date(due_date_str) {
}

Task::Task(const std::string &task_content, TaskState state)
    : task_content(task_content), state(state) {
}

Task::Task(const std::string &task_content)
    : task_content(task_content), state(NOT_STARTED) {
}

std::string Task::get_content() const {
    return task_content;
}

date Task::get_due_date() const {
    return due_date;
}

TaskState Task::get_state() const {
    return state;
}

}
