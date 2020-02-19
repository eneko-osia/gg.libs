#include "gg/engine/engine_base.h"

//==============================================================================
namespace gg
{
//==============================================================================

engine_base::engine_base(data const & data) noexcept
    : application(data)
    , m_modules()
{
}

engine_base::~engine_base(void) noexcept
{
}

//==============================================================================

int32 engine_base::main(void) noexcept
{
    if (init())
    {
        int32 result = run();
        finalize();
        return result;
    }

    return EXIT_FAILURE;
}

//==============================================================================
}
//==============================================================================
