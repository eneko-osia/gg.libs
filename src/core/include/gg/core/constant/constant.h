#ifndef _gg_constant_h_
#define _gg_constant_h_

// include files

#include "gg/core/type/limit.h"
#include "gg/core/type/type.h"

// namespace

namespace gg
{
    // namespace in charge of define constant utilities

    namespace constant
    {
        // int8 constants

        static constexpr int8 int8_max = limit::numeric<int8>::max();
        static constexpr int8 int8_min = limit::numeric<int8>::min();

        // uint8 constants

        static constexpr uint8 uint8_max = limit::numeric<uint8>::max();
        static constexpr uint8 uint8_min = limit::numeric<uint8>::min();

        // int16 constants

        static constexpr int16 int16_max = limit::numeric<int16>::max();
        static constexpr int16 int16_min = limit::numeric<int16>::min();

        // uint16 constants

        static constexpr uint16 uint16_max = limit::numeric<uint16>::max();
        static constexpr uint16 uint16_min = limit::numeric<uint16>::min();

        // int32 constants

        static constexpr int32 int32_max = limit::numeric<int32>::max();
        static constexpr int32 int32_min = limit::numeric<int32>::min();

        // uint32 constants

        static constexpr uint32 uint32_max = limit::numeric<uint32>::max();
        static constexpr uint32 uint32_min = limit::numeric<uint32>::min();

        // int64 constants

        static constexpr int64 int64_max = limit::numeric<int64>::max();
        static constexpr int64 int64_min = limit::numeric<int64>::min();

        // uint64 constants

        static constexpr uint64 uint64_max = limit::numeric<uint64>::max();
        static constexpr uint64 uint64_min = limit::numeric<uint64>::min();

        // float32 constants

        static constexpr float32 float32_epsilon = limit::numeric<float32>::epsilon();
        static constexpr float32 float32_max = limit::numeric<float32>::max();
        static constexpr float32 float32_min = limit::numeric<float32>::min();

        // float64 constants

        static constexpr float64 float64_epsilon = limit::numeric<float64>::epsilon();
        static constexpr float64 float64_max = limit::numeric<float64>::max();
        static constexpr float64 float64_min = limit::numeric<float64>::min();
    }
}

// core fundamental constants

using gg::constant::int8_max;
using gg::constant::int8_min;

using gg::constant::uint8_max;
using gg::constant::uint8_min;

using gg::constant::int16_max;
using gg::constant::int16_min;

using gg::constant::uint16_max;
using gg::constant::uint16_min;

using gg::constant::int32_max;
using gg::constant::int32_min;

using gg::constant::uint32_max;
using gg::constant::uint32_min;

using gg::constant::int64_max;
using gg::constant::int64_min;

using gg::constant::uint64_max;
using gg::constant::uint64_min;

using gg::constant::float32_epsilon;
using gg::constant::float32_max;
using gg::constant::float32_min;

using gg::constant::float64_epsilon;
using gg::constant::float64_max;
using gg::constant::float64_min;

#endif // _gg_constant_h_
