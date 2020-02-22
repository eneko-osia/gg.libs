#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/observer/observable.h"

//==============================================================================
namespace gg::observable_test
{
//==============================================================================

class imock_observer
{
public:

    // virtual methods

    virtual void on_method1(void) noexcept = 0;
    virtual void on_method2(void) noexcept = 0;
};

class mock_observable
    : public imock_observer
    , public observable<imock_observer>
{
public:

    // constructors

    mock_observable(void) noexcept
        : m_method1_called(false)
        , m_method2_called(false)
    {
    }

    // inquiries

    bool8 is_method1_called(void) const noexcept
    {
        return m_method1_called;
    }

    bool8 is_method2_called(void) const noexcept
    {
        return m_method2_called;
    }

private:

    // imock_observer override methods

    void on_method1(void) noexcept override
    {
        m_method1_called = true;
    }

    void on_method2(void) noexcept override
    {
        m_method2_called = true;
    }

private:

    // attributes

    bool8 m_method1_called : 1;
    bool8 m_method2_called : 1;
};

//==============================================================================

TEST_CASE("observable", "[gg.observable]")
{
    SECTION("pod")
    {
        REQUIRE_FALSE(type::is_pod<observable<imock_observer>>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE_FALSE(type::is_polymorphic<observable<imock_observer>>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(
            sizeof(observable<imock_observer>) ==
            sizeof(array_dynamic<imock_observer *>));
    }
}

TEST_CASE("observable.constructor", "[gg.observable]")
{
    SECTION("observable()")
    {
        mock_observable observable;
        REQUIRE_FALSE(observable.has_observers());

        observable.add_observer(&observable);
        REQUIRE(observable.has_observers());
    }

    SECTION("observable(observable)")
    {
        mock_observable copied_observable;
        copied_observable.add_observer(&copied_observable);
        REQUIRE(copied_observable.has_observers());

        mock_observable observable(copied_observable);
        REQUIRE(observable.has_observers());
    }

    SECTION("observable(rvalue_observable)")
    {
        mock_observable moved_observable;
        moved_observable.add_observer(&moved_observable);
        mock_observable observable(type::move(moved_observable));
        REQUIRE(observable.has_observers());
        REQUIRE_FALSE(moved_observable.has_observers());
    }
}

TEST_CASE("observable.add_observer", "[gg.observable]")
{
    SECTION("add_observer")
    {
        mock_observable observable;
        observable.add_observer(&observable);
        REQUIRE(observable.has_observer(&observable));
        REQUIRE(observable.has_observers());
    }
}

TEST_CASE("observable.clear_observers", "[gg.observable]")
{
    SECTION("clear_observers")
    {
        mock_observable observable;
        observable.add_observer(&observable);
        REQUIRE(observable.has_observer(&observable));
        observable.clear_observers();
        REQUIRE_FALSE(observable.has_observer(&observable));
        REQUIRE_FALSE(observable.has_observers());
    }
}

TEST_CASE("observable.remove_observer", "[gg.observable]")
{
    SECTION("remove_observer")
    {
        mock_observable observable;
        observable.add_observer(&observable);
        REQUIRE(observable.has_observer(&observable));
        observable.remove_observer(&observable);
        REQUIRE_FALSE(observable.has_observer(&observable));
        REQUIRE_FALSE(observable.has_observers());
    }
}

TEST_CASE("observable.notify_observers", "[gg.observable]")
{
    SECTION("notify_observers")
    {
        mock_observable observable;
        observable.add_observer(&observable);
        REQUIRE_FALSE(observable.is_method1_called());
        REQUIRE_FALSE(observable.is_method2_called());

        observable.notify_observers(&imock_observer::on_method1);
        REQUIRE(observable.is_method1_called());
        REQUIRE_FALSE(observable.is_method2_called());

        observable.notify_observers(&imock_observer::on_method2);
        REQUIRE(observable.is_method1_called());
        REQUIRE(observable.is_method2_called());
    }
}

//==============================================================================
}
//==============================================================================
