#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/singleton/singleton_static.h"

//==============================================================================
namespace gg::singleton_static_test
{
//==============================================================================

class mock_singleton : public singleton_static<mock_singleton>
{
private:

    friend class singleton_static<mock_singleton>;
    mock_singleton(void) = default;
    ~mock_singleton(void) = default;
};

//==============================================================================

TEST_CASE("singleton_static", "[gg.singleton_static]")
{
    SECTION("assignable")
    {
        REQUIRE(!type::is_assignable<singleton_static<mock_singleton>>::value);
    }

    SECTION("constructor")
    {
        REQUIRE(
            !type::is_constructible<singleton_static<mock_singleton>>::value);
        REQUIRE(
            !type::has_trivial_constructor<singleton_static<mock_singleton>>::value);
    }

    SECTION("copy_constructor")
    {
        REQUIRE(
            !type::is_copyable<singleton_static<mock_singleton>>::value);
        REQUIRE(
            !type::has_trivial_copy<singleton_static<mock_singleton>>::value);
    }

    SECTION("destructor")
    {
        REQUIRE(
            !type::is_destructible<singleton_static<mock_singleton>>::value);
        REQUIRE(
            !type::has_trivial_destructor<singleton_static<mock_singleton>>::value);
    }

    SECTION("equality_operator")
    {
        REQUIRE(
            type::no_equality_operator<singleton_static<mock_singleton>>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<singleton_static<mock_singleton>>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<singleton_static<mock_singleton>>::value);
    }
}

TEST_CASE("singleton_static.get_instance", "[gg.singleton_static]")
{
    SECTION("get_instance")
    {
        mock_singleton const & instance = mock_singleton::get_instance();
        REQUIRE(&instance == &mock_singleton::get_instance());
    }
}

//==============================================================================
}
//==============================================================================
