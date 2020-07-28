#include "gg/config/configuration.h"

//==============================================================================
namespace gg
{
//==============================================================================

bool8
configuration::load(string_ref const & line, string & section) noexcept
{
    static string_ref constexpr k_chars_to_ignore = GG_TEXT("\0\n\r#/;");
    for (auto char_to_ignore : k_chars_to_ignore)
    {
        GG_RETURN_TRUE_IF(char_to_ignore == line[0]);
    }

    // section

    if ('[' == line[0])
    {
        size_type position = line.find("]");
        GG_RETURN_FALSE_IF(gg::string::npos == position);
        section.set(line, 1, position - 1);
        section.trim();
    }
    else if (!section.is_empty())
    {
        // name = value

        size_type position = line.find("=");
        GG_RETURN_FALSE_IF(gg::string::npos == position);

        string name(line, position);
        name.trim();

        string value(&line[position + 1]);
        value.trim();

        string_static<1024> key;
        key.set(section).append('/').append(name);

        m_values.emplace(hash::fnv1a::generate(key), value);
    }
    else
    {
        return false;
    }

    return true;
}

void configuration::unload(void) noexcept
{
    m_values.clear();
}

//==============================================================================
}
//==============================================================================
