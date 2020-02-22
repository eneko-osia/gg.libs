#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/singleton/singleton_static.h"

//==============================================================================
namespace gg::singleton_static_test
{
//==============================================================================

class mock_singleton : public singleton_static<mock_singleton>
{
private:

    friend class singleton_static<mock_singleton>;
    mock_singleton(void) = default;
    ~mock_singleton(void) = default;
};

//==============================================================================

TEST_CASE("singleton_static", "[gg.singleton_static]")
{
    SECTION("pod")
    {
#if defined(GG_LINUX)
        REQUIRE(type::is_pod<singleton_static<uint32>>::value);
#elif defined(GG_WINDOWS)
        REQUIRE(!type::is_pod<singleton_static<uint32>>::value);
#endif
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<singleton_static<uint32>>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(sizeof(singleton_static<uint32>) == 1);
    }
}

TEST_CASE("singleton_static.get_instance", "[gg.singleton_static]")
{
    SECTION("get_instance")
    {
        mock_singleton& instance = mock_singleton::get_instance();
        REQUIRE(&instance == &mock_singleton::get_instance());
    }
}

//==============================================================================
}
//==============================================================================
