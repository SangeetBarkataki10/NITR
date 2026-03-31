#include "pipeline_config.h"
#include "test_util.h"

using nitr::case016::DeviceKind;
using nitr::case016::PipelineConfig;

namespace {

void TestConfigLoaderSmoke() {
  const std::string json_text = R"JSON(
{
  "legacy_gpu_through_step": 4,
  "steps": [
    {"name": "a"},
    {"name": "b"},
    {"name": "c", "device": "gpu"},
    {"name": "d", "device": "cpu"}
  ]
}
)JSON";

  const PipelineConfig config = PipelineConfig::FromJsonText(json_text);
  ASSERT_EQ(4, static_cast<int>(config.step_count()));
  ASSERT_TRUE(config.legacy_gpu_through_step().has_value());
  ASSERT_EQ(4, config.legacy_gpu_through_step().value());
  ASSERT_TRUE(config.steps()[2].required_device.has_value());
  ASSERT_EQ(static_cast<int>(DeviceKind::kGpu),
            static_cast<int>(config.steps()[2].required_device.value()));
  ASSERT_TRUE(config.steps()[3].required_device.has_value());
  ASSERT_EQ(static_cast<int>(DeviceKind::kCpu),
            static_cast<int>(config.steps()[3].required_device.value()));
}

}  // namespace

int main() {
  return RunTest("config_loader_smoke", &TestConfigLoaderSmoke);
}
