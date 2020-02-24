#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/identifiable.h"

//==============================================================================
namespace gg::identifiable_test
{
//==============================================================================

class mock_id
{
public:

    // constructors

    mock_id(void) noexcept : m_id (0)
    {
    }

    mock_id(uint32 id) noexcept : m_id(id)
    {
    }

    mock_id(mock_id const & id) noexcept : m_id(id.m_id)
    {
    }

    mock_id(mock_id && id) noexcept : m_id(id.m_id)
    {
        id.m_id = 0;
    }

    // operators

    mock_id & operator=(mock_id const & id) noexcept
    {
        m_id = id.m_id;
        return *this;
    }

    mock_id & operator=(mock_id && id) noexcept
    {
        *this = id;
        id.m_id = 0;
        return *this;
    }

    bool8 operator==(mock_id const & id) const noexcept
    {
        return m_id == id.m_id;
    }

private:

    uint32 m_id;
};

class mock_identifiable : public identifiable<mock_id>
{
public:

    mock_identifiable(void) noexcept
        : identifiable<mock_id>()
    {
    }

    mock_identifiable(mock_id const & id) noexcept
        : identifiable<mock_id>(id)
    {
    }

    mock_identifiable(mock_id && id) noexcept
        : identifiable<mock_id>(type::move(id))
    {
    }

    mock_identifiable(mock_identifiable const & obj) noexcept
        : identifiable<mock_id>(obj)
    {
    }

    mock_identifiable(mock_identifiable && obj) noexcept
        : identifiable<mock_id>(type::move(obj))
    {
    }
};

//==============================================================================

TEST_CASE("identifiable", "[gg.identifiable]")
{
    SECTION("assignable")
    {
        REQUIRE(!type::is_assignable<identifiable<mock_id>>::value);
    }

    SECTION("constructor")
    {
        REQUIRE(!type::is_constructible<identifiable<mock_id>>::value);
        REQUIRE(!type::has_trivial_constructor<identifiable<mock_id>>::value);
    }

    SECTION("copy_constructor")
    {
        REQUIRE(!type::is_copyable<identifiable<mock_id>>::value);
        REQUIRE(!type::has_trivial_copy<identifiable<mock_id>>::value);
    }

    SECTION("destructor")
    {
        REQUIRE(!type::is_destructible<identifiable<mock_id>>::value);
        REQUIRE(!type::no_destructor<identifiable<mock_id>>::value);
    }

    SECTION("equality_operator")
    {
        REQUIRE(type::no_equality_operator<identifiable<mock_id>>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<identifiable<mock_id>>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<identifiable<mock_id>>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(
            sizeof(identifiable<mock_id>) ==
            sizeof(identifiable<mock_id>::id_type));
    }
}

TEST_CASE("identifiable.constructor", "[gg.identifiable]")
{
    SECTION("identifiable")
    {
        mock_identifiable identifiable;
        REQUIRE(identifiable.is_id(0));
    }

    SECTION("identifiable(id_type)")
    {
        mock_id id(123);
        mock_identifiable identifiable(id);
        REQUIRE(identifiable.is_id(id));
        REQUIRE(id == 123);
    }

    SECTION("identifiable(rvalue_id_type)")
    {
        mock_id id(123);
        mock_id moved_id(id);
        mock_identifiable identifiable(type::move(moved_id));
        REQUIRE(identifiable.is_id(id));
        REQUIRE(moved_id == 0);
        REQUIRE(id == 123);
    }

    SECTION("identifiable(identifiable)")
    {
        mock_id id(123);
        mock_identifiable copied_identifiable(id);
        mock_identifiable identifiable(copied_identifiable);
        REQUIRE(identifiable.is_id(copied_identifiable.get_id()));
    }

    SECTION("identifiable(rvalue_identifiable)")
    {
        mock_identifiable moved_identifiable(123);
        mock_identifiable copied_identifiable(moved_identifiable);
        mock_identifiable identifiable(type::move(moved_identifiable));
        REQUIRE(identifiable.is_id(copied_identifiable.get_id()));
        REQUIRE(moved_identifiable.is_id(0));
    }
}

TEST_CASE("identifiable.get_id", "[gg.identifiable]")
{
    SECTION("get_id")
    {
        mock_identifiable identifiable(123);
        REQUIRE(identifiable.get_id() == 123);
    }
}

TEST_CASE("identifiable.set_id", "[gg.identifiable]")
{
    SECTION("set_id(id_type)")
    {
        mock_id id(123);
        mock_identifiable identifiable(0);
        identifiable.set_id(id);
        REQUIRE(identifiable.is_id(id));
        REQUIRE(id == 123);
    }

    SECTION("set_id(rvalue_id_type)")
    {
        mock_id id(123);
        mock_id moved_id(id);
        mock_identifiable identifiable(0);
        identifiable.set_id(type::move(moved_id));
        REQUIRE(identifiable.is_id(id));
        REQUIRE(moved_id == 0);
        REQUIRE(id == 123);
    }

    SECTION("set_id<TYPE>(id_type)")
    {
        mock_identifiable identifiable(0);
        identifiable.set_id(123);
        REQUIRE(identifiable.is_id(123));
    }
}

TEST_CASE("identifiable.is_id", "[gg.identifiable]")
{
    SECTION("is_id")
    {
        mock_identifiable identifiable(0);
        identifiable.set_id(123);
        REQUIRE(identifiable.is_id(123));
    }

    SECTION("!is_id")
    {
        mock_identifiable identifiable(0);
        identifiable.set_id(123);
        REQUIRE(!identifiable.is_id(321));
    }
}

//==============================================================================
}
//==============================================================================
