#include "gg/config/config.h"

//==============================================================================
namespace gg
{
//==============================================================================

bool8
config::load(string_dynamic const & line, string_dynamic & key) noexcept
{
    static string_ref constexpr k_chars_to_ignore = GG_TEXT("\0\n\r#/;");
    for (auto char_to_ignore : k_chars_to_ignore)
    {
        GG_CONTINUE_IF(char_to_ignore == line[0]);
    }

    // section

    if ('[' == line[0])
    {
        size_type position = line.find("]");
        if (string::npos == position)
        {
            return false;
        }
        key.set(line, 1, position);
    }
    else
    {
        // name = value

        size_type position = line.find("=");
        if (string::npos == position)
        {
            return false;
        }

        m_values.emplace(
            hash::fnv1a::generate(key.append('/').append(line, position)),
            string_ref(&line[position + 1]));
    }

    return true;
}

void config::unload(void) noexcept
{
    m_values.clear();
}

//==============================================================================
}
//==============================================================================
