#include "gg/test/catch.h"

//==============================================================================

#include "gg/engine/engine.h"

//==============================================================================
namespace gg
{
//==============================================================================

TEST_CASE("engine", "[gg.engine]")
{
    SECTION("pod")
    {
        REQUIRE(!type::is_pod<engine>());
    }

    SECTION("polymorphic")
    {
        REQUIRE(type::is_polymorphic<engine>());
    }
}

//==============================================================================
}
//==============================================================================
