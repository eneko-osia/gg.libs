//==============================================================================

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
        REQUIRE(type::is_copy_assignable<configuration>::value);
        REQUIRE(!type::is_trivially_assignable<configuration>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<configuration>::value);
        REQUIRE(!type::is_trivially_constructible<configuration>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<configuration>::value);
        REQUIRE(!type::is_trivially_copy_constructible<configuration>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<configuration>::value);
        REQUIRE(!type::is_trivially_destructible<configuration>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<configuration>::value);
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
        "float32 = 32.23\n"
        "float64 = 64.46\n"
        "string = this is a string\n";
    memory_istream stream(memory_buffer_ref((byte *) data.c_str(), data.size()));
    configuration config;
    REQUIRE(config.load(stream));

    SECTION("get_value<bool8>")
    {
        REQUIRE(config.get_value<bool8>(GG_TEXT("section/bool8"), false));
    }

    SECTION("get_value<bool8> - invalid")
    {
        REQUIRE(!config.get_value<bool8>(GG_TEXT("section/bool8_invalid"), false));
    }

    SECTION("get_value<int8>")
    {
        REQUIRE(-8 == config.get_value<int8>(GG_TEXT("section/int8"), 0));
    }

    SECTION("get_value<int8> - invalid")
    {
        REQUIRE(0 == config.get_value<int8>(GG_TEXT("section/int8_invalid"), 0));
    }

    SECTION("get_value<uint8>")
    {
        REQUIRE(8 == config.get_value<uint8>(GG_TEXT("section/uint8"), 0));
    }

    SECTION("get_value<uint8> - invalid")
    {
        REQUIRE(0 == config.get_value<uint8>(GG_TEXT("section/uint8_invalid"), 0));
    }

    SECTION("get_value<int16>")
    {
        REQUIRE(-16 == config.get_value<int16>(GG_TEXT("section/int16"), 0));
    }

    SECTION("get_value<int16> - invalid")
    {
        REQUIRE(0 == config.get_value<int16>(GG_TEXT("section/int16_invalid"), 0));
    }

    SECTION("get_value<uint16>")
    {
        REQUIRE(16 == config.get_value<uint16>(GG_TEXT("section/uint16"), 0));
    }

    SECTION("get_value<uint16> - invalid")
    {
        REQUIRE(0 == config.get_value<uint16>(GG_TEXT("section/uint16_invalid"), 0));
    }

    SECTION("get_value<int32>")
    {
        REQUIRE(-32 == config.get_value<int32>(GG_TEXT("section/int32"), 0));
    }

    SECTION("get_value<int32> - invalid")
    {
        REQUIRE(0 == config.get_value<int32>(GG_TEXT("section/int32_invalid"), 0));
    }

    SECTION("get_value<uint32>")
    {
        REQUIRE(32 == config.get_value<uint32>(GG_TEXT("section/uint32"), 0));
    }

    SECTION("get_value<uint32> - invalid")
    {
        REQUIRE(0 == config.get_value<uint32>(GG_TEXT("section/uint32_invalid"), 0));
    }

    SECTION("get_value<int64>")
    {
        REQUIRE(-64 == config.get_value<int64>(GG_TEXT("section/int64"), 0));
    }

    SECTION("get_value<int64> - invalid")
    {
        REQUIRE(0 == config.get_value<int64>(GG_TEXT("section/int64_invalid"), 0));
    }

    SECTION("get_value<uint64>")
    {
        REQUIRE(64 == config.get_value<uint64>(GG_TEXT("section/uint64"), 0));
    }

    SECTION("get_value<uint64> - invalid")
    {
        REQUIRE(0 == config.get_value<uint64>(GG_TEXT("section/uint64_invalid"), 0));
    }

    SECTION("get_value<float32>")
    {
        REQUIRE(32.23f == config.get_value<float32>(GG_TEXT("section/float32"), 0.0f));
    }

    SECTION("get_value<float32> - invalid")
    {
        REQUIRE(0.0f == config.get_value<float32>(GG_TEXT("section/float32_invalid"), 0.0f));
    }

    SECTION("get_value<float64>")
    {
        REQUIRE(64.46 == config.get_value<float64>(GG_TEXT("section/float64"), 0.0f));
    }

    SECTION("get_value<float64> - invalid")
    {
        REQUIRE(0.0 == config.get_value<float64>(GG_TEXT("section/float64_invalid"), 0.0f));
    }

    SECTION("get_value<string>")
    {
        REQUIRE("this is a string" == config.get_value<string_ref>(GG_TEXT("section/string"), GG_TEXT("")));
    }

    SECTION("get_value<string> - invalid")
    {
        REQUIRE("" == config.get_value<string_ref>(GG_TEXT("section/string_invalid"), GG_TEXT("")));
    }
}

