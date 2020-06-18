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

    mock_nameable(void) noexcept = default;
    mock_nameable(mock_nameable const & obj) noexcept = default;
    mock_nameable(mock_nameable && obj) noexcept = default;

    mock_nameable(string_ref const & name) noexcept
        : nameable<string_ref>(name)
    {
    }

    mock_nameable(string_ref && name) noexcept
        : nameable<string_ref>(type::move(name))
    {
    }
};

class trivial_mock_nameable : public nameable<char8 const *>
{
public:

    trivial_mock_nameable(void) noexcept = default;
    trivial_mock_nameable(trivial_mock_nameable const & obj) noexcept = default;
    trivial_mock_nameable(trivial_mock_nameable && obj) noexcept = default;
};

//==============================================================================

TEST_CASE("nameable", "[gg.nameable]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_assignable<nameable<string_ref>>::value);
        REQUIRE(!type::has_trivial_assign<nameable<string_ref>>::value);

        REQUIRE(!type::is_assignable<mock_nameable>::value);
        REQUIRE(!type::has_trivial_assign<mock_nameable>::value);

        REQUIRE(!type::is_assignable<nameable<char8 const *>>::value);
        REQUIRE(!type::has_trivial_assign<nameable<char8 const *>>::value);

        REQUIRE(!type::is_assignable<trivial_mock_nameable>::value);
        REQUIRE(!type::has_trivial_assign<trivial_mock_nameable>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<nameable<string_ref>>::value);
        REQUIRE(!type::has_trivial_constructor<nameable<string_ref>>::value);

        REQUIRE(type::is_constructible<mock_nameable>::value);
        REQUIRE(!type::has_trivial_constructor<mock_nameable>::value);

        REQUIRE(!type::is_constructible<nameable<char8 const *>>::value);
        REQUIRE(!type::has_trivial_constructor<nameable<char8 const *>>::value);

        REQUIRE(type::is_constructible<trivial_mock_nameable>::value);
        REQUIRE(type::has_trivial_constructor<trivial_mock_nameable>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copyable<nameable<string_ref>>::value);
        REQUIRE(!type::has_trivial_copy<nameable<string_ref>>::value);

        REQUIRE(type::is_copyable<mock_nameable>::value);
        REQUIRE(!type::has_trivial_copy<mock_nameable>::value);

        REQUIRE(!type::is_copyable<nameable<char8 const *>>::value);
        REQUIRE(!type::has_trivial_copy<nameable<char8 const *>>::value);

        REQUIRE(type::is_copyable<trivial_mock_nameable>::value);
        REQUIRE(type::has_trivial_copy<trivial_mock_nameable>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(!type::is_destructible<nameable<string_ref>>::value);
        REQUIRE(!type::has_trivial_destructor<nameable<string_ref>>::value);

        REQUIRE(type::is_destructible<mock_nameable>::value);
        REQUIRE(type::has_trivial_destructor<mock_nameable>::value);

        REQUIRE(!type::is_destructible<nameable<char8 const *>>::value);
        REQUIRE(!type::has_trivial_destructor<nameable<char8 const *>>::value);

        REQUIRE(type::is_destructible<trivial_mock_nameable>::value);
        REQUIRE(type::has_trivial_destructor<trivial_mock_nameable>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<nameable<string_ref>>::value);
        REQUIRE(!type::has_equality<mock_nameable>::value);
        REQUIRE(!type::has_equality<nameable<char8 const *>>::value);
        REQUIRE(!type::has_equality<trivial_mock_nameable>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<nameable<string_ref>>::value);
        REQUIRE(!type::is_pod<mock_nameable>::value);
#if defined(GG_LINUX)
        REQUIRE(type::is_pod<nameable<char8 const *>>::value);
        REQUIRE(type::is_pod<trivial_mock_nameable>::value);
#elif defined(GG_WINDOWS)
        REQUIRE(!type::is_pod<nameable<char8 const *>>::value);
        REQUIRE(!type::is_pod<trivial_mock_nameable>::value);
#endif
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<nameable<string_ref>>::value);
        REQUIRE(!type::is_polymorphic<mock_nameable>::value);
        REQUIRE(!type::is_polymorphic<nameable<char8 const *>>::value);
        REQUIRE(!type::is_polymorphic<trivial_mock_nameable>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(
            sizeof(nameable<string_ref>) ==
            sizeof(nameable<string_ref>::name_type));
        REQUIRE(
            sizeof(mock_nameable) ==
            sizeof(mock_nameable::name_type));
        REQUIRE(
            sizeof(nameable<uint32>) ==
            sizeof(nameable<uint32>::name_type));
        REQUIRE(
            sizeof(trivial_mock_nameable) ==
            sizeof(trivial_mock_nameable::name_type));
    }
}

TEST_CASE("nameable.constructor", "[gg.nameable]")
{
    SECTION("nameable")
    {
        mock_nameable nameable;
        REQUIRE(nameable.is_named(string::empty));
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
        mock_nameable nameable;
        nameable.set_name(name);
        REQUIRE(nameable.is_named(name));
        REQUIRE(name == "123");
    }

    SECTION("set_name(rvalue_name_type)")
    {
        string_ref name("123");
        string_ref moved_name(name);
        mock_nameable nameable;
        nameable.set_name(type::move(moved_name));
        REQUIRE(nameable.is_named(name));
        REQUIRE(moved_name.is_empty());
        REQUIRE(name == "123");
    }

    SECTION("set_name<TYPE>(name_type)")
    {
        string_static<> referenced_string("123");
        mock_nameable nameable;
        nameable.set_name(referenced_string);
        REQUIRE(nameable.is_named("123"));
    }
}

TEST_CASE("nameable.is_named", "[gg.nameable]")
{
    SECTION("is_named")
    {
        mock_nameable nameable;
        nameable.set_name("123");
        REQUIRE(nameable.is_named("123"));
    }

    SECTION("!is_named")
    {
        mock_nameable nameable;
        nameable.set_name("123");
        REQUIRE(!nameable.is_named("321"));
    }
}

//==============================================================================
}
//==============================================================================
