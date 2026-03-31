#include "session_manager.h"

#include <utility>

namespace nitr::case009 {

SessionManager::SessionManager(std::int64_t ttl_seconds)
    : SessionManager(ttl_seconds, std::make_shared<SystemTimeSource>()) {}

SessionManager::SessionManager(std::int64_t ttl_seconds,
                               std::shared_ptr<TimeSource> time_source)
    : ttl_seconds_(ttl_seconds), time_source_(std::move(time_source)) {}

bool SessionManager::CreateSession(const std::string& session_id) {
  if (sessions_.count(session_id) != 0U) {
    return false;
  }

  const std::int64_t now_seconds = time_source_->NowSeconds();
  sessions_.emplace(session_id,
                    SessionRecord{session_id, now_seconds, now_seconds});
  return true;
}

bool SessionManager::IsValid(const std::string& session_id) const {
  if (sessions_.find(session_id) == sessions_.end()) {
    return false;
  }

  // TODO: implement expiration logic.
  return true;
}

bool SessionManager::RefreshSession(const std::string& session_id) {
  const auto it = sessions_.find(session_id);
  if (it == sessions_.end()) {
    return false;
  }

  // TODO: refresh should fail for expired sessions and restart the validity window.
  it->second.last_started_at_seconds = time_source_->NowSeconds();
  return true;
}

bool SessionManager::RemoveSession(const std::string& session_id) {
  return sessions_.erase(session_id) > 0U;
}

std::size_t SessionManager::SessionCount() const {
  return sessions_.size();
}

}  // namespace nitr::case009
