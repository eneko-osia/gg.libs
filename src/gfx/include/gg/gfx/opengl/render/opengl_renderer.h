#ifndef _gg_gfx_opengl_renderer_h_
#define _gg_gfx_opengl_renderer_h_

#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/container/container.h"

namespace gg::gfx
{
    template <typename RENDER_KEY_TYPE>
    class opengl_renderer
    {
    public:

        // type definitions

        typedef RENDER_KEY_TYPE render_key_type;

        // constructors

        opengl_renderer(void) noexcept = default;
        virtual ~opengl_renderer(void) = default;

        // methods

        void add_key(render_key_type && key)
        {
            m_render_keys.emplace_back(type::forward(key));
        }

        void render(void) noexcept
        {
            // effect_type const * effect = nullptr;
            // effect_type const * prev_effect = nullptr;
            // render_key_type const * prev_key = nullptr;

            size_type prev_key = 0;
            for (size_type i = 0; i < m_render_keys.size(); ++i)
            {
                m_render_keys[i].pre_render();
                // effect = get_effect(key.get_effect_id());
                // if (effect && effect->is_enabled())
                // {
                //     if ((!prev_effect) || (effect != prev_effect))
                //     {
                //         if (prev_effect) { prev_effect->reset(prev_key); }
                //         effect->upload(key);
                //     }
                //     effect->render(key, prev_key);
                //     prev_key = i;
                //     prev_effect = effect;
                // }
                m_render_keys[i].post_render();
            }

            // if (prev_effect)
            // {
            //     prev_effect->reset(prev_key);
            // }
        }

        template <typename FUNCTION>
        void sort(FUNCTION && function)
        {
            container::sort(
                m_render_keys.begin(),
                m_render_keys.end(),
                type::forward<FUNCTION>(function));
        }

    private:

        // type definitions

        typedef array_dynamic<render_key_type> render_key_array;

    private:

        // attributes

        render_key_array m_render_keys;
    };
}

#endif // _gg_gfx_opengl_renderer_h_
