#include "gg/core/pattern/module_locator/module_locator.h"

//==============================================================================
namespace gg
{
//==============================================================================

void module_locator::publish(uint32 id, void * module) noexcept
{
	GG_ASSERT(!has(id));
	m_modules.insert(id, module);
}

void module_locator::unpublish(uint32 id) noexcept
{
	GG_ASSERT(has(id));
	m_modules.erase(id);
}

//==============================================================================
}
//==============================================================================
