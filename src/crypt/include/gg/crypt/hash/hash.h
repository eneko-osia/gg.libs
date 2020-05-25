#ifndef _gg_hash_h_
#define _gg_hash_h_

// include files

#include "gg/core/string/type/string_ref.h"

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

            inline constexpr uint32 generate(string_ref const & string)
            {
                static constexpr uint32 k_offset_basis = 0x811c9dc5;
                static constexpr uint32 k_prime = (1 << 24) + (1 << 8) + 0x93;

                uint32 hash = k_offset_basis;
                for (auto cit = string.begin(); cit != string.end(); ++cit)
                {
                    hash *= k_prime;
                    hash ^= type::cast_static<uint8>(*cit);
                }
                return hash;
            }
        }

        // namespace in charge of define fnv1a hash utilities

        namespace fnv1a
        {
            // methods

            inline constexpr uint32 generate(string_ref const & string)
            {
                static constexpr uint32 k_offset_basis = 0x811c9dc5;
                static constexpr uint32 k_prime = (1 << 24) + (1 << 8) + 0x93;

                uint32 hash = k_offset_basis;
                for (auto cit = string.begin(); cit != string.end(); ++cit)
                {
                    hash ^= type::cast_static<uint8>(*cit);
                    hash *= k_prime;
                }
                return hash;
            }
        }
    }
}

#endif // _gg_hash_h_
