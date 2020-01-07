#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/container/iterator/iterator_type.h"

//==============================================================================
namespace gg::iterator_test
{
//==============================================================================

TEST_CASE("iterator", "[gg.iterator]")
{
#if defined(GG_DEBUG)
    SECTION("iterator type descriptors")
    {
        REQUIRE(
            GG_TEXT("no_const") ==
            iterator_type_descriptors[enums::cast(iterator_type::no_const)]);

        REQUIRE(
            GG_TEXT("is_const") ==
            iterator_type_descriptors[enums::cast(iterator_type::is_const)]);
    }
#endif
}

//==============================================================================
}
//==============================================================================
