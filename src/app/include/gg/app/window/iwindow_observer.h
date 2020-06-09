#ifndef _gg_app_iwindow_observer_h_
#define _gg_app_iwindow_observer_h_

namespace gg::app
{
    class iwindow_observer
    {
    public:

        // virtual methods

        virtual void on_close(void) noexcept = 0;
        virtual void on_gain_focus(void) noexcept = 0;
        virtual void on_lost_focus(void) noexcept = 0;
    };
}

#endif // _gg_app_iwindow_observer_h_
