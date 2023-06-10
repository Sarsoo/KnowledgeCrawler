#include "Link.hpp"

namespace kc {

Link::Link(std::string original)
{
    original_form = std::regex_replace(original, std::regex("%20"), " ");

    auto opening_display = original_form.find('[');
    auto closing_display = original_form.find(']', opening_display);

    display = original_form.substr(opening_display + 1, closing_display - opening_display - 1);

    auto opening_link = closing_display + 1;
    auto closing_link = original_form.rfind(')');

    link = original_form.substr(opening_link + 1, closing_link - opening_link - 1);

    auto display_pos = original_form.find('#', opening_link);

    if(display_pos != std::string::npos)
    {
        display = original_form.substr(display_pos + 1, closing_link - display_pos - 1);
    }
}

}