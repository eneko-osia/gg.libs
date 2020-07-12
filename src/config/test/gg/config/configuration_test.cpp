#include "gg/test/catch.h"

//==============================================================================

#include "gg/config/configuration.h"
#include "gg/core/stream/memory_istream.h"
#include "gg/core/string/type/string_dynamic.h"

//==============================================================================
namespace gg::configuration_test
{
//==============================================================================

TEST_CASE("configuration", "[gg.configuration]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_assignable<configuration>::value);
        REQUIRE(!type::has_trivial_assign<configuration>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<configuration>::value);
        REQUIRE(!type::has_trivial_constructor<configuration>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copyable<configuration>::value);
        REQUIRE(!type::has_trivial_copy<configuration>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<configuration>::value);
        REQUIRE(!type::has_trivial_destructor<configuration>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<configuration>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<configuration>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<configuration>::value);
    }
}

TEST_CASE("configuration.constructor", "[gg.configuration]")
{
    SECTION("configuration")
    {
        configuration config;
        REQUIRE(!config.has_values());
    }
}

TEST_CASE("configuration.load", "[gg.configuration]")
{
    SECTION("load")
    {
        string_dynamic data = "[section] \n my_value = 4";
        memory_istream stream(
            memory_buffer_ref((byte *) data.c_str(), data.size()));
        configuration config;
        REQUIRE(config.load(stream));
        REQUIRE(config.has_values());
    }

    SECTION("load - invalid section")
    {
        string_dynamic data = "[section \n my_value = 4";
        memory_istream stream(
            memory_buffer_ref((byte *) data.c_str(), data.size()));
        configuration config;
        REQUIRE(!config.load(stream));
        REQUIRE(!config.has_values());
    }

    SECTION("load - invalid value")
    {
        string_dynamic data = "[section] \n my_value 1as 4";
        memory_istream stream(
            memory_buffer_ref((byte *) data.c_str(), data.size()));
        configuration config;
        REQUIRE(!config.load(stream));
        REQUIRE(!config.has_values());
    }
}

TEST_CASE("configuration.unload", "[gg.configuration]")
{
    SECTION("unload")
    {
        string_dynamic data = "[section] \n my_value = 4";
        memory_istream stream(
            memory_buffer_ref((byte *) data.c_str(), data.size()));
        configuration config;
        REQUIRE(config.load(stream));
        REQUIRE(config.has_values());
        config.unload();
        REQUIRE(!config.has_values());
    }
}

TEST_CASE("configuration.get_value", "[gg.configuration]")
{
    string_dynamic data =
        "[section]\n"
        "bool8 = 1\n"
        "int8 = -8\n"
        "uint8 = 8\n"
        "int16 = -16\n"
        "uint16 = 16\n"
        "int32 = -32\n"
        "uint32 = 32\n"
        "int64 = -64\n"
        "uint64 = 64\n"
        "float32 = 32.1\n"
        "float64 = 64.1\n"
        "char8 = a\n"
        "uchar8 = b\n"
        "char16 = c\n"
        "uchar16 = d\n"
        "char32 = e\n"
        "uchar32 = f\n"
        "string = this is a string\n";
    memory_istream stream(memory_buffer_ref((byte *) data.c_str(), data.size()));
    configuration config;
    REQUIRE(config.load(stream));

    SECTION("get_value<bool8>")
    {
        REQUIRE(config.get_value<bool8>(GG_TEXT("section/bool8")));
    }

    SECTION("get_value<bool8> - invalid")
    {
        REQUIRE(!config.get_value<bool8>(GG_TEXT("section/bool8_invalid")));
    }

    SECTION("get_value<int8>")
    {
        REQUIRE(-8 == config.get_value<int8>(GG_TEXT("section/int8")));
    }

    SECTION("get_value<int8> - invalid")
    {
        REQUIRE(0 == config.get_value<int8>(GG_TEXT("section/int8_invalid")));
    }

    SECTION("get_value<uint8>")
    {
        REQUIRE(8 == config.get_value<uint8>(GG_TEXT("section/uint8")));
    }

    SECTION("get_value<uint8> - invalid")
    {
        REQUIRE(0 == config.get_value<uint8>(GG_TEXT("section/uint8_invalid")));
    }

    SECTION("get_value<int16>")
    {
        REQUIRE(-16 == config.get_value<int16>(GG_TEXT("section/int16")));
    }

    SECTION("get_value<int16> - invalid")
    {
        REQUIRE(0 == config.get_value<int16>(GG_TEXT("section/int16_invalid")));
    }

    SECTION("get_value<uint16>")
    {
        REQUIRE(16 == config.get_value<uint16>(GG_TEXT("section/uint16")));
    }

    SECTION("get_value<uint16> - invalid")
    {
        REQUIRE(0 == config.get_value<uint16>(GG_TEXT("section/uint16_invalid")));
    }

    SECTION("get_value<int32>")
    {
        REQUIRE(-32 == config.get_value<int32>(GG_TEXT("section/int32")));
    }

    SECTION("get_value<int32> - invalid")
    {
        REQUIRE(0 == config.get_value<int32>(GG_TEXT("section/int32_invalid")));
    }

    SECTION("get_value<uint32>")
    {
        REQUIRE(32 == config.get_value<uint32>(GG_TEXT("section/uint32")));
    }

    SECTION("get_value<uint32> - invalid")
    {
        REQUIRE(0 == config.get_value<uint32>(GG_TEXT("section/uint32_invalid")));
    }

    SECTION("get_value<int64>")
    {
        REQUIRE(-64 == config.get_value<int64>(GG_TEXT("section/int64")));
    }

    SECTION("get_value<int64> - invalid")
    {
        REQUIRE(0 == config.get_value<int64>(GG_TEXT("section/int64_invalid")));
    }

    SECTION("get_value<uint64>")
    {
        REQUIRE(64 == config.get_value<uint64>(GG_TEXT("section/uint64")));
    }

    SECTION("get_value<uint64> - invalid")
    {
        REQUIRE(0 == config.get_value<uint64>(GG_TEXT("section/uint64_invalid")));
    }
}

//==============================================================================
}
//==============================================================================
