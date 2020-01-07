#include "gg/crypt/hash/hash.h"

//==============================================================================

#include "gg/core/string/type/string_ref.h"

//==============================================================================
namespace gg
{
//==============================================================================

uint32 hash::fnv1::generate(string_ref const & string)
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

uint32 hash::fnv1a::generate(string_ref const & string)
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

//==============================================================================
}
//==============================================================================
