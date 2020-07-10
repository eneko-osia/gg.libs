#ifndef _gg_config_h_
#define _gg_config_h_

#include "gg/core/container/map/hash_map.h"
#include "gg/core/string/type/string_dynamic.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/core/type/convert.h"
#include "gg/crypt/hash/hash.h"

namespace gg
{
    class config final
    {
    public:

        // constructors

        config(void) noexcept = default;
        ~config(void) noexcept = default;

        // methods

        template <typename STREAM_TYPE>
        bool8 load(STREAM_TYPE & stream) noexcept
        {
            bool8 success = stream.is_valid();
            if (success)
            {
                static size_type constexpr k_initial_size = 512;
                string_dynamic key, line;
                key.reserve(k_initial_size);
                line.reserve(k_initial_size);

                while (stream.read_line(line.c_str(), line.max_size()))
                {
                    string::trim(line.c_str(), line.size());
                    success = load(line, key);
                }

                if (!success)
                {
                    unload();
                }
            }
            return success;
        }
        void unload(void) noexcept;

        // accessors

        template <typename TYPE>
        TYPE
        get_value(string_ref const & key, TYPE const & ret_value) noexcept
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

    private:

        // type definitions

        typedef hash_map<uint32, string_dynamic> value_map;

        // methods

        bool8
        load(string_dynamic const & line, string_dynamic & key) noexcept;

    private:

        // attributes

        value_map m_values;
    };

    template <>
    string_ref
    config::get_value<string_ref>(
        string_ref const & key,
        string_ref const & ret_value) noexcept
    {
        auto cit = m_values.find(hash::fnv1a::generate(key));
        return cit == m_values.end() ? ret_value : string_ref(cit->second);
    }
}

#endif // _gg_config_h_
