#if defined(GG_LINUX)
//==============================================================================

#include "gg/app/data/data.h"
#include "gg/app/runtime/runtime.h"

//==============================================================================

int main(int argc, char const **argv)
{
    gg::app::data data;

    // populate data

    for (int i = 0; i < argc; ++i)
    {
        data.add_argument(argv[i]);
    }

    // run main

    return gg::app::runtime::main(data);
}

//==============================================================================
#endif
//==============================================================================
