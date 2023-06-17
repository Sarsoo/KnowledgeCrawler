# pragma once

#include <memory>
#include <vector>

#include <opencv2/opencv.hpp>

#include "../parse/FileContext.hpp"

namespace kc {

void image_proc(const std::vector<std::shared_ptr<kc::FileContext>> &contexts);

}