TEST_CASE("configuration.set_value", "[gg.configuration]")
{
    configuration config;

    SECTION("set_value<bool8>")
    {
        REQUIRE(!config.get_value<bool8>(GG_TEXT("section/bool8"), false));
        config.set_value<bool8>(GG_TEXT("section/bool8"), true);
        REQUIRE(config.get_value<bool8>(GG_TEXT("section/bool8"), false));
    }

    SECTION("set_value<int8>")
    {
        REQUIRE(0 == config.get_value<int8>(GG_TEXT("section/int8"), 0));
        config.set_value<int8>(GG_TEXT("section/int8"), -8);
        REQUIRE(-8 == config.get_value<int8>(GG_TEXT("section/int8"), 0));
    }

    SECTION("set_value<uint8>")
    {
        REQUIRE(0 == config.get_value<uint8>(GG_TEXT("section/uint8"), 0));
        config.set_value<uint8>(GG_TEXT("section/uint8"), 8);
        REQUIRE(8 == config.get_value<uint8>(GG_TEXT("section/uint8"), 0));
    }

    SECTION("set_value<int16>")
    {
        REQUIRE(0 == config.get_value<int16>(GG_TEXT("section/int16"), 0));
        config.set_value<int16>(GG_TEXT("section/int16"), -16);
        REQUIRE(-16 == config.get_value<int16>(GG_TEXT("section/int16"), 0));
    }

    SECTION("set_value<uint16>")
    {
        REQUIRE(0 == config.get_value<uint16>(GG_TEXT("section/uint16"), 0));
        config.set_value<uint16>(GG_TEXT("section/uint16"), 16);
        REQUIRE(16 == config.get_value<uint16>(GG_TEXT("section/uint16"), 0));
    }

    SECTION("set_value<int32>")
    {
        REQUIRE(0 == config.get_value<int32>(GG_TEXT("section/int32"), 0));
        config.set_value<int32>(GG_TEXT("section/int32"), -32);
        REQUIRE(-32 == config.get_value<int32>(GG_TEXT("section/int32"), 0));
    }

    SECTION("set_value<uint32>")
    {
        REQUIRE(0 == config.get_value<uint32>(GG_TEXT("section/uint32"), 0));
        config.set_value<uint32>(GG_TEXT("section/uint32"), 32);
        REQUIRE(32 == config.get_value<uint32>(GG_TEXT("section/uint32"), 0));
    }

    SECTION("set_value<int64>")
    {
        REQUIRE(0 == config.get_value<int64>(GG_TEXT("section/int64"), 0));
        config.set_value<int64>(GG_TEXT("section/int64"), -64);
        REQUIRE(-64 == config.get_value<int64>(GG_TEXT("section/int64"), 0));
    }

    SECTION("set_value<uint64>")
    {
        REQUIRE(0 == config.get_value<uint64>(GG_TEXT("section/uint64"), 0));
        config.set_value<uint64>(GG_TEXT("section/uint64"), 64);
        REQUIRE(64 == config.get_value<uint64>(GG_TEXT("section/uint64"), 0));
    }

    SECTION("set_value<float32>")
    {
        REQUIRE(0.0f == config.get_value<float32>(GG_TEXT("section/float32"), 0.0f));
        config.set_value<float32>(GG_TEXT("section/float32"), 32.23f);
        REQUIRE(32.23f == config.get_value<float32>(GG_TEXT("section/float32"), 0.0f));
    }

    SECTION("set_value<float64>")
    {
        REQUIRE(0.0 == config.get_value<float64>(GG_TEXT("section/float64"), 0.0));
        config.set_value<float64>(GG_TEXT("section/float64"), 64.46);
        REQUIRE(64.46 == config.get_value<float64>(GG_TEXT("section/float64"), 0.0));
    }

    SECTION("set_value<string>")
    {
        REQUIRE(GG_TEXT("") == config.get_value<string_ref>(GG_TEXT("section/string"), GG_TEXT("")));
        config.set_value<string_ref>(GG_TEXT("section/string"), GG_TEXT("this is a string"));
        REQUIRE(GG_TEXT("this is a string") == config.get_value<string_ref>(GG_TEXT("section/string"), GG_TEXT("")));
    }
}

//==============================================================================
}
//==============================================================================
