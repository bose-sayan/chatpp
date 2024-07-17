#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <utility>

class Message {
private:
    std::string username;
    std::string content;
    std::string timestamp;

    // Setters
    void set_username(const std::string &uname);

    void set_content(const std::string &text);

    void set_timestamp(const std::string &cur_time);

public:

    // Constructors
    Message();

    Message(std::string username, std::string content,
            std::string timestamp);

    // Getters
    [[nodiscard]] std::string get_username() const;

    [[nodiscard]] std::string get_content() const;

    [[nodiscard]] std::string get_timestamp() const;

    // JSON Serialization
    [[nodiscard]] nlohmann::json to_json() const;

    static Message from_json(const nlohmann::json &json);
};