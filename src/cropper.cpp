#include "cropper.hpp"

#include <cmath>

#include <spdlog/spdlog.h>
#include <opencv2/opencv.hpp>

namespace imcrop
{

auto rect_start = cv::Point{};
auto rect_stop = cv::Point{};

void draw_rect(int event, int x, int y, [[maybe_unused]] int flags, void *userdata)
{
  cv::Mat &img = *static_cast<cv::Mat *>(userdata); //*(cv::Mat *)userdata;

  if (event == cv::EVENT_LBUTTONDOWN)
  {
    spdlog::debug("LMB down @ ({},{})", x, y);
    rect_start = cv::Point{x, y};

  } else if (event == cv::EVENT_LBUTTONUP)
  {
    spdlog::debug("LMB up @ ({},{})", x, y);
    rect_stop = cv::Point{x, y};

    auto rect_tl = cv::Point{std::min(rect_start.x, rect_stop.x), std::min(rect_start.y, rect_stop.y)};
    auto rect_br = cv::Point{std::max(rect_start.x, rect_stop.x), std::max(rect_start.y, rect_stop.y)};

    auto rect = cv::Rect(rect_tl.x, rect_tl.y, (rect_br.x - rect_tl.x), (rect_br.y - rect_tl.y));

    cv::rectangle(img, rect.tl(), rect.br(), cv::Scalar(0, 0, 255)); // cv::Scalar(blue, green. red)

    cv::imshow("imcrop", img);

    std::size_t const img_width = img.size().width;
    std::size_t const img_height = img.size().height;
    std::size_t const img_area = img_width * img_height;
    spdlog::info("               img resolution : {} x {}", img_width, img_height);
    spdlog::info("                     img area : {}", img_area);

    std::size_t tl_x = rect.tl().x;
    std::size_t tl_y = rect.tl().y;
    std::size_t br_x = rect.br().x;
    std::size_t br_y = rect.br().y;

    spdlog::info("                rect top left : {} x {}", tl_x, tl_y);
    spdlog::info("            rect bottom right : {} x {}", br_x, br_y);

    // Calculate the scale factor needed to multiply the image width/height by, in order get the top left x and y positions of the rectangle (0,0 is top left)
    double tl_x_s = static_cast<double>(tl_x) / static_cast<double>(img_width);
    double tl_y_s = static_cast<double>(tl_y) / static_cast<double>(img_height);

    spdlog::info("    rect top left x / y scale : {:.3g} x {:.3g}", tl_x_s, tl_y_s);

    // Calculate the scale factor needed to multiply the image width/height by, in order get the bottom right x and y positions of the rectangle (0,0 is top left)
    double br_x_s = static_cast<double>(br_x) / static_cast<double>(img_width);
    double br_y_s = static_cast<double>(br_y) / static_cast<double>(img_height);

    spdlog::info("rect bottom right x / y scale : {:.3g} x {:.3g}", br_x_s, br_y_s);

    // Calculate the scale factor needed to multiply the image width/height by, in order get the width/height of the rectangle
    double w_s = std::abs(static_cast<double>(br_x - tl_x)) / static_cast<double>(img_width);
    double h_s = std::abs(static_cast<double>(br_y - tl_y)) / static_cast<double>(img_height);

    spdlog::info("         width / height scale : {:.3g} x {:.3g}", w_s, h_s);

    // Calculate the scale factor needed to multiply the image area by, in order get the area of the rectangle
    double a_s = static_cast<double>(rect.area()) / static_cast<double>(img_area);

    spdlog::info("         rectangle area scale : {:.3g}", a_s);
  }
}

auto display_img(cv::Mat &img) -> void
{
  cv::namedWindow("imcrop", 1);

  cv::setMouseCallback("imcrop", draw_rect, static_cast<void *>(&img));

  cv::imshow("imcrop", img);

  cv::waitKey();
}

} // namespace imcrop
