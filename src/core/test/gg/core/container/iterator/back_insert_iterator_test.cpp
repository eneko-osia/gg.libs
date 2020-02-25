#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/container/iterator/back_insert_iterator.h"
#include "gg/core/memory/memory.h"

//==============================================================================
namespace gg::back_insert_iterator_test
{
//==============================================================================

struct mock_container
{
    typedef int8 item_type;

    mock_container(void) : m_index(0)
    {
        memory::zero(m_data, k_max_items);
    }

    void push_back(int8 item) noexcept
    {
        m_data[m_index++] = item;
    }

    static constexpr int8 k_max_items = 16;
    int8 m_data[k_max_items];
    int8 m_index;
};

typedef back_insert_iterator<mock_container> mock_back_insert_iterator;

//==============================================================================

TEST_CASE("back_insert_iterator", "[gg.back_insert_iterator]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_assignable<mock_back_insert_iterator>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<mock_back_insert_iterator>::value);
        REQUIRE(!type::has_trivial_constructor<mock_back_insert_iterator>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copyable<mock_back_insert_iterator>::value);
        REQUIRE(type::has_trivial_copy<mock_back_insert_iterator>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<mock_back_insert_iterator>::value);
        REQUIRE(type::has_trivial_destructor<mock_back_insert_iterator>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<mock_back_insert_iterator>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<mock_back_insert_iterator>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<mock_back_insert_iterator>::value);
    }
}

TEST_CASE("back_insert_iterator.operator=", "[gg.back_insert_iterator]")
{
    SECTION("back_insert_iterator = item")
    {
        mock_container container;
        mock_back_insert_iterator inserter = back_inserter(container);

        *(inserter++) = 2;
        *(inserter++) = 4;
        *(++inserter) = 7;

        REQUIRE(container.m_data[0] == 2);
        REQUIRE(container.m_data[1] == 4);
        REQUIRE(container.m_data[2] == 7);
    }
}

//==============================================================================
}
//==============================================================================
