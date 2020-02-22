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
    SECTION("assignable")
    {
        REQUIRE(!type::is_assignable<non_movable>::value);
    }

    SECTION("constructor")
    {
        REQUIRE(!type::is_constructible<non_movable>::value);
        REQUIRE(!type::no_constructor<non_movable>::value);
    }

    SECTION("copy_constructor")
    {
        REQUIRE(!type::is_copyable<non_movable>::value);
        REQUIRE(!type::no_copy_constructor<non_movable>::value);
    }

    SECTION("destructor")
    {
        REQUIRE(!type::is_destructible<non_movable>::value);
        REQUIRE(!type::no_destructor<non_movable>::value);
    }

    SECTION("equality_operator")
    {
        REQUIRE(type::no_equality_operator<non_movable>::value);
    }

    SECTION("pod")
    {
#if defined(GG_LINUX)
        REQUIRE(type::is_pod<non_movable>::value;
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
