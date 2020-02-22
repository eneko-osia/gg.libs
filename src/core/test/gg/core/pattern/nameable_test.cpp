#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/nameable.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/core/string/type/string_static.h"

//==============================================================================
namespace gg::nameable_test
{
//==============================================================================

class mock_nameable : public nameable<string_ref>
{
public:

    mock_nameable(void) noexcept
        : nameable<string_ref>()
    {
    }

    mock_nameable(string_ref const & name) noexcept
        : nameable<string_ref>(name)
    {
    }

    mock_nameable(string_ref && name) noexcept
        : nameable<string_ref>(type::move(name))
    {
    }

    mock_nameable(mock_nameable const & obj) noexcept
        : nameable<string_ref>(obj)
    {
    }

    mock_nameable(mock_nameable && obj) noexcept
        : nameable<string_ref>(type::move(obj))
    {
    }
};

//==============================================================================

TEST_CASE("nameable", "[gg.nameable]")
{
    SECTION("assignable")
    {
        REQUIRE(!type::is_assignable<mock_nameable>::value);
    }

    SECTION("constructor")
    {
        REQUIRE(type::is_constructible<mock_nameable>::value);
        REQUIRE(!type::no_constructor<mock_nameable>::value);
    }

    SECTION("copy_constructor")
    {
        REQUIRE(type::is_copyable<mock_nameable>::value);
        REQUIRE(!type::no_copy_constructor<mock_nameable>::value);
    }

    SECTION("destructor")
    {
        REQUIRE(type::is_destructible<mock_nameable>::value);
        REQUIRE(!type::no_destructor<mock_nameable>::value);
    }

    SECTION("equality_operator")
    {
        REQUIRE(type::no_equality_operator<mock_nameable>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<mock_nameable>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<mock_nameable>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(sizeof(mock_nameable) == sizeof(mock_nameable::name_type));
    }
}

TEST_CASE("nameable.constructor", "[gg.nameable]")
{
    SECTION("nameable")
    {
        mock_nameable nameable;
        REQUIRE(nameable.is_named(""));
    }

    SECTION("nameable(name_type)")
    {
        string_ref name("123");
        mock_nameable nameable(name);
        REQUIRE(nameable.is_named(name));
        REQUIRE(name == "123");
    }

    SECTION("nameable(rvalue_name_type)")
    {
        string_ref name("123");
        string_ref moved_name(name);
        mock_nameable nameable(type::move(moved_name));
        REQUIRE(nameable.is_named(name));
        REQUIRE(moved_name.is_empty());
        REQUIRE(name == "123");
    }

    SECTION("nameable(nameable)")
    {
        string_ref name("123");
        mock_nameable copied_nameable(name);
        mock_nameable nameable(copied_nameable);
        REQUIRE(nameable.is_named(copied_nameable.get_name()));
    }

    SECTION("nameable(rvalue_nameable)")
    {
        mock_nameable moved_nameable("123");
        mock_nameable copied_nameable(moved_nameable);
        mock_nameable nameable(type::move(moved_nameable));
        REQUIRE(nameable.is_named(copied_nameable.get_name()));
        REQUIRE(moved_nameable.get_name().is_empty());
    }
}

TEST_CASE("nameable.get_name", "[gg.nameable]")
{
    SECTION("get_name")
    {
        mock_nameable nameable("123");
        REQUIRE(nameable.get_name() == "123");
    }
}

TEST_CASE("nameable.set_name", "[gg.nameable]")
{
    SECTION("set_name(name_type)")
    {
        string_ref name("123");
        mock_nameable nameable("");
        nameable.set_name(name);
        REQUIRE(nameable.is_named(name));
        REQUIRE(name == "123");
    }

    SECTION("set_name(rvalue_name_type)")
    {
        string_ref name("123");
        string_ref moved_name(name);
        mock_nameable nameable("");
        nameable.set_name(type::move(moved_name));
        REQUIRE(nameable.is_named(name));
        REQUIRE(moved_name.is_empty());
        REQUIRE(name == "123");
    }

    SECTION("set_name<TYPE>(name_type)")
    {
        string_static<> referenced_string("123");
        mock_nameable nameable("");
        nameable.set_name(referenced_string);
        REQUIRE(nameable.is_named("123"));
    }
}

TEST_CASE("nameable.is_named", "[gg.nameable]")
{
    SECTION("is_named")
    {
        mock_nameable nameable("");
        nameable.set_name("123");
        REQUIRE(nameable.is_named("123"));
    }

    SECTION("!is_named")
    {
        mock_nameable nameable("");
        nameable.set_name("123");
        REQUIRE_FALSE(nameable.is_named("321"));
    }
}

//==============================================================================
}
//==============================================================================
