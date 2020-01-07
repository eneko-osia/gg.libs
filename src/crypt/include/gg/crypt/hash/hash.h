#ifndef _gg_hash_h_
#define _gg_hash_h_

// include files

#include "gg/core/type/type.h"

// namespace

namespace gg
{
    // forward declarations

    class string_ref;

    // namespace in charge of define hash utilities

    namespace hash
    {
        // namespace in charge of define fnv1 hash utilities

        namespace fnv1
        {
            // methods

            uint32 generate(string_ref const & string);
        }

        // namespace in charge of define fnv1a hash utilities

        namespace fnv1a
        {
            // methods

            uint32 generate(string_ref const & string);
        }
    }
}

#endif // _gg_hash_h_
