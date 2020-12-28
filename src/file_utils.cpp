#include "file_utils.hpp"

#include <spdlog/spdlog.h>
#include <opencv2/opencv.hpp>

namespace imcrop
{

auto is_valid_image(std::filesystem::path const &path) -> bool
{
  spdlog::debug("Checking path: {}", path.string());

  // Does the path exist?
  if (!std::filesystem::exists(path))
  {
    spdlog::error("[❗] Couldn't find path: {}", path.string());
    return false;
  }

  if (!std::filesystem::is_regular_file(path))
  {
    spdlog::error("[❗] Not a regular file: {}", path.string());
    return false;
  }

  // Lambda to check for image file extensions
  auto const has_image_extension = [](std::filesystem::path const &file) -> bool {
    static constexpr auto image_extensions = std::array{".jpg", ".jpeg", ".png"};

    std::string const extension = file.extension().string();
    return (!extension.empty() && std::find(std::begin(image_extensions), std::end(image_extensions), extension) != std::end(image_extensions));
  };

  return has_image_extension(path);
}

auto load_image(std::filesystem::path const &path) -> cv::Mat
{
  spdlog::debug("Loading image: {}", path.string());

  if (is_valid_image(path))
  {
    return cv::imread(path.string(), cv::IMREAD_UNCHANGED);
  } else
  {
    spdlog::error("[❗] Check inputs and try again!");
    return cv::Mat{};
  }
}

} // namespace imcrop
