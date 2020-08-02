#ifndef _gg_log_ilog_handler_h_
#define	_gg_log_ilog_handler_h_

#include "gg/log/logger_defs.h"

namespace gg { class string_ref; }

namespace gg::log
{
    class ilog_handler
    {
    public:

        // virtual methods

        virtual void log(level level, string_ref const & message) noexcept = 0;
    };
}

#endif // _gg_log_ilog_handler_h_
