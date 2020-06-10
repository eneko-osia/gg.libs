#ifndef _gg_app_data_base_h_
#define _gg_app_data_base_h_

#include "gg/core/pattern/non_copyable.h"
#include "gg/core/string/type/string_dynamic.h"
#include "gg/core/string/type/string_ref.h"

namespace gg::app
{
    class data_base : public non_copyable
    {
    public:

        // type definitions

        typedef array_dynamic<string_dynamic> argument_container;

        // methods

        void add_argument(string_ref const & argument) noexcept
        {
            m_arguments.emplace_back(argument);
        }

        // accessors

        argument_container const & get_arguments(void) const noexcept
        {
            return m_arguments;
        }

    protected:

        // constructors

        data_base(void) noexcept = default;
        ~data_base(void) noexcept = default;

    private:

        // attributes

        argument_container m_arguments;
    };
}

#endif // _gg_app_data_base_h_
