#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/singleton/singleton_manual.h"

//==============================================================================
namespace gg::singleton_manual_test
{
//==============================================================================

class mock_singleton : public singleton_manual<mock_singleton>
{
protected:

    friend class gg::memory;
    mock_singleton(void) = default;
    virtual ~mock_singleton(void) = default;
};

class mock_singleton_derived : public mock_singleton
{
private:

    friend class gg::memory;
    mock_singleton_derived(void) = default;
    ~mock_singleton_derived(void) = default;
};

//==============================================================================

TEST_CASE("singleton_manual", "[gg.singleton_manual]")
{
    SECTION("pod")
    {
        REQUIRE_FALSE(type::is_pod<singleton_manual<uint32>>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE_FALSE(type::is_polymorphic<singleton_manual<uint32>>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(sizeof(singleton_manual<uint32>) == 1);
    }
}

TEST_CASE("singleton_manual.create", "[gg.singleton_manual]")
{
    SECTION("create")
    {
        REQUIRE_FALSE(mock_singleton::is_available());
        mock_singleton::create();
        REQUIRE(mock_singleton::is_available());
        mock_singleton::destroy();
        REQUIRE_FALSE(mock_singleton::is_available());
    }

    SECTION("create<TYPE>")
    {
        REQUIRE_FALSE(mock_singleton::is_available());
        mock_singleton::create<mock_singleton_derived>();
        REQUIRE(mock_singleton::is_available());
        mock_singleton::destroy();
        REQUIRE_FALSE(mock_singleton::is_available());
    }
}

TEST_CASE("singleton_manual.get_instance", "[gg.singleton_manual]")
{
    SECTION("get_instance")
    {
        mock_singleton::create();
        mock_singleton& instance = mock_singleton::get_instance();
        REQUIRE(&instance == &mock_singleton::get_instance());
        mock_singleton::destroy();
    }

    SECTION("get_instance<TYPE>")
    {
        mock_singleton::create<mock_singleton_derived>();
        mock_singleton_derived& instance =
            mock_singleton::get_instance<mock_singleton_derived>();
        REQUIRE(
            &instance == &mock_singleton::get_instance<mock_singleton_derived>());
        mock_singleton::destroy();
    }
}

//==============================================================================
}
//==============================================================================
