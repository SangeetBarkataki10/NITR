#include "shift_tracker.h"

#include <stdexcept>
#include <utility>

namespace nitr::case020 {

ShiftTracker::ShiftTracker(std::string shift_id)
    : shift_id_(std::move(shift_id)) {}

void ShiftTracker::AddCompletedTote(const std::string& tote_id,
                                    int package_count) {
  completed_totes_.push_back(ToteRecord{tote_id, package_count});
}

void ShiftTracker::StartTote(const std::string& tote_id) {
  if (current_tote_.has_value()) {
    throw std::logic_error("current tote already started");
  }
  current_tote_ = ToteRecord{tote_id, 0};
}

void ShiftTracker::ScanPackageIntoCurrentTote() {
  ScanPackagesIntoCurrentTote(1);
}

void ShiftTracker::ScanPackagesIntoCurrentTote(int package_count) {
  if (!current_tote_.has_value()) {
    throw std::logic_error("no current tote");
  }
  current_tote_->package_count += package_count;
}

void ShiftTracker::CloseCurrentTote() {
  if (!current_tote_.has_value()) {
    throw std::logic_error("no current tote");
  }
  completed_totes_.push_back(*current_tote_);
  current_tote_.reset();
}

const std::string& ShiftTracker::shift_id() const {
  return shift_id_;
}

const std::vector<ToteRecord>& ShiftTracker::completed_totes() const {
  return completed_totes_;
}

const std::optional<ToteRecord>& ShiftTracker::current_tote() const {
  return current_tote_;
}

}  // namespace nitr::case020
