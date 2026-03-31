#include "pipeline_config.h"
#include "pipeline_runner.h"
#include "test_util.h"

using nitr::case016::PipelineConfig;
using nitr::case016::PipelineRunner;

namespace {

void TestRunnerSmoke() {
  const std::string json_text = R"JSON(
{
  "steps": [
    {"name": "step1"},
    {"name": "step2"},
    {"name": "step3"}
  ]
}
)JSON";

  const PipelineConfig config = PipelineConfig::FromJsonText(json_text);
  const PipelineRunner runner;
  const auto result = runner.Run(config);

  ASSERT_EQ(3, static_cast<int>(result.executed_steps.size()));
  ASSERT_EQ(std::string("step1"), result.executed_steps[0].step_name);
  ASSERT_EQ(std::string("step2"), result.executed_steps[1].step_name);
  ASSERT_EQ(std::string("step3"), result.executed_steps[2].step_name);
}

}  // namespace

int main() {
  return RunTest("runner_smoke", &TestRunnerSmoke);
}
