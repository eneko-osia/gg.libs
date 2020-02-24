#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/non_copyable.h"
#include "gg/core/type/type_trait.h"

//==============================================================================
namespace gg::non_copyable_test
{
//==============================================================================

TEST_CASE("non_copyable", "[gg.non_copyable]")
{
    SECTION("assignable")
    {
        REQUIRE(!type::is_assignable<non_copyable>::value);
    }

    SECTION("constructor")
    {
        REQUIRE(!type::is_constructible<non_copyable>::value);
        REQUIRE(!type::has_trivial_constructor<non_copyable>::value);
    }

    SECTION("copy_constructor")
    {
        REQUIRE(!type::is_copyable<non_copyable>::value);
        REQUIRE(!type::has_trivial_copy<non_copyable>::value);
    }

    SECTION("destructor")
    {
        REQUIRE(!type::is_destructible<non_copyable>::value);
        REQUIRE(!type::no_destructor<non_copyable>::value);
    }

    SECTION("equality_operator")
    {
        REQUIRE(type::no_equality_operator<non_copyable>::value);
    }

    SECTION("pod")
    {
#if defined(GG_LINUX)
        REQUIRE(type::is_pod<non_copyable>::value);
#elif defined(GG_WINDOWS)
        REQUIRE(!type::is_pod<non_copyable>::value);
#endif
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<non_copyable>::value);
    }
}

//==============================================================================
}
//==============================================================================
