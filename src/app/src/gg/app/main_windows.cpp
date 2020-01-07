#if defined(GG_WINDOWS)
//==============================================================================

#include "gg/app/application/application.h"
#include "gg/app/data/data.h"
#include "gg/core/macro/macro.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/core/string/type/string_static.h"

//==============================================================================

int main(int argc, char const ** argv)
{
    gg::data data;

    // populate data

    for (int i = 0; i < argc; ++i)
    {
        data.add_argument(gg::string_ref(argv[i]));
    }

    // run main

    return gg::application::main(data);
}

//==============================================================================

INT WINAPI WinMain(
    HINSTANCE hinstance,
    HINSTANCE GG_UNUSED_ARGUMENT(h_prev_instance),
    LPSTR GG_UNUSED_ARGUMENT(cmd_line),
    int GG_UNUSED_ARGUMENT(n_cmd_show))
{
    // get command line arguments

    int argc = 0;
    LPWSTR * argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    GG_RETURN_VALUE_IF_NULL(argv, EXIT_FAILURE);

    // populate data

    gg::data data;
    data.set_hinstance(hinstance);

    for (int i = 0; i < argc; ++i)
    {
        size_t counter = 0;
        gg::string_static<512> buffer;
        wcstombs_s(
            &counter,
            buffer.begin(),
            buffer.max_size(),
            argv[i],
            buffer.max_size());
        data.add_argument(gg::string_ref(buffer));
    }

    // free arguments

    LocalFree(argv);

    // run main

    return gg::application::main(data);
}

//==============================================================================
#endif
//==============================================================================
