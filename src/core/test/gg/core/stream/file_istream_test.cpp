#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/stream/file_istream.h"
#include "gg/core/string/type/string_ref.h"

//==============================================================================
namespace gg::file_istream_test
{
//==============================================================================

TEST_CASE("file_istream", "[gg.file_istream]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_assignable<file_istream>::value);
        REQUIRE(type::has_trivial_assign<file_istream>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<file_istream>::value);
        REQUIRE(!type::has_trivial_constructor<file_istream>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copyable<file_istream>::value);
        REQUIRE(!type::has_trivial_copy<file_istream>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<file_istream>::value);
        REQUIRE(!type::has_trivial_destructor<file_istream>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<file_istream>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<file_istream>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<file_istream>::value);
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
        file_istream file(GG_TEXT("invalid_file.txt"), stream_mode::text);
        REQUIRE(!file.is_valid());
        REQUIRE(file.get_position() == 0);
        REQUIRE(file.size() == 0);
    }
}

//==============================================================================
}
//==============================================================================
