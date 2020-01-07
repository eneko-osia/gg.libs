#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/constant/constant.h"

//==============================================================================
namespace gg::constant_test
{
//==============================================================================

TEST_CASE("constant.int8", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(int8_min < int8_max);
    }
}

TEST_CASE("constant.uint8", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(uint8_min < uint8_max);
    }
}

TEST_CASE("constant.int16", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(int16_min < int16_max);
    }
}

TEST_CASE("constant.uint16", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(uint16_min < uint16_max);
    }
}

TEST_CASE("constant.int32", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(int32_min < int32_max);
    }
}

TEST_CASE("constant.uint32", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(uint32_min < uint32_max);
    }
}

TEST_CASE("constant.int64", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(int64_min < int64_max);
    }
}

TEST_CASE("constant.uint64", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(uint64_min < uint64_max);
    }
}

TEST_CASE("constant.float32", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(float32_min < float32_max);
    }
}

TEST_CASE("constant.float64", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(float64_min < float64_max);
    }
}

//==============================================================================
}
//==============================================================================
