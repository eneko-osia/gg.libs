#ifndef _gg_config_h_
#define _gg_config_h_

// include files

#include "gg/core/container/map/hash_map.h"
#include "gg/core/string/type/string_dynamic.h"

// namespace

namespace gg
{
    // forward declarations

    class file_istream;
    class string_ref;

    // class in charge of define a config

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

        bool8 get_bool(
            string_ref const & key,
            bool8 ret_value = false) const noexcept;

        float32 get_float(
            string_ref const & key,
            float32 ret_value = 0.0f) const noexcept;

        int32 get_int(
            string_ref const & key,
            int32 ret_value = 0) const noexcept;

        string_ref get_string(
            string_ref const & key,
            string_ref ret_value = GG_TEXT("")) const noexcept;

        uint32 get_uint(
            string_ref const & key,
            uint32 ret_value = 0) const noexcept;

        // inquiries

        bool8 has_value(string_ref const & key) const noexcept;

    private:

        // type definitions

        typedef hash_map<uint32, string_dynamic> ret_value_map;

    private:

        // attributes

        ret_value_map m_values;
    };
}

#endif // _gg_config_h_
