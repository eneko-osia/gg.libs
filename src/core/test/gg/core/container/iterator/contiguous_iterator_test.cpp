#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/container/iterator/contiguous_iterator.h"

//==============================================================================
namespace gg::contiguous_iterator_test
{
//==============================================================================

struct mock_container
{
    mock_container(void)
    {
        for (int8 i = 0; i < k_max_items; ++i)
        {
            m_data[i] = (i << 1);
        }
    }
    ~mock_container(void) = default;

    static constexpr int8 k_max_items = 16;
    int8 m_data[k_max_items];
};

typedef contiguous_iterator<int8, iterator_type::no_const> iterator;
typedef contiguous_iterator<int8, iterator_type::is_const> const_iterator;

//==============================================================================

TEST_CASE("contiguous_iterator", "[gg.contiguous_iterator]")
{
    SECTION("no_const")
    {
        REQUIRE(!type::is_const<iterator::item_type>::value);

        SECTION("assignable")
        {
            REQUIRE(type::is_assignable<iterator>::value);
        }

        SECTION("constructor")
        {
            REQUIRE(type::is_constructible<iterator>::value);
            REQUIRE(!type::has_trivial_constructor<iterator>::value);
        }

        SECTION("copy_constructor")
        {
            REQUIRE(type::is_copyable<iterator>::value);
            REQUIRE(!type::has_trivial_copy<iterator>::value);
        }

        SECTION("destructor")
        {
            REQUIRE(type::is_destructible<iterator>::value);
            REQUIRE(type::no_destructor<iterator>::value);
        }

        SECTION("equality_operator")
        {
            REQUIRE(!type::no_equality_operator<iterator>::value);
        }

        SECTION("pod")
        {
            REQUIRE(!type::is_pod<iterator>::value);
        }

        SECTION("polymorphic")
        {
            REQUIRE(!type::is_polymorphic<iterator>::value);
        }
    }

    SECTION("is_const")
    {
        REQUIRE(type::is_const<const_iterator::item_type>::value);

        SECTION("assignable")
        {
            REQUIRE(type::is_assignable<const_iterator>::value);
        }

        SECTION("constructor")
        {
            REQUIRE(type::is_constructible<const_iterator>::value);
            REQUIRE(!type::has_trivial_constructor<const_iterator>::value);
        }

        SECTION("copy_constructor")
        {
            REQUIRE(type::is_copyable<const_iterator>::value);
            REQUIRE(type::has_trivial_copy<const_iterator>::value);
        }

        SECTION("destructor")
        {
            REQUIRE(type::is_destructible<const_iterator>::value);
            REQUIRE(type::no_destructor<const_iterator>::value);
        }

        SECTION("equality_operator")
        {
            REQUIRE(!type::no_equality_operator<const_iterator>::value);
        }

        SECTION("pod")
        {
            REQUIRE(!type::is_pod<const_iterator>::value);
        }

        SECTION("polymorphic")
        {
            REQUIRE(!type::is_polymorphic<const_iterator>::value);
        }
    }
}

TEST_CASE("contiguous_iterator.constructor", "[gg.contiguous_iterator]")
{
    SECTION("iterator")
    {
        iterator it;
        REQUIRE(&(*it) == nullptr);
    }

    SECTION("iterator(pointer)")
    {
        iterator::item_type value = 0;
        iterator it(&value);
        REQUIRE(&(*it) == &value);
    }

    SECTION("iterator(iterator)")
    {
        iterator::item_type value = 0;
        iterator it_1(&value);
        iterator it_2(it_1);
        REQUIRE(&(*it_1) == &(*it_2));
    }

    SECTION("const_iterator")
    {
        const_iterator cit;
        REQUIRE(&(*cit) == nullptr);
    }

    SECTION("const_iterator(pointer)")
    {
        const_iterator::item_type value = 0;
        const_iterator cit(&value);
        REQUIRE(&(*cit) == &value);
    }

    SECTION("const_iterator(const_iterator)")
    {
        const_iterator::item_type value = 0;
        const_iterator cit_1(&value);
        const_iterator cit_2(cit_1);
        REQUIRE(&(*cit_1) == &(*cit_2));
    }

    SECTION("const_iterator(iterator)")
    {
        iterator::item_type value = 0;
        iterator it(&value);
        const_iterator cit(it);
        REQUIRE(&(*it) == &(*cit));
    }
}

TEST_CASE("contiguous_iterator.operator-access", "[gg.contiguous_iterator]")
{
    SECTION("iterator[idx]")
    {
        mock_container container;
        iterator it(container.m_data);

        REQUIRE(it[3] == 6);
        REQUIRE(it[6] == 12);
        REQUIRE(it[7] == 14);
    }

    SECTION("const_iterator[idx]")
    {
        mock_container container;
        const_iterator cit(container.m_data);

        REQUIRE(cit[1] == 2);
        REQUIRE(cit[9] == 18);
        REQUIRE(cit[14] == 28);
    }
}

TEST_CASE("contiguous_iterator.operator*", "[gg.contiguous_iterator]")
{
    SECTION("*iterator")
    {
        iterator::item_type value = 123;
        iterator it(&value);
        REQUIRE(*it == value);
    }

    SECTION("*const_iterator")
    {
        const_iterator::item_type value = 123;
        const_iterator cit(&value);
        REQUIRE(*cit == value);
    }
}

TEST_CASE("contiguous_iterator.operator->", "[gg.contiguous_iterator]")
{
    struct mock_item { uint32 m_value; };
    typedef contiguous_iterator<
        mock_item, iterator_type::no_const> mock_item_iterator;
    typedef contiguous_iterator<
        mock_item, iterator_type::is_const> mock_item_const_iterator;

    SECTION("iterator->object")
    {
        mock_item_iterator::item_type item{ 123 };
        mock_item_iterator it(&item);
        REQUIRE(it->m_value == 123);
    }

    SECTION("const_iterator->object")
    {
        mock_item_const_iterator::item_type item{ 123 };
        mock_item_const_iterator cit(&item);
        REQUIRE(cit->m_value == 123);
    }
}

TEST_CASE("contiguous_iterator.operator++", "[gg.contiguous_iterator]")
{
    SECTION("++iterator")
    {
        mock_container container;
        iterator it(container.m_data);

        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 6);
    }

