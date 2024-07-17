#include "message.hpp"

// Constructors
Message::Message() = default;

Message::Message(std::string username, std::string content, std::string timestamp) : username(std::move(username)),
                                                                                     content(std::move(content)),
                                                                                     timestamp(std::move(timestamp)) {}
// Getters

std::string Message::get_username() const { return username; }

std::string Message::get_content() const { return content; }

std::string Message::get_timestamp() const { return timestamp; }

// Setters
void Message::set_username(const std::string &uname) { this->username = uname; }

void Message::set_content(const std::string &text) { this->content = text; }

void Message::set_timestamp(const std::string &cur_time) { this->timestamp = cur_time; }

// JSON Serialization
nlohmann::json Message::to_json() const {
    return nlohmann::json{
            {"username",  username},
            {"content",   content},
            {"timestamp", timestamp}};
}

Message Message::from_json(const nlohmann::json &json) {
    Message message;
    message.set_username(json.at("username").get<std::string>());
    message.set_content(json.at("content").get<std::string>());
    message.set_timestamp(json.at("timestamp").get<std::string>());
    return message;
}