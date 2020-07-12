#ifndef _gg_configuration_h_
#define _gg_configuration_h_

#include "gg/core/container/map/hash_map.h"
#include "gg/core/string/type/string_dynamic.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/core/string/type/string_static.h"
#include "gg/core/type/convert.h"
#include "gg/crypt/hash/hash.h"

namespace gg
{
    class configuration final
    {
    public:

        // constructors

        configuration(void) noexcept = default;
        ~configuration(void) noexcept = default;

        // methods

        template <typename STREAM_TYPE>
        bool8 load(STREAM_TYPE & stream) noexcept
        {
            string line, section;

            bool8 success = stream.is_valid();
            while (success && stream.read_line(line.c_str(), line.max_size()))
            {
                line.trim();
                success = load(line, section);
            }

            if (!success)
            {
                unload();
            }

            return success;
        }
        void unload(void) noexcept;

        // accessors

        template <typename TYPE>
        TYPE
        get_value(string_ref const & key, TYPE const & ret_value = TYPE(0)) noexcept
        {
            string_ref value = get_value<string_ref>(key, string_ref());
            return
                value.is_empty() ? ret_value : convert::to<TYPE>(value.c_str());
        }

        // inquiries

        bool8 has_value(string_ref const & key) const noexcept
        {
            return m_values.find(hash::fnv1a::generate(key)) != m_values.end();
        }

        bool8 has_values(void) const noexcept
        {
            return !m_values.is_empty();
        }

    private:

        // type definitions

        typedef string_static<512> string;
        typedef hash_map<uint32, string_dynamic> value_map;

        // methods

        bool8 load(string_ref const & line, string & section) noexcept;

    private:

        // attributes

        value_map m_values;
    };

    template <>
    inline string_ref
    configuration::get_value<string_ref>(
        string_ref const & key,
        string_ref const & ret_value) noexcept
    {
        auto cit = m_values.find(hash::fnv1a::generate(key));
        return cit == m_values.end() ? ret_value : string_ref(cit->second);
    }
}

#endif // _gg_configuration_h_
