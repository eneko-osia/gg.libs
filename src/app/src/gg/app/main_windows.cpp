#if defined(GG_WINDOWS)
//==============================================================================

#include "gg/app/data/data.h"
#include "gg/app/runtime/runtime.h"
#include "gg/core/string/type/string_static.h"

//==============================================================================

int main(int argc, char const ** argv)
{
    gg::app::data data;

    for (int i = 0; i < argc; ++i)
    {
        data.add_argument(argv[i]);
    }

    return gg::app::runtime::main(data);
}

//==============================================================================

INT WINAPI WinMain(
    HINSTANCE hinstance,
    HINSTANCE GG_UNUSED_ARGUMENT(h_prev_instance),
    LPSTR GG_UNUSED_ARGUMENT(cmd_line),
    int GG_UNUSED_ARGUMENT(n_cmd_show))
{
    int argc = 0;
    LPWSTR * argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    GG_RETURN_VALUE_IF(!argv, EXIT_FAILURE);

    gg::app::data data;

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
        data.add_argument(buffer);
    }
    LocalFree(argv);

    data.set_hinstance(hinstance);

    return gg::app::runtime::main(data);
}

//==============================================================================
#endif
//==============================================================================
