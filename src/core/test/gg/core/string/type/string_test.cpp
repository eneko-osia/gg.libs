#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/string/type/string.h"

//==============================================================================
namespace gg::string_test
{
//==============================================================================

TEST_CASE("string::compare", "[gg.string]")
{
    SECTION("compare")
    {
        char8 text[] =
            GG_TEXT(
                "Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit,\r\n");
        REQUIRE(
            string::compare(
                text,
                "Lorem ipsum dolor sit amet, consectetur "
                "adipiscing elit,\r\n") == 0);
    }
}

TEST_CASE("string::find", "[gg.string]")
{
    SECTION("find")
    {
        char8 text[] =
            GG_TEXT(
                "Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit,\r\n");
        REQUIRE((string::find(text, GG_TEXT("consectetur")) - text) == 28);
    }
}

TEST_CASE("string::length", "[gg.string]")
{
    SECTION("length")
    {
        char8 text[] =
            GG_TEXT(
                "Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit,\r\n");
        REQUIRE(string::length(text) == 58);
    }
}

TEST_CASE("string::trim", "[gg.string]")
{
    SECTION("trim")
    {
        char8 text[] =
            GG_TEXT(
                " Lorem ipsum dolor sit amet, consectetur adipiscing elit,\r\n"
                " \tsed do eiusmod tempor incididunt ut labore et dolore magna \n"
                " aliqua.");

        REQUIRE(string::length(text) == 129);
        string::trim(text, string::length(text));

        REQUIRE(
            string::compare(
                text,
                GG_TEXT(
                    "Loremipsumdolorsitamet,consecteturadipiscingelit,"
                    "seddoeiusmodtemporincididuntutlaboreetdoloremagna"
                    "aliqua.")) == 0);
        REQUIRE(string::length(text) == 105);
    }

    SECTION("trim custom delims")
    {
        char8 text[] =
            GG_TEXT(
                " Lorem ipsum dolor sit amet, consectetur adipiscing elit,\r\n"
                " \tsed do eiusmod tempor incididunt ut labore et dolore magna \n"
                " aliqua.");

        REQUIRE(string::length(text) == 129);
        string::trim(text, string::length(text), GG_TEXT("abc"));

        REQUIRE(
            string::compare(
                text,
                GG_TEXT(
                    " Lorem ipsum dolor sit met, onsetetur dipising elit,\r\n"
                    " \tsed do eiusmod tempor inididunt ut lore et dolore mgn \n"
                    " liqu.")) == 0);
        REQUIRE(string::length(text) == 117);
    }
}

//==============================================================================
}
//==============================================================================
