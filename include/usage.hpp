#pragma once

namespace imcrop
{

static constexpr auto usage =
  R"(imcrop 1.0.0
  
Use imcrop to draw a rectange on an image and calculate the width, height, x, and y scale factors needed to crop that image using OpenCV.

Usage:
  imcrop <path> [options]

Options:
  -h, --help              Show this screen
  -v, --version           Show app version
  -V, --verbose           Enable verbose logging (for debugging purposes)
)";

} // namespace imcrop
