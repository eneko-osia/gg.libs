#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/string/type/string_static.h"
#include "gg/core/version.h"

//==============================================================================
namespace gg::version_test
{
//==============================================================================

TEST_CASE("version", "[gg.version]")
{
    SECTION("version number")
    {
        string_static<32> version_number;
        version_number.append(version_major)
                      .append(".")
                      .append(version_minor)
                      .append(".")
                      .append(version_patch);
        REQUIRE(version_number == version_string);
    }
}

//==============================================================================
}
//==============================================================================
