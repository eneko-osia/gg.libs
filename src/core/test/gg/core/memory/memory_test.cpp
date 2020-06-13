#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/memory/memory.h"
#include "gg/core/memory/memory_defs.h"

//==============================================================================
namespace gg::memory_test
{
//==============================================================================

TEST_CASE("memory", "[gg.memory]")
{
#if defined(GG_DEBUG)
    SECTION("memory owner mode descriptors")
    {
        REQUIRE(
            GG_TEXT("is_not_owner") ==
            memory_owner_mode_descriptors[
                enums::cast(memory_owner_mode::is_not_owner)]);

        REQUIRE(
            GG_TEXT("is_owner") ==
            memory_owner_mode_descriptors[
                enums::cast(memory_owner_mode::is_owner)]);
    }
#endif
}

TEST_CASE("memory.compare", "[gg.memory]")
{
    SECTION("compare")
    {
        static uint32 constexpr k_max_num = 8;
        uint32 lhs[k_max_num];
        uint32 rhs[k_max_num];
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            lhs[i] = i;
            rhs[i] = i;
        }
        REQUIRE(memory::compare(lhs, rhs, k_max_num) == 0);
    }

    SECTION("!compare")
    {
        static uint32 constexpr k_max_num = 8;
        uint32 lhs[k_max_num];
        uint32 rhs[k_max_num];
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            lhs[i] = i;
            rhs[i] = k_max_num + i;
        }
        REQUIRE(memory::compare(lhs, rhs, k_max_num) != 0);
    }
}

TEST_CASE("memory.copy", "[gg.memory]")
{
    SECTION("copy")
    {
        static uint32 constexpr k_max_num = 8;
        uint32 lhs[k_max_num];
        uint32 rhs[k_max_num];
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            lhs[i] = i;
            rhs[i] = k_max_num + i;
            REQUIRE(lhs[i] != rhs[i]);
        }
        memory::copy(rhs, lhs, k_max_num);
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            REQUIRE(lhs[i] == rhs[i]);
        }
    }
}

TEST_CASE("memory.move", "[gg.memory]")
{
    SECTION("move")
    {
        static uint32 constexpr k_max_num = 8;
        uint32 lhs[k_max_num];
        uint32 rhs[k_max_num];
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            lhs[i] = i;
            rhs[i] = k_max_num + i;
            REQUIRE(lhs[i] != rhs[i]);
        }
        memory::move(rhs, lhs, k_max_num);
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            REQUIRE(lhs[i] == rhs[i]);
        }
    }
}

TEST_CASE("memory.zero", "[gg.memory]")
{
    SECTION("zero")
    {
        static uint32 constexpr k_max_num = 8;
        uint32 ptr[k_max_num];
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            ptr[i] = i;
            REQUIRE(ptr[i] == i);
        }
        memory::zero(ptr, k_max_num);
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            REQUIRE(ptr[i] == 0);
        }
    }
}

TEST_CASE("memory.allocate", "[gg.memory]")
{
    SECTION("allocate")
    {
        void * ptr = memory::allocate(16);
        REQUIRE(ptr);
        memory::deallocate(ptr);
    }
}

TEST_CASE("memory.deallocate", "[gg.memory]")
{
    SECTION("deallocate")
    {
        void * ptr = nullptr;
        memory::deallocate(ptr);
    }
}

TEST_CASE("memory.reallocate", "[gg.memory]")
{
    SECTION("reallocate")
    {
        void * ptr = nullptr;
        ptr = memory::reallocate(ptr, 16);
        REQUIRE(ptr);
        memory::deallocate(ptr);
    }
}


//==============================================================================
}
//==============================================================================
