#ifndef _gg_log_log_manager_h_
#define	_gg_log_log_manager_h_

#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/pattern/singleton/singleton_manual.h"
#include "gg/log/ilog_handler.h"

namespace gg { class string_ref; }

namespace gg::log
{
    class log_manager final : public singleton_manual<log_manager>
    {
    public:

        // methods

        void add_handler(ilog_handler * handler) noexcept;
        void remove_handler(ilog_handler const * handler) noexcept;
        void log(level level, string_ref const & message) noexcept;

        // inquiry

        bool8 has_handler(ilog_handler const * handler) const noexcept;

    protected:

        // constructors

        log_manager(void) noexcept = default;
        ~log_manager(void) noexcept = default;

    private:

        // friendships

        friend class gg::memory;

        // type definitions

        typedef array_dynamic<ilog_handler *> handler_container;

    private:

        // attributes

        handler_container m_handlers;
    };
}

#endif // _gg_log_log_manager_h_
