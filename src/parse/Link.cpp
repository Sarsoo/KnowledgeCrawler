#include "Link.hpp"

namespace kc {

Link::Link(const std::string &original)
{
    original_form = std::regex_replace(original, std::regex("%20"), " ");

    const auto opening_display = original_form.find('[');
    const auto closing_display = original_form.find(']', opening_display);

    display = original_form.substr(opening_display + 1, closing_display - opening_display - 1);

    const auto opening_link = closing_display + 1;
    const auto closing_link = original_form.rfind(')');

    link = original_form.substr(opening_link + 1, closing_link - opening_link - 1);

    external = link.starts_with("http");

    if(const auto sublink_pos = original_form.find('#', opening_link);
        sublink_pos != std::string::npos)
    {
        sublink = original_form.substr(sublink_pos + 1, closing_link - sublink_pos - 1);
        link = original_form.substr(opening_link + 1, sublink_pos - opening_link - 1);
    }
}

bool Link::is_external() const
{
    return external;
}

}