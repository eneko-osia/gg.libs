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
    bool8 success = file.is_valid();
    if (success)
    {
        static size_type constexpr k_max_size = 512;
        string_static<k_max_size> line, section, value;
        string_static<k_max_size << 1> key;
        while (file.read_line(line))
        {
            string::trim(line.begin(), line.size());

            static string_ref constexpr k_chars_to_ignore = GG_TEXT("\0\n\r#/;");
            for (auto char_to_ignore : k_chars_to_ignore)
            {
                if (char_to_ignore == line[0])
                {
                    continue;
                }
            }

            // section

            if ('[' == line[0])
            {
                size_type position = line.find("]");
                if (string::npos == position)
                {
                    success = false;
                    break;
                }

                section.set(line, 1, position);
            }
            else
            {
                // name = value

                size_type position = line.find("=");
                if (string::npos == position)
                {
                    success = false;
                    break;
                }

                key.set(section).append('/').append(line, position);
                value.set(line, position + 1, line.size());
                m_values.emplace(hash::fnv1a::generate(key), value);
            }
        }

        if (!success)
        {
            m_values.clear();
        }
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
