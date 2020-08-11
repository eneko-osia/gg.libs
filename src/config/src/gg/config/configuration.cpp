#include "gg/config/configuration.h"

//==============================================================================
namespace gg
{
//==============================================================================

bool8
configuration::load(string_ref const & line, string & section) noexcept
{
    GG_RETURN_TRUE_IF(line.is_empty());
    static string_ref constexpr k_chars_to_ignore = GG_TEXT("-/;#\r\n");
    for (auto char_to_ignore : k_chars_to_ignore)
    {
        GG_RETURN_TRUE_IF(char_to_ignore == line[0]);
    }

    // section

    size_type equal_position = line.find("=");
    if (gg::string::npos != equal_position)
    {
        GG_RETURN_FALSE_IF(section.is_empty());

        // name = value

        string name(line, equal_position);
        name.trim();

        string value(&line[equal_position + 1]);
        value.trim();

        string_static<1024> key;
        key.set(section).append('/').append(name);

        m_values[hash::fnv1a::generate(key)] = type::move(value);
    }
    else
    {
        size_type section_start = line.find("[");
        size_type section_end = line.find("]");

        GG_RETURN_FALSE_IF(
            gg::string::npos == section_start ||
            gg::string::npos == section_end);

        section.set(line, section_start + 1, section_end - 1);
        section.trim();
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
