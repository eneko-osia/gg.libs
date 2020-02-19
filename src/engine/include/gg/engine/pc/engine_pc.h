#ifndef _gg_engine_pc_h_
#define _gg_engine_pc_h_

// include files

#include "gg/app/window/iwindow_observer.h"
#include "gg/engine/engine_base.h"

// namespace

namespace gg
{
    // type definitions

    typedef class engine_pc engine_platform;

    // class in charge of define a pc engine

    class engine_pc : public engine_base, public iwindow_observer
    {
    protected:

        // constructors

        engine_pc(data const & data) noexcept;
        virtual ~engine_pc(void) noexcept = default;

    private:

        // engine base override methods

        void finalize(void) noexcept override;
        bool8 init(void) noexcept override;
        int32 run(void) noexcept override;

        // window observer override methods

        void on_close(void) noexcept override;
        void on_quit(void) noexcept override;
        void on_gain_focus(void) noexcept override;
        void on_lost_focus(void) noexcept override;

    private:

        // attributes

        bool8 m_running;
    };
}

#endif // _gg_engine_pc_h_
