#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/stream/file_istream.h"

//==============================================================================
namespace gg::file_istream_test
{
//==============================================================================

TEST_CASE("file_istream", "[gg.file_istream]")
{
    SECTION("pod")
    {
        REQUIRE_FALSE(type::is_pod<file_istream>());
    }

    SECTION("polymorphic")
    {
        REQUIRE_FALSE(type::is_polymorphic<file_istream>());
    }

    SECTION("sizeof")
    {
    #if defined(GG_X86)
        REQUIRE(sizeof(file_istream) == 16);
    #elif defined(GG_X86_64)
        REQUIRE(sizeof(file_istream) == 24);
    #endif
    }
}

TEST_CASE("file_istream.constructor", "[gg.file_istream]")
{
    SECTION("file_istream(filename)")
    {
        // file_istream file("temp/file.txt", stream_mode::text);

        // REQUIRE(file.is_valid());
        // REQUIRE(file.get_position() == 0);
        // REQUIRE(file.size() == 24);
    }

    SECTION("file_istream(invalid filename)")
    {
        file_istream file("temp/invalid_file.txt", stream_mode::text);

        REQUIRE_FALSE(file.is_valid());
        REQUIRE(file.get_position() == 0);
        REQUIRE(file.size() == 0);
    }
}

//==============================================================================
}
//==============================================================================
