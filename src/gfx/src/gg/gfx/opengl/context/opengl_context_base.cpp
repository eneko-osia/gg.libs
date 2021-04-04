//==============================================================================
#if defined(GG_GFX_OPENGL_SUPPORT)
//==============================================================================

#include "gg/gfx/opengl/context/opengl_context_base.h"

//==============================================================================

#include "gg/core/type/convert.h"
#include "gg/core/utils/bit_field.h"
#include "gg/gfx/opengl/context/opengl_context.h"
#include "gg/gfx/opengl/opengl_includes.h"

//==============================================================================
namespace gg::gfx
{
//==============================================================================

void
opengl_context_base::clear(
    uint8 red,
    uint8 green,
    uint8 blue,
    uint8 alpha,
    opengl_clear_mode mode) const noexcept
{
    static float32 const max_uint8_float = 255.0f;
    uint32 clear_mask = 0;

    if (bit_field::is_set(mode, opengl_clear_mode::color))
    {
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        clear_mask |= GL_COLOR_BUFFER_BIT;
    }

    if (bit_field::is_set(mode, opengl_clear_mode::depth))
    {
        glDepthMask(GL_TRUE);
        clear_mask |= GL_DEPTH_BUFFER_BIT;
    }

    if (bit_field::is_set(mode, opengl_clear_mode::stencil))
    {
        glStencilMask(GL_TRUE);
        clear_mask |= GL_STENCIL_BUFFER_BIT;
    }

    glClearColor((convert::to<float32>(red) / max_uint8_float),
                 (convert::to<float32>(green) / max_uint8_float),
                 (convert::to<float32>(blue)  / max_uint8_float),
                 (convert::to<float32>(alpha) / max_uint8_float));

    glClear(clear_mask);
}

void opengl_context_base::finalize(void) noexcept
{
    type::cast_static<opengl_context *>(this)->on_finalize();
}

bool8 opengl_context_base::init(opengl_context_info const & info) noexcept
{
    if (type::cast_static<opengl_context *>(this)->on_init(info))
    {
        return true;
    }

    finalize();
    return false;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
