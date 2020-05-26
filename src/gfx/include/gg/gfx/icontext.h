
#ifndef _gg_gfx_icontext_h_
#define _gg_gfx_icontext_h_

// include files

#include "gg/core/type/type.h"

// namespace

namespace gg
{
    // namespace in charge of define graphics

    namespace gfx
    {
        // interface in charge of define graphics context

        class icontext
        {
        public:

            // constructors

            virtual ~icontext(void) noexcept = default;

            // methods

            virtual void finalize(void) noexcept = 0;
            virtual bool8 init(void) noexcept = 0;
        };
    }
}

#endif // _gg_gfx_icontext_h_
