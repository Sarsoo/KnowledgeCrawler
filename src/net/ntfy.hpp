#pragma once

#include "http.hpp"

namespace kc {

enum NotificationUrgency {
    MAX, HIGH, DEFAULT, LOW, MIN
};

constexpr std::string get_urgency_string(NotificationUrgency u);

class Notification {
public:
    explicit Notification(
        const std::string &topic,
        const std::string &payload
    ) :
        topic(topic),
        payload(payload),
        title("KnowledgeCrawler"),
        priority(DEFAULT)
    {}

    explicit Notification(
        const std::string &topic,
        const std::string &payload,
        const std::string &title
    ) :
        topic(topic),
        payload(payload),
        title(title),
        priority(DEFAULT)
    {}

    explicit Notification(
        const std::string &topic,
        const std::string &payload,
        const std::string &title,
        const NotificationUrgency &priority
    ) :
        topic(topic),
        payload(payload),
        title(title),
        priority(priority)
    {}

    std::string get_topic() const;
    std::string get_payload() const;
    void add_tag(const std::string &tag);
    void clear_tags();
    std::unordered_map<std::string, std::string> get_attributes() const;
private:
    std::string topic;
    std::string payload;
    std::string title;
    std::vector<std::string> tags;
    NotificationUrgency priority;
};

void notify(std::string host, Notification notification);

}