#include "img.hpp"

namespace kc {

void image_proc(const std::vector<std::shared_ptr<kc::FileContext>> &contexts)
{
    for (auto const context: contexts)
    {
        if (context->images.size() > 0)
        {
            auto img = context->images[0];
            auto composed_path = context->abs_path(img);

            cv::Mat image;  // variable image of datatype Matrix
            image = cv::imread(composed_path);

            cv::imshow(img.link, image);
            cv::waitKey(0);

            break;
        }
    }
}

}