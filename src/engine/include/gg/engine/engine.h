#ifndef _gg_engine_h_
#define _gg_engine_h_

// include files

#include "gg/engine/engine_platform.h"

// namespace

namespace gg
{
    // class in charge of define an engine

    class engine final: public engine_platform
    {
    public:

        // constructors

        engine(data const & data) noexcept;
        ~engine(void) noexcept = default;
    };
}

#endif // _gg_engine_h_
