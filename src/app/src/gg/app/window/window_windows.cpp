#if defined(GG_WINDOWS)
//==============================================================================

#include "gg/app/window/window_windows.h"

//==============================================================================

#include "gg/app/window/window_info.h"
#include "gg/app/window/window.h"

//==============================================================================
namespace gg::app
{
//==============================================================================

static window * get_window(HWND hwnd)
{
    auto user_data = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    return type::cast_reinterpret<window *>(user_data);
}

static void set_window(HWND hwnd, LPARAM lparam)
{
    auto * create_struct = type::cast_reinterpret<CREATESTRUCT *>(lparam);
    auto * win = type::cast_reinterpret<window *>(create_struct->lpCreateParams);
    SetWindowLongPtr(hwnd, GWLP_USERDATA, type::cast_reinterpret<LONG_PTR>(win));
}

static LRESULT WINAPI wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (WM_CREATE == msg)
    {
        set_window(hwnd, lparam);
    }
    else if (WM_DESTROY == msg)
    {
        PostQuitMessage(0);
        return 0;
    }

    window * win = get_window(hwnd);

    if (win)
    {
        win->handle_messages(msg, wparam, lparam);
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

//==============================================================================

window_windows::window_windows(void) noexcept
    : m_hwnd(nullptr)
    , m_wnd_class()
{
    memory::zero(&m_wnd_class);
}

window_windows::~window_windows(void)
{
    GG_ASSERT_NULL(m_hwnd);
}

//==============================================================================

void
window_windows::handle_messages(UINT msg, WPARAM wparam, LPARAM lparam) noexcept
{
    GG_UNUSED(lparam);

    // handle messages

    switch(msg)
    {
        case WM_ACTIVATEAPP:
        {
            notify_observers((TRUE == wparam) ?
                &iwindow_observer::on_gain_focus :
                &iwindow_observer::on_lost_focus);
            break;
        }

        case WM_CLOSE:
        case WM_QUIT:
        {
            notify_observers(&iwindow_observer::on_close);
            break;
        }

        default:
        {
            break;
        }
    }

#if defined(GG_INPUT)
    // handle input
    get_input_manager()->handle_messages(get_hwnd(), msg, wparam, lparam);
#endif
}

void window_windows::on_finalize(void) noexcept
{
    GG_RETURN_IF_NULL(m_hwnd);

    // unregister class

    unregister_class();
    memory::zero(&m_wnd_class);

    // destroy window

    DestroyWindow(m_hwnd);
    m_hwnd = nullptr;
}

bool8 window_windows::on_init(window_info const * info) noexcept
{
    GG_RETURN_FALSE_IF_NOT_NULL(m_hwnd);

    // register window class

    GG_RETURN_FALSE_IF_FALSE(register_class(info->m_hinstance));

    // prepare window rectangle

    DWORD window_style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    RECT rect =
    {
        0, 0,
        type::cast_static<LONG>(get_width()),
        type::cast_static<LONG>(get_height())
    };
    AdjustWindowRect(&rect, window_style, FALSE);

    // create window

    m_hwnd =
        CreateWindow(
            get_name().begin(),
            get_name().begin(),
            window_style,
            0, 0,
            rect.right - rect.left, rect.bottom - rect.top,
            nullptr,
            nullptr,
            m_wnd_class.hInstance,
            this);
    GG_RETURN_FALSE_IF_NULL(m_hwnd);

    // show display

    ShowWindow(m_hwnd, SW_SHOW);
    SetFocus(m_hwnd);
    UpdateWindow(m_hwnd);

    return true;
}

bool8 window_windows::register_class(HINSTANCE hinstance) noexcept
{
    m_wnd_class.cbSize = sizeof(WNDCLASSEX);
    m_wnd_class.style = CS_CLASSDC;
    m_wnd_class.lpfnWndProc = wndproc;
    m_wnd_class.cbClsExtra = 0;
    m_wnd_class.cbWndExtra = 0;
    m_wnd_class.hInstance = hinstance;
    m_wnd_class.hIcon = LoadIcon(0, IDI_WINLOGO);
    m_wnd_class.hIconSm = m_wnd_class.hIcon;
    m_wnd_class.hCursor = LoadCursor(0, IDC_ARROW);
    m_wnd_class.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    m_wnd_class.lpszMenuName = 0;
    m_wnd_class.lpszClassName = get_name().begin();
    return FALSE != RegisterClassEx(&m_wnd_class);
}

bool8 window_windows::unregister_class(void) noexcept
{
    return FALSE != UnregisterClass(get_name().begin(), m_wnd_class.hInstance);
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================
