//==============================================================================
#if defined(GG_GFX_OPENGL_SUPPORT)
//==============================================================================

#include "gg/gfx/opengl/shader/opengl_shader_format.h"

//==============================================================================
namespace gg::gfx
{
//==============================================================================

uint32 const opengl_shader_format::k_invalid_attribute_location = uint32_max;
uint32 const opengl_shader_format::k_invalid_uniform_location = uint32_max;

//==============================================================================

void opengl_shader_format::add_attribute(string_ref const & name) noexcept
{
    m_attributes.emplace_back(k_invalid_attribute_location, name);
}

void opengl_shader_format::add_uniform(string_ref const & name) noexcept
{
    m_uniforms.emplace_back(k_invalid_uniform_location, name);
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
