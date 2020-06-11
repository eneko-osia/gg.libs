#ifndef _gg_config_h_
#define _gg_config_h_

#include "gg/core/container/map/hash_map.h"
#include "gg/core/string/type/string_dynamic.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/core/type/convert.h"
#include "gg/crypt/hash/hash.h"

namespace gg
{
    class file_istream;

    class config final
    {
    public:

        // constructors

        config(void) noexcept = default;
        ~config(void) noexcept = default;

        // methods

        bool8 load(file_istream & file) noexcept;
        void unload(void) noexcept;

        // accessors

        template <typename TYPE>
        TYPE
        get_value(string_ref const & key, TYPE ret_value) noexcept
        {
            auto value = get_value<string_ref>(key, string_ref());
            return value.is_empty() ? ret_value : convert::to<TYPE>(value.c_str());
        }

        // inquiries

        bool8 has_value(string_ref const & key) const noexcept
        {
            return m_values.find(hash::fnv1a::generate(key)) != m_values.end();
        }

    private:

        // type definitions

        typedef hash_map<uint32, string_dynamic> value_map;

        // attributes

        value_map m_values;
    };

    template <>
    string_ref
    config::get_value<string_ref>(string_ref const & key, string_ref ret_value) noexcept
    {
        auto cit = m_values.find(hash::fnv1a::generate(key));
        return cit == m_values.end() ? ret_value : cit->second;
    }
}

#endif // _gg_config_h_
