#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

#include "time_source.h"

namespace nitr::case009 {

struct SessionRecord {
  std::string id;
  std::int64_t created_at_seconds;
  std::int64_t last_started_at_seconds;
};

class SessionManager {
 public:
  explicit SessionManager(std::int64_t ttl_seconds);
  SessionManager(std::int64_t ttl_seconds,
                 std::shared_ptr<TimeSource> time_source);

  bool CreateSession(const std::string& session_id);
  bool IsValid(const std::string& session_id) const;
  bool RefreshSession(const std::string& session_id);
  bool RemoveSession(const std::string& session_id);
  std::size_t SessionCount() const;

 private:
  std::int64_t ttl_seconds_;
  std::shared_ptr<TimeSource> time_source_;
  std::unordered_map<std::string, SessionRecord> sessions_;
};

}  // namespace nitr::case009
