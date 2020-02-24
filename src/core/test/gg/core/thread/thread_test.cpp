#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/thread/thread.h"
#include "gg/core/time/type/second.h"
#include "gg/core/time/utils/time_utils.h"
#include "gg/core/type/type_trait.h"

//==============================================================================
namespace gg::thread_test
{
//==============================================================================

void fast_increment(int32 & value, int32 amount)
{
    value += amount;
}

void slow_increment(int32 & value, int32 amount)
{
    thread::current::sleep(second(1));
    value += amount;
}

//==============================================================================

TEST_CASE("thread", "[gg.thread]")
{
    SECTION("assignable")
    {
        REQUIRE(!type::is_assignable<thread>::value);
    }

    SECTION("constructor")
    {
        REQUIRE(!type::is_constructible<thread>::value);
        REQUIRE(!type::has_trivial_constructor<thread>::value);
    }

    SECTION("copy_constructor")
    {
        REQUIRE(!type::is_copyable<thread>::value);
        REQUIRE(!type::has_trivial_copy<thread>::value);
    }

    SECTION("destructor")
    {
        REQUIRE(type::is_destructible<thread>::value);
        REQUIRE(!type::has_trivial_destructor<thread>::value);
    }

    SECTION("equality_operator")
    {
        REQUIRE(type::no_equality_operator<thread>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<thread>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<thread>::value);
    }
}

TEST_CASE("thread.constructor", "[gg.thread]")
{
    SECTION("thread(function)")
    {
        int32 value = 0;
        thread t(&fast_increment, type::ref(value), 1);
        t.join();
        REQUIRE(value == 1);
    }

    SECTION("thread(lambda)")
    {
        int32 value = 0;
        thread t([&value, amount = 1](void) { value += amount; });
        t.join();
        REQUIRE(value == 1);
    }
}

TEST_CASE("thread.max_threads", "[gg.thread]")
{
    SECTION("max_threads")
    {
        REQUIRE(thread::max_threads() > 0);
    }
}

TEST_CASE("thread.detach", "[gg.thread]")
{
    SECTION("detach")
    {
        int32 value = 0;
        thread t(&slow_increment, type::ref(value), 5);
        REQUIRE(t.is_joinable());
        t.detach();
        REQUIRE(!t.is_joinable());
        REQUIRE(value == 0);
    }
}

TEST_CASE("thread.join", "[gg.thread]")
{
    SECTION("join")
    {
        int32 value = 0;
        thread t(&fast_increment, type::ref(value), 5);
        REQUIRE(t.is_joinable());
        t.join();
        REQUIRE(!t.is_joinable());
        REQUIRE(value == 5);
    }
}

TEST_CASE("thread.get_id", "[gg.thread]")
{
    SECTION("get_id")
    {
        thread t1([](void) {});
        thread t2([](void) {});
        REQUIRE(t1.get_id() != t2.get_id());
        t1.join();
        t2.join();
    }
}

//==============================================================================

TEST_CASE("thread.current.sleep", "[gg.thread]")
{
    SECTION("sleep")
    {
        second start = time_utils::clock_now<second>();
        thread::current::sleep(second(1));
        second end = time_utils::clock_now<second>();
        REQUIRE((end - start).get() >= 1);
    }
}

TEST_CASE("thread.current.get_id", "[gg.thread]")
{
    SECTION("get_id")
    {
        thread t([](void) {});
        REQUIRE(thread::current::get_id() != t.get_id());
        t.join();
    }
}

//==============================================================================
}
//==============================================================================
