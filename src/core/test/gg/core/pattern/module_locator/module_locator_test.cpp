#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/module_locator/module_locator.h"

//==============================================================================
namespace gg::module_locator_test
{
//==============================================================================

class mock_module
{
};

//==============================================================================

TEST_CASE("module_locator", "[gg.module_locator]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(module_locator) == sizeof(hash_map<uint32, void *>));
    }

    SECTION("constructible")
    {
        REQUIRE(!type::is_constructible<module_locator>::value);
        REQUIRE(!type::no_constructor<module_locator>::value);
    }

    SECTION("destructible")
    {
        REQUIRE(!type::is_destructible<module_locator>::value);
        REQUIRE(!type::no_destructor<module_locator>::value);
    }

    SECTION("copyable")
    {
        REQUIRE(!type::is_copyable<module_locator>::value);
        REQUIRE(!type::no_copy_constructor<module_locator>::value);
    }

    SECTION("assignable")
    {
        REQUIRE(!type::is_assignable<module_locator>::value);
    }

    SECTION("comparable")
    {
        REQUIRE(type::no_equality_operator<module_locator>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<module_locator>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<module_locator>::value);
    }
}

TEST_CASE("module_locator.publish", "[gg.module_locator]")
{
    SECTION("publish")
    {
        module_locator::create();
        mock_module * module = memory::new_object<mock_module>();

        module_locator & locator = module_locator::get_instance();
        REQUIRE(!locator.has(1));

        locator.publish(1, module);
        REQUIRE(locator.has(1));

        memory::delete_object(module);
        module_locator::destroy();
    }
}

TEST_CASE("module_locator.unpublish", "[gg.module_locator]")
{
    SECTION("unpublish")
    {
        module_locator::create();
        mock_module * module = memory::new_object<mock_module>();

        module_locator & locator = module_locator::get_instance();
        REQUIRE(!locator.has(1));

        locator.publish(1, module);
        REQUIRE(locator.has(1));

        locator.unpublish(1);
        REQUIRE(!locator.has(1));

        memory::delete_object(module);
        module_locator::destroy();
    }
}

TEST_CASE("module_locator.get", "[gg.module_locator]")
{
    SECTION("get")
    {
        module_locator::create();
        mock_module * module = memory::new_object<mock_module>();

        module_locator & locator = module_locator::get_instance();
        locator.publish(1, module);
        REQUIRE(module == locator.get<mock_module>(1));

        memory::delete_object(module);
        module_locator::destroy();
    }
}

//==============================================================================
}
//==============================================================================
