#ifndef _gg_non_movable_h_
#define	_gg_non_movable_h_

// namespace

namespace gg
{
    // class in charge of define a non movable object

    class non_movable
    {
    protected:

        // constructors

        non_movable(void) = default;
        ~non_movable(void) = default;

    private:

        // constructors

        non_movable(non_movable &&) = delete;

        // operators

        non_movable const & operator=(non_movable &&) = delete;
    };
}

#endif // _gg_non_movable_h_
