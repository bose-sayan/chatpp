#include <string>
/**
 * @brief Check if a username is valid
 * Check if a username is valid by ensuring the following:
 * - Minimum length of username is 3 characters
 * - Maximum length of username is 30 characters
 * - Username can only contain alphanumeric characters and underscores
 * - Username must start with an alphabetic character
 * - Username must not end with an underscore
 * @param username The username to validate
 * @return true if the username is valid, false otherwise
 *
 */
bool is_valid_username(const std::string &username) {
  // Minimum length of username is 3 characters
  if (username.size() < 3) {
    return false;
  }
  // Maximum length of username is 30 characters
  if (username.size() > 30) {
    return false;
  }

  // Username can only contain alphanumeric characters and underscores
  for (char c : username) {
    if (!std::isalnum(c) && c != '_') {
      return false;
    }
  }

  // Username must start with an alphabetic character
  if (!std::isalpha(username[0])) {
    return false;
  }

  // Username must not end with an underscore
  if (username.back() == '_') {
    return false;
  }

  // Username is valid
  return true;
}
