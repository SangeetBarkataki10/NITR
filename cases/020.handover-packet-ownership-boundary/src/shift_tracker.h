#pragma once

#include <optional>
#include <string>
#include <vector>

namespace nitr::case020 {

struct ToteRecord {
  std::string tote_id;
  int package_count;
};

class ShiftTracker {
 public:
  explicit ShiftTracker(std::string shift_id);

  void AddCompletedTote(const std::string& tote_id, int package_count);
  void StartTote(const std::string& tote_id);
  void ScanPackageIntoCurrentTote();
  void ScanPackagesIntoCurrentTote(int package_count);
  void CloseCurrentTote();

  const std::string& shift_id() const;
  const std::vector<ToteRecord>& completed_totes() const;
  const std::optional<ToteRecord>& current_tote() const;

 private:
  std::string shift_id_;
  std::vector<ToteRecord> completed_totes_;
  std::optional<ToteRecord> current_tote_;
};

}  // namespace nitr::case020
