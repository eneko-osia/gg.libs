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

class mock_observer : public imock_observer
{
public:

    // constructors

    mock_observer(void) noexcept
        : m_method1_called(0)
        , m_method2_called(0)
    {
    }

    // inquiries

    uint8 get_method1_called(void) const noexcept
    {
        return m_method1_called;
    }

    uint8 get_method2_called(void) const noexcept
    {
        return m_method2_called;
    }

private:

    // imock_observer override methods

    void on_method1(void) noexcept override
    {
        ++m_method1_called;
    }

    void on_method2(void) noexcept override
    {
        ++m_method2_called;
    }

private:

    // attributes

    uint8 m_method1_called;
    uint8 m_method2_called;
};

class mock_observable : public observable<imock_observer> {};

//==============================================================================

TEST_CASE("observable", "[gg.observable]")
{
    SECTION("assignable")
    {
        REQUIRE(!type::is_assignable<observable<imock_observer>>::value);
    }

    SECTION("constructor")
    {
        REQUIRE(!type::is_constructible<observable<imock_observer>>::value);
        REQUIRE(!type::has_trivial_constructor<observable<imock_observer>>::value);
    }

    SECTION("copy_constructor")
    {
        REQUIRE(!type::is_copyable<observable<imock_observer>>::value);
        REQUIRE(!type::has_trivial_copy<observable<imock_observer>>::value);
    }

    SECTION("destructor")
    {
        REQUIRE(!type::is_destructible<observable<imock_observer>>::value);
        REQUIRE(!type::has_trivial_destructor<observable<imock_observer>>::value);
    }

    SECTION("equality_operator")
    {
        REQUIRE(type::no_equality_operator<observable<imock_observer>>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<observable<imock_observer>>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<observable<imock_observer>>::value);
    }
}

TEST_CASE("observable.constructor", "[gg.observable]")
{
    SECTION("observable")
    {
        mock_observer observer;
        mock_observable observable;
        REQUIRE(!observable.has_observers());

        observable.add_observer(&observer);
        REQUIRE(observable.has_observers());
    }

    SECTION("observable(observable)")
    {
        mock_observer observer;
        mock_observable copied_observable;
        copied_observable.add_observer(&observer);

        mock_observable observable(copied_observable);
        REQUIRE(observable.has_observers());
        REQUIRE(copied_observable.has_observers());
    }

    SECTION("observable(rvalue_observable)")
    {
        mock_observer observer;
        mock_observable moved_observable;
        moved_observable.add_observer(&observer);

        mock_observable observable(type::move(moved_observable));
        REQUIRE(observable.has_observers());
        REQUIRE(!moved_observable.has_observers());
    }
}

TEST_CASE("observable.add_observer", "[gg.observable]")
{
    SECTION("add_observer")
    {
        mock_observer observer;
        mock_observable observable;
        REQUIRE(!observable.has_observers());

        observable.add_observer(&observer);
        REQUIRE(observable.has_observers());
        REQUIRE(observable.has_observer(&observer));
    }
}

TEST_CASE("observable.clear_observers", "[gg.observable]")
{
    SECTION("clear_observers")
    {
        mock_observer observer1;
        mock_observer observer2;
        mock_observable observable;
        observable.add_observer(&observer1);
        observable.add_observer(&observer2);

        observable.clear_observers();
        REQUIRE(!observable.has_observers());
        REQUIRE(!observable.has_observer(&observer1));
        REQUIRE(!observable.has_observer(&observer2));
    }
}

TEST_CASE("observable.remove_observer", "[gg.observable]")
{
    SECTION("remove_observer")
    {
        mock_observer observer1;
        mock_observer observer2;
        mock_observable observable;
        observable.add_observer(&observer1);
        observable.add_observer(&observer2);

        observable.remove_observer(&observer2);
        REQUIRE(observable.has_observers());
        REQUIRE(observable.has_observer(&observer1));
        REQUIRE(!observable.has_observer(&observer2));
    }
}

TEST_CASE("observable.notify_observers", "[gg.observable]")
{
    SECTION("notify_observers")
    {
        mock_observer observer;
        mock_observable observable;
        observable.add_observer(&observer);
        REQUIRE(0 == observer.get_method1_called());
        REQUIRE(0 == observer.get_method2_called());

        observable.notify_observers(&imock_observer::on_method1);
        REQUIRE(1 == observer.get_method1_called());
        REQUIRE(0 == observer.get_method2_called());

        observable.notify_observers(&imock_observer::on_method2);
        REQUIRE(1 == observer.get_method1_called());
        REQUIRE(1 == observer.get_method2_called());

        observable.notify_observers(&imock_observer::on_method1);
        REQUIRE(2 == observer.get_method1_called());
        REQUIRE(1 == observer.get_method2_called());

        observable.notify_observers(&imock_observer::on_method2);
        REQUIRE(2 == observer.get_method1_called());
        REQUIRE(2 == observer.get_method2_called());
    }
}

//==============================================================================
}
//==============================================================================
