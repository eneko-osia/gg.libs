#ifndef _gg_memory_h_
#define _gg_memory_h_

// include files

#include "gg/core/type/type_trait.h"
#include <cstdlib>
#include <cstring>
#include <new>

// namespace

namespace gg
{
    // class in charge of define memory utilities

    class memory final
    {
    public:

        // type definitions

        typedef uint32 value_type;

        // methods

        static int32
        compare(void const * lptr, void const * rptr, size_type bytes) noexcept
        {
            GG_ASSERT_NOT_NULL(lptr);
            GG_ASSERT_NOT_NULL(rptr);
            return std::memcmp(lptr, rptr, bytes);
        }

        template <typename TYPE>
        static int32
        compare(TYPE const * lptr, TYPE const * rptr, size_type items = 1) noexcept
        {
            return compare(
                type::cast_static<void const *>(lptr),
                type::cast_static<void const *>(rptr),
                items * sizeof(TYPE));
        }

        static void *
        copy(void * destination, void const * source, size_type bytes) noexcept
        {
            GG_ASSERT(bytes == 0 || nullptr != destination);
            GG_ASSERT(bytes == 0 || nullptr != source);
            GG_ASSERT(
                ((type::cast_static<uchar8 *>(destination)) + bytes) <=
                    (type::cast_static<const uchar8 *>(source)) ||
                ((type::cast_static<const uchar8 *>(source)) + bytes) <=
                    (type::cast_static<uchar8 *>(destination)));

            return std::memcpy(destination, source, bytes);
        }

        template <typename TYPE>
        static TYPE *
        copy(TYPE * destination, TYPE const * source, size_type items = 1) noexcept
        {
            return type::cast_static<TYPE *>(
                copy(
                    type::cast_static<void *>(destination),
                    type::cast_static<void const *>(source),
                    items * sizeof(TYPE)));
        }

        static void *
        move(void * destination, void const * source, size_type bytes) noexcept
        {
            GG_ASSERT_NOT_NULL(destination);
            GG_ASSERT_NOT_NULL(source);
            return std::memmove(destination, source, bytes);
        }

        template <typename TYPE>
        static TYPE *
        move(TYPE * destination, TYPE const * source, size_type items = 1) noexcept
        {
            return type::cast_static<TYPE *>(
                move(
                    type::cast_static<void *>(destination),
                    type::cast_static<void const *>(source),
                    items * sizeof(TYPE)));
        }

        static void *
        set(void * destination, value_type value, size_type bytes) noexcept
        {
            GG_ASSERT_NOT_NULL(destination);
            return std::memset(destination, value, bytes);
        }

        template <typename TYPE>
        static TYPE *
        set(TYPE * destination, value_type value, size_type items = 1) noexcept
        {
            return type::cast_static<TYPE *>(
                set(
                    type::cast_static<void *>(destination),
                    value,
                    items * sizeof(TYPE)));
        }

        static void *
        zero(void * destination, size_type bytes) noexcept
        {
            GG_ASSERT_NOT_NULL(destination);
            return set(destination, value_type(0), bytes);
        }

        template <typename TYPE>
        static TYPE *
        zero(TYPE * destination, size_type items = 1) noexcept
        {
            return type::cast_static<TYPE *>(
                zero(
                    type::cast_static<void *>(destination),
                    items * sizeof(TYPE)));
        }

        static void * allocate(size_type bytes) noexcept
        {
            return std::malloc(bytes);
        }

        template <typename TYPE>
        static TYPE * allocate(size_type items = 1) noexcept
        {
            return type::cast_static<TYPE *>(allocate(items * sizeof(TYPE)));
        }

        static void deallocate(void * ptr) noexcept
        {
            std::free(ptr);
        }

        template <typename TYPE>
        static void deallocate(TYPE * ptr) noexcept
        {
            return deallocate(type::cast_static<void *>(ptr));
        }

        template <typename OBJECT_TYPE, typename... ARGS>
        static OBJECT_TYPE *
        construct_object(OBJECT_TYPE * ptr, ARGS &&... args) noexcept
        {
            OBJECT_TYPE * object =
                new (ptr) OBJECT_TYPE(type::forward<ARGS>(args)...);
            GG_ASSERT_NOT_NULL(object);
            return object;
        }

        template <typename OBJECT_TYPE>
        static void
        delete_object(OBJECT_TYPE *& object) noexcept
        {
            delete object;
            object = nullptr;
        }

        template <typename OBJECT_TYPE>
        static void
        delete_object_array(OBJECT_TYPE *& objects) noexcept
        {
            delete[] objects;
            objects = nullptr;
        }

        template <typename OBJECT_TYPE, typename... ARGS>
        static OBJECT_TYPE *
        new_object(ARGS &&... args) noexcept
        {
            OBJECT_TYPE * object =
                new (std::nothrow) OBJECT_TYPE(
                    type::forward<ARGS>(args)...);
            GG_ASSERT_NOT_NULL(object);
            return object;
        }

        template <typename OBJECT_TYPE>
        static OBJECT_TYPE *
        new_object_array(size_type size) noexcept
        {
            OBJECT_TYPE * objects = new (std::nothrow) OBJECT_TYPE[size];
            GG_ASSERT_NOT_NULL(objects);
            return objects;
        }
    };
}

#endif // _gg_memory_h_
