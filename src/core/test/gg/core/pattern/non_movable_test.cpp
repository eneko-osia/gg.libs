#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/non_movable.h"
#include "gg/core/type/type_trait.h"

//==============================================================================
namespace gg::non_movable_test
{
//==============================================================================

TEST_CASE("non_movable", "[gg.non_movable]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_assignable<non_movable>::value);
        REQUIRE(!type::has_trivial_assign<non_movable>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<non_movable>::value);
        REQUIRE(!type::has_trivial_constructor<non_movable>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copyable<non_movable>::value);
        REQUIRE(!type::has_trivial_copy<non_movable>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(!type::is_destructible<non_movable>::value);
        REQUIRE(!type::has_trivial_destructor<non_movable>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<non_movable>::value);
    }

    SECTION("pod")
    {
#if defined(GG_LINUX)
        REQUIRE(type::is_pod<non_movable>::value);
#elif defined(GG_WINDOWS)
        REQUIRE(!type::is_pod<non_movable>::value);
#endif
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<non_movable>::value);
    }
}

//==============================================================================
}
//==============================================================================
