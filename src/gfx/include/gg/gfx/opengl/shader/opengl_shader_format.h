#ifndef _gg_gfx_opengl_shader_format_h_
#define _gg_gfx_opengl_shader_format_h_

#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/string/type/string_dynamic.h"
#include "gg/core/string/type/string_ref.h"

namespace gg::gfx
{
    // struct

    struct opengl_attribute
    {
        opengl_attribute(uint32 location, string_ref const & name)
            : m_location(location)
            , m_name(name)
        {
        }

        uint32 m_location;
        string_dynamic m_name;
    };

    struct opengl_uniform
    {
        opengl_uniform(uint32 location, string_ref const & name)
            : m_location(location)
            , m_name(name)
        {
        }

        uint32 m_location;
        string_dynamic m_name;
    };

    class opengl_shader_format
    {
    public:

        // type definitions

        typedef opengl_attribute attribute_type;
        typedef opengl_uniform uniform_type;

        // constants

        static uint32 const k_invalid_attribute_location;
        static uint32 const k_invalid_uniform_location;

        // constructors

        opengl_shader_format(void) noexcept = default;
        ~opengl_shader_format(void) noexcept = default;

        // methods

        void add_attribute(string_ref const & name) noexcept;
        void add_uniform(string_ref const & name) noexcept;

    private:

        // type definitions

        typedef array_dynamic<attribute_type> attribute_container;
        typedef array_dynamic<uniform_type> uniform_container;

    private:

        // attributes

        attribute_container m_attributes;
        uniform_container m_uniforms;
    };
}

#endif // _gg_gfx_opengl_shader_format_h_
