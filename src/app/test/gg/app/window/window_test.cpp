#include "gg/test/catch.h"

//==============================================================================

#include "gg/app/window/window_info.h"
#include "gg/app/window/window.h"

//==============================================================================
namespace gg::app::window_test
{
//==============================================================================

class mock_observer : public iwindow_observer
{
public:

    // constructors

    mock_observer(void) noexcept
        : m_on_close(0)
        , m_on_gain_focus(0)
        , m_on_lost_focus(0)
    {
    }

public:

    // attributes

    uint8 m_on_close;
    uint8 m_on_gain_focus;
    uint8 m_on_lost_focus;

private:

    // iwindow_observer override methods

    void on_close(void) noexcept override
    {
        ++m_on_close;
    }

    void on_gain_focus(void) noexcept override
    {
        ++m_on_gain_focus;
    }

    void on_lost_focus(void) noexcept override
    {
        ++m_on_lost_focus;
    }
};

//==============================================================================

TEST_CASE("window", "[gg.app.window]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_assignable<window>::value);
        REQUIRE(!type::has_trivial_assign<window>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<window>::value);
        REQUIRE(!type::has_trivial_constructor<window>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copyable<window>::value);
        REQUIRE(!type::has_trivial_copy<window>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<window>::value);
        REQUIRE(!type::has_trivial_destructor<window>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<window>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<window>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(type::is_polymorphic<window>::value);
    }
}

TEST_CASE("window::init", "[gg.app.window]")
{
#if defined(GG_WINDOWS)
    SECTION("init")
    {
        window_info info =
        {
            GG_TEXT("Test"),
            64,
            64,
            (HINSTANCE) GetModuleHandle(NULL)
        };

        window win;
        REQUIRE(win.init(&info));
        win.finalize();
    }
#endif
}

TEST_CASE("window::notify", "[gg.app.window]")
{
#if defined(GG_WINDOWS)
    window_info info =
    {
        GG_TEXT("Test"),
        64,
        64,
        (HINSTANCE) GetModuleHandle(NULL)
    };

    window win;
    REQUIRE(win.init(&info));

    SECTION("on_close")
    {
        mock_observer observer;
        win.add_observer(&observer);
        REQUIRE(0 == observer.m_on_close);
        SendMessage(win.get_hwnd(), WM_CLOSE, NULL, NULL);
        REQUIRE(1 == observer.m_on_close);

        SendMessage(win.get_hwnd(), WM_QUIT, NULL, NULL);
        REQUIRE(2 == observer.m_on_close);
    }

    SECTION("gain_focus")
    {
        mock_observer observer;
        win.add_observer(&observer);
        REQUIRE(0 == observer.m_on_gain_focus);
        SendMessage(win.get_hwnd(), WM_ACTIVATEAPP, true, NULL);
        REQUIRE(1 == observer.m_on_gain_focus);
    }

    SECTION("lost_focus")
    {
        mock_observer observer;
        win.add_observer(&observer);
        REQUIRE(0 == observer.m_on_lost_focus);
        SendMessage(win.get_hwnd(), WM_ACTIVATEAPP, false, NULL);
        REQUIRE(1 == observer.m_on_lost_focus);
    }

    win.finalize();
#endif
}

//==============================================================================
}
//==============================================================================