    SECTION("iterator++")
    {
        mock_container container;
        iterator it(container.m_data);

        REQUIRE(*(it++) == 0);
        REQUIRE(*(it++) == 2);
        REQUIRE(*(it++) == 4);
    }

    SECTION("++const_iterator")
    {
        mock_container container;
        const_iterator cit(container.m_data);

        REQUIRE(*(++cit) == 2);
        REQUIRE(*(++cit) == 4);
        REQUIRE(*(++cit) == 6);
    }

    SECTION("const_iterator++")
    {
        mock_container container;
        const_iterator cit(container.m_data);

        REQUIRE(*(cit++) == 0);
        REQUIRE(*(cit++) == 2);
        REQUIRE(*(cit++) == 4);
    }
}

TEST_CASE("contiguous_iterator.operator--", "[gg.contiguous_iterator]")
{
    SECTION("--iterator")
    {
        mock_container container;
        iterator it(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(--it) == 28);
        REQUIRE(*(--it) == 26);
        REQUIRE(*(--it) == 24);
    }

    SECTION("iterator--")
    {
        mock_container container;
        iterator it(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(it--) == 30);
        REQUIRE(*(it--) == 28);
        REQUIRE(*(it--) == 26);
    }

    SECTION("--const_iterator")
    {
        mock_container container;
        const_iterator cit(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(--cit) == 28);
        REQUIRE(*(--cit) == 26);
        REQUIRE(*(--cit) == 24);
    }

    SECTION("const_iterator--")
    {
        mock_container container;
        const_iterator cit(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(cit--) == 30);
        REQUIRE(*(cit--) == 28);
        REQUIRE(*(cit--) == 26);
    }
}

TEST_CASE("contiguous_iterator.operator+", "[gg.contiguous_iterator]")
{
    SECTION("iterator + offset")
    {
        mock_container container;
        iterator it(container.m_data);

        REQUIRE(*(it + 3) == 6);
        REQUIRE(*(it + 6) == 12);
        REQUIRE(*(it + 7) == 14);
    }

    SECTION("const_iterator + offset")
    {
        mock_container container;
        const_iterator cit(container.m_data);

        REQUIRE(*(cit + 1) == 2);
        REQUIRE(*(cit + 9) == 18);
        REQUIRE(*(cit + 14) == 28);
    }
}

TEST_CASE("contiguous_iterator.operator+=", "[gg.contiguous_iterator]")
{
    SECTION("iterator += offset")
    {
        mock_container container;
        iterator it(container.m_data);

        REQUIRE(*(it += 3) == 6);
        REQUIRE(*(it += 3) == 12);
        REQUIRE(*(it += 1) == 14);
    }

    SECTION("const_iterator += offset")
    {
        mock_container container;
        const_iterator cit(container.m_data);

        REQUIRE(*(cit += 1) == 2);
        REQUIRE(*(cit += 8) == 18);
        REQUIRE(*(cit += 5) == 28);
    }
}

