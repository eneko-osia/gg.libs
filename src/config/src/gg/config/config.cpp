#include "gg/config/config.h"

//==============================================================================

#include "gg/core/stream/file_istream.h"
#include "gg/core/string/type/string_static.h"

//==============================================================================
namespace gg
{
//==============================================================================

bool8 config::load(file_istream & file) noexcept
{
    typedef string_static<512> temp_string;

    bool8 success = file.is_valid();
    temp_string line;
    temp_string section;
    temp_string name;
    temp_string value;

    while (success && file.read_line(line))
    {
        string::trim(line.begin(), line.size());

        // ignored values

        if (line.is_empty() ||
            '\0' == line[0] ||
            '\n' == line[0] ||
            '\r' == line[0] ||
            '#' == line[0] ||
            '/' == line[0] ||
            ';' == line[0])
        {
            continue;
        }

        // section

        if ('[' == line[0])
        {
            size_type position = line.find("]");

            if (string::npos == position)
            {
                success = false;
                continue;
            }

            // get section

            section.set(line, 1, position);
            string::trim(section.begin(), section.size());

            continue;
        }

        // name = value

        size_type equal_position = line.find("=");

        if (string::npos == equal_position)
        {
            success = false;
            continue;
        }

        // get name

        name.set(line, 0, equal_position);
        string::trim(name.begin(), name.size());

        // get value

        value.set(line, equal_position + 1, line.size());
        string::trim(value.begin(), value.size());

        // insert into config

        string_static<1024> key;
        key.set(section).append("/").append(name);
        m_values.emplace(hash::fnv1a::generate(key), value);
    }

    return success;
}

void config::unload(void) noexcept
{
    m_values.clear();
}

//==============================================================================
}
//==============================================================================
