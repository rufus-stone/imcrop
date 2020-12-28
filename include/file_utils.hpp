#pragma once

#include <filesystem>

#include <opencv2/opencv.hpp>

namespace imcrop
{

auto is_valid_image(std::filesystem::path const &path) -> bool;
auto load_image(std::filesystem::path const &path) -> cv::Mat;

} // namespace imcrop