TEST_CASE("contiguous_iterator.operator-", "[gg.contiguous_iterator]")
{
    SECTION("iterator - offset")
    {
        mock_container container;
        iterator it(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(it - 3) == 24);
        REQUIRE(*(it - 6) == 18);
        REQUIRE(*(it - 7) == 16);
    }

    SECTION("iterator - iterator")
    {
        mock_container container;
        iterator it_start(container.m_data);
        iterator it_end(container.m_data + mock_container::k_max_items);
        REQUIRE((it_end - it_start) == mock_container::k_max_items);
    }

    SECTION("const_iterator - offset")
    {
        mock_container container;
        const_iterator cit(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(cit - 1) == 28);
        REQUIRE(*(cit - 9) == 12);
        REQUIRE(*(cit - 14) == 2);
    }

    SECTION("const_iterator - const_iterator")
    {
        mock_container container;
        const_iterator cit_start(container.m_data);
        const_iterator cit_end(container.m_data + mock_container::k_max_items);
        REQUIRE((cit_end - cit_start) == mock_container::k_max_items);
    }
}

TEST_CASE("contiguous_iterator.operator-=", "[gg.contiguous_iterator]")
{
    SECTION("iterator -= offset")
    {
        mock_container container;
        iterator it(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(it -= 3) == 24);
        REQUIRE(*(it -= 3) == 18);
        REQUIRE(*(it -= 1) == 16);
    }

    SECTION("const_iterator -= offset")
    {
        mock_container container;
        const_iterator cit(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(cit -= 1) == 28);
        REQUIRE(*(cit -= 8) == 12);
        REQUIRE(*(cit -= 5) == 2);
    }
}

TEST_CASE("contiguous_iterator.operator==", "[gg.contiguous_iterator]")
{
    SECTION("iterator == iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 == it_2);
    }

    SECTION("!(iterator == iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!(it_1 == (++it_2)));
    }

    SECTION("const_iterator == const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 == cit_2);
    }

    SECTION("!(const_iterator == const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!(cit_1 == (++cit_2)));
    }
}

TEST_CASE("contiguous_iterator.operator!=", "[gg.contiguous_iterator]")
{
    SECTION("iterator != iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!(it_1 != it_2));
    }

    SECTION("!(iterator != iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 != (++it_2));
    }

    SECTION("const_iterator != const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!(cit_1 != cit_2));
    }

    SECTION("!(const_iterator != const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 != (++cit_2));
    }
}

TEST_CASE("contiguous_iterator.operator<", "[gg.contiguous_iterator]")
{
    SECTION("iterator < iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 < (++it_2));
    }

    SECTION("!(iterator < iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!(it_1 < it_2));
    }

    SECTION("const_iterator < const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 < (++cit_2));
    }

    SECTION("!(const_iterator < const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!(cit_1 < cit_2));
    }
}

TEST_CASE("contiguous_iterator.operator<=", "[gg.contiguous_iterator]")
{
    SECTION("iterator <= iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 <= it_2);
    }

    SECTION("iterator <= iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 <= (++it_2));
    }

    SECTION("!(iterator <= iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!((++it_1) < it_2));
    }

    SECTION("const_iterator <= const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 <= cit_2);
    }

    SECTION("const_iterator <= const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 <= (++cit_2));
    }

    SECTION("!(const_iterator <= const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!((++cit_1) < cit_2));
    }
}

TEST_CASE("contiguous_iterator.operator>", "[gg.contiguous_iterator]")
{
    SECTION("iterator > iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE((++it_1) > it_2);
    }

    SECTION("!(iterator > iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!(it_1 > it_2));
    }

    SECTION("const_iterator > const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE((++cit_1) > cit_2);
    }

    SECTION("!(const_iterator > const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!(cit_1 > cit_2));
    }
}

TEST_CASE("contiguous_iterator.operator>=", "[gg.contiguous_iterator]")
{
    SECTION("iterator >= iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 >= it_2);
    }

    SECTION("iterator >= iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE((++it_1) >= it_2);
    }

    SECTION("!(iterator >= iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!(it_1 > (++it_2)));
    }

    SECTION("const_iterator >= const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 >= cit_2);
    }

    SECTION("const_iterator >= const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE((++cit_1) >= cit_2);
    }

    SECTION("!(const_iterator >= const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!(cit_1 > (++cit_2)));
    }
}

//==============================================================================
}
//==============================================================================
