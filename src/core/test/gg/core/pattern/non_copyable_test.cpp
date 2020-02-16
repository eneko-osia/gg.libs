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
#if defined(GG_LINUX)
        REQUIRE(type::is_pod<non_copyable>());
#elif defined(GG_WINDOWS)
        REQUIRE(!type::is_pod<non_copyable>());
#endif
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<non_copyable>());
    }

    SECTION("sizeof")
    {
        REQUIRE(sizeof(non_copyable) == 1);
    }
}

//==============================================================================
}
//==============================================================================
