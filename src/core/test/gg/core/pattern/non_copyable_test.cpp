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
    SECTION("pod")
    {
        REQUIRE_FALSE(type::is_pod<non_copyable>());
    }

    SECTION("polymorphic")
    {
        REQUIRE_FALSE(type::is_polymorphic<non_copyable>());
    }

    SECTION("sizeof")
    {
        REQUIRE(sizeof(non_copyable) == 1);
    }
}

//==============================================================================
}
//==============================================================================
