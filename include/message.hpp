#pragma once
#include <nlohmann/json.hpp>
#include <string>

class Message {
  std::string username;
  std::string content;
  std::string timestamp;

public:
  // Constructors
  Message() = default;
  Message(const std::string &username, const std::string &content,
          const std::string &timestamp)
      : username(username), content(content), timestamp(timestamp) {}

  // Getters
  std::string get_username() const { return username; }
  std::string get_content() const { return content; }
  std::string get_timestamp() const { return timestamp; }

  // Setters
  void set_username(const std::string &username) { this->username = username; }
  void set_content(const std::string &content) { this->content = content; }
  void set_timestamp(const std::string &timestamp) {
    this->timestamp = timestamp;
  }

  // JSON Serialization
  nlohmann::json to_json() const {
    return nlohmann::json{
        {"username", username}, {"content", content}, {"timestamp", timestamp}};
  }
  static Message from_json(const nlohmann::json &json) {
    Message message;
    message.set_username(json.at("username").get<std::string>());
    message.set_content(json.at("content").get<std::string>());
    message.set_timestamp(json.at("timestamp").get<std::string>());
    return message;
  }
};