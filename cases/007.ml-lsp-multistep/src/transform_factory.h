#ifndef SOLID_TRANSFORM_FACTORY_H_
#define SOLID_TRANSFORM_FACTORY_H_

#include <memory>
#include <string>

#include "feature_transform.h"

namespace nitr::case007 {

std::unique_ptr<FeatureTransform> MakeTransform(const std::string& name);

}  // namespace nitr::case007

#endif  // SOLID_TRANSFORM_FACTORY_H_
