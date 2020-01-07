#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/memory/memory.h"
#include "gg/core/memory/memory_defs.h"

//==============================================================================
namespace gg::memory_test
{
//==============================================================================

TEST_CASE("memory", "[gg.memory]")
{
#if defined(GG_DEBUG)
    SECTION("memory owner mode descriptors")
    {
        REQUIRE(
            GG_TEXT("is_not_owner") ==
            memory_owner_mode_descriptors[
                enums::cast(memory_owner_mode::is_not_owner)]);

        REQUIRE(
            GG_TEXT("is_owner") ==
            memory_owner_mode_descriptors[
                enums::cast(memory_owner_mode::is_owner)]);
    }
#endif
}

//==============================================================================
}
//==============================================================================
