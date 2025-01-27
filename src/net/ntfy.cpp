#include "ntfy.hpp"

#include <boost/algorithm/string/join.hpp>

namespace kc {

constexpr std::string get_urgency_string(NotificationUrgency u){
    switch(u){
        case NotificationUrgency::MAX:
            return "max";
        case NotificationUrgency::HIGH:
            return "high";
        case NotificationUrgency::DEFAULT:
            return "default";
        case NotificationUrgency::LOW:
            return "low";
        case NotificationUrgency::MIN:
            return "min";
    }
    return "default";
}

void notify(std::string host, Notification notification)
{
    request(
        http::verb::post,
        host,
        std::format("/{}", notification.get_topic()),
        notification.get_payload(),
        std::make_unique<std::unordered_map<std::string, std::string>>(notification.get_attributes()));
}

std::unordered_map<std::string, std::string> Notification::get_attributes() const {
    std::unordered_map<std::string, std::string> attributes = {
        {"Title", title},
        {"Priority", get_urgency_string(priority)}
    };

    if (tags.size() > 0) {
        attributes["Tags"] = boost::algorithm::join(tags, ",");
    }

    return attributes;
}

std::string Notification::get_payload() const {
    return payload;
}

std::string Notification::get_topic() const {
    return topic;
}

void Notification::add_tag(const std::string &tag) {
    tags.emplace_back(tag);
}

void Notification::clear_tags() {
    tags.clear();
}

}