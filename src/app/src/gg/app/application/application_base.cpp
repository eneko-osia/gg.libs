#include "gg/app/application/application_base.h"

//==============================================================================
namespace gg
{
//==============================================================================

application_base::application_base(data const & data) noexcept
    : m_data(data)
{
}

//==============================================================================

int32 application_base::main(data const & data) noexcept
{
    create(data);
    int32 result = get_instance().main();
    destroy();
    return result;
}

//==============================================================================
}
//==============================================================================
