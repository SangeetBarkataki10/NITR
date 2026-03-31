#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "build_pipeline.h"
#include "event.h"
#include "pipeline_config.h"

namespace {

nitr::case015::PipelineConfig ParseArgs(int argc, char** argv) {
  nitr::case015::PipelineConfig config;
  for (int i = 1; i < argc; ++i) {
    const std::string arg(argv[i]);
    if (arg == "--mode=file") {
      config.policy_mode = nitr::case015::PolicyMode::kFile;
    } else if (arg == "--mode=static") {
      config.policy_mode = nitr::case015::PolicyMode::kStatic;
    } else if (arg == "--enable-policy-enrichment") {
      config.enable_policy_enrichment = true;
    } else if (arg.rfind("--policy-file=", 0) == 0) {
      config.policy_file_path =
          arg.substr(std::string("--policy-file=").size());
    }
  }
  return config;
}

std::vector<nitr::case015::Event> ReadEvents(const std::string& path) {
  std::ifstream input(path);
  std::vector<nitr::case015::Event> events;
  std::string line;
  while (std::getline(input, line)) {
    if (line.empty()) {
      continue;
    }

    std::istringstream row(line);
    std::string source_id;
    std::string payload;
    std::string score_text;
    if (!std::getline(row, source_id, ',')) {
      continue;
    }
    if (!std::getline(row, payload, ',')) {
      continue;
    }
    if (!std::getline(row, score_text, ',')) {
      continue;
    }

    events.push_back(
        nitr::case015::Event{source_id, payload, std::stoi(score_text)});
  }
  return events;
}

}  // namespace

int main(int argc, char** argv) {
  const nitr::case015::PipelineConfig config = ParseArgs(argc, argv);
  const auto pipeline = nitr::case015::BuildPipeline(config);

  const std::vector<nitr::case015::Event> events = ReadEvents(
      "evaluator/015.pipeline-provider-decoupling/data/events_input.txt");
  for (const std::string& line : pipeline.runner.Run(events)) {
    std::cout << line << '\n';
  }
  return 0;
}
