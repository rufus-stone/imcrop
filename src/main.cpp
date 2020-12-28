#include <sstream>
#include <queue>

#include <spdlog/spdlog.h>
#include <docopt/docopt.h>
#include <opencv2/opencv.hpp>

#include "usage.hpp"
#include "file_utils.hpp"
#include "cropper.hpp"

int main(int argc, const char **argv)
{
  auto const args = docopt::docopt(imcrop::usage, {std::next(argv), std::next(argv, argc)},
    true,            // show help if requested
    "imcrop 1.0.0"); // version string

  bool const verbose = args.at("--verbose").asBool();

  if (verbose)
  {
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Enabled verbose logging...");
  }

  // Print the args out
  for (auto const &arg : args)
  {
    std::stringstream ss;
    ss << arg.second;

    spdlog::debug("{}: {}", arg.first, ss.str());
  }

  // Get the path to the image to load
  std::string const img_path = args.at("<path>").asString();

  // Load the image
  cv::Mat img = imcrop::load_image(img_path);

  if (img.empty())
  {
    return EXIT_FAILURE;
  }

  // Display it
  imcrop::display_img(img);

  return EXIT_SUCCESS;
}
