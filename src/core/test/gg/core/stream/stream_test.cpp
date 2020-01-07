#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/stream/stream_defs.h"

//==============================================================================
namespace gg::stream_test
{
//==============================================================================

TEST_CASE("stream", "[gg.stream]")
{
#if defined(GG_DEBUG)
    SECTION("stream mode descriptors")
    {
        REQUIRE(
            GG_TEXT("binary") ==
            stream_mode_descriptors[enums::cast(stream_mode::binary)]);

        REQUIRE(
            GG_TEXT("text") ==
            stream_mode_descriptors[enums::cast(stream_mode::text)]);
    }
#endif
}

//==============================================================================
}
//==============================================================================
