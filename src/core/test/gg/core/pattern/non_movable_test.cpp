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
    SECTION("pod")
    {
        REQUIRE_FALSE(type::is_pod<non_movable>());
    }

    SECTION("polymorphic")
    {
        REQUIRE_FALSE(type::is_polymorphic<non_movable>());
    }

    SECTION("sizeof")
    {
        REQUIRE(sizeof(non_movable) == 1);
    }
}

//==============================================================================
}
//==============================================================================
