#ifndef NITR_AUDIT_LOGGER_H_
#define NITR_AUDIT_LOGGER_H_

#include <string>

namespace nitr::case010 {

class AuditLogger {
 public:
  virtual ~AuditLogger() = default;
  virtual void Log(const std::string& message) = 0;
};

class NullAuditLogger final : public AuditLogger {
 public:
  void Log(const std::string& message) override;
};

}  // namespace nitr::case010

#endif  // NITR_AUDIT_LOGGER_H_
