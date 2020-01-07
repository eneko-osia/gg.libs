#ifndef _gg_data_base_h_
#define _gg_data_base_h_

// include files

#include "gg/core/pattern/non_copyable.h"
#include "gg/core/string/type/string_dynamic.h"
#include "gg/core/string/type/string_ref.h"

// namespace

namespace gg
{
    // class in charge of define an application base data

    class data_base : public non_copyable
    {
    public:

        // type definitions

        typedef array_dynamic<string_dynamic> argument_container;

        // methods

        void add_argument(string_ref const & argument)
        {
            m_arguments.emplace_back(argument);
        }

        argument_container const & get_arguments(void) const
        {
            return m_arguments;
        }

    protected:

        // constructors

        data_base(void) = default;
        ~data_base(void) = default;

    private:

        // attributes

        argument_container m_arguments;
    };
}

#endif // _gg_data_base_h_
