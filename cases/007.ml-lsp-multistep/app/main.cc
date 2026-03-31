#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "feature_pipeline.h"
#include "transform_factory.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "usage: case007_app <identity|l2|clamp> [values...]\n";
    return EXIT_FAILURE;
  }

  try {
    std::vector<float> input;
    for (int i = 2; i < argc; ++i) {
      input.push_back(std::stof(argv[i]));
    }

    nitr::case007::FeaturePipeline pipeline(
        nitr::case007::MakeTransform(argv[1]));
    const std::vector<float> output = pipeline.Run(input);
    for (std::size_t i = 0; i < output.size(); ++i) {
      if (i > 0U) {
        std::cout << ' ';
      }
      std::cout << output[i];
    }
    std::cout << '\n';
  } catch (const std::exception& ex) {
    std::cerr << ex.what() << '\n';
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
