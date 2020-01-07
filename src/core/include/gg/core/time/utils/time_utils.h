#ifndef _gg_time_utils_h_
#define _gg_time_utils_h_

// include files

#include "gg/core/time/type/nanosecond.h"
#include <chrono>

// namespace

namespace gg
{
    // class in charge of define an time utilities

    class time_utils final
    {
    public:

        // methods

        template <typename TIME_TYPE>
        static TIME_TYPE clock_now(void)
        {
            return now<TIME_TYPE, std::chrono::high_resolution_clock>();
        }

        template <typename TIME_TYPE>
        static TIME_TYPE system_now(void)
        {
            return now<TIME_TYPE, std::chrono::system_clock>();
        }

    private:

        // methods

        template <typename TIME_TYPE, typename TIME_GENERATOR>
        static TIME_TYPE now(void)
        {
            auto current_time = TIME_GENERATOR::now();
            std::chrono::nanoseconds time_since_epoch =
                std::chrono::duration_cast<
                    std::chrono::nanoseconds>(current_time.time_since_epoch());
            return TIME_TYPE(nanosecond(time_since_epoch.count()));
        }
    };
}

#endif // _gg_time_utils_h_
