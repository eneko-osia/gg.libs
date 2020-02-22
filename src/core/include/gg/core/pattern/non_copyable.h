#ifndef _gg_non_copyable_h_
#define	_gg_non_copyable_h_

// namespace

namespace gg
{
    // class in charge of define a non copyable object

    class non_copyable
    {
    protected:

        // constructors

        non_copyable(void) noexcept = default;
        ~non_copyable(void) noexcept = default;

    private:

        // constructors

        non_copyable(non_copyable const &) noexcept = delete;

        // operators

        non_copyable const & operator=(non_copyable const &) noexcept = delete;
    };
}

#endif // _gg_non_copyable_h_